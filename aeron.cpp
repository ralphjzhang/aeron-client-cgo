#include "aeron.h"
#include <array>
#include <thread>
#include <chrono>
#include <Aeron.h>

using namespace aeron::util;
using namespace aeron;

// to simplify, we use a fixed size array for publications, and let client use index
// since publication is potentially expensive, 16 publication should be enough
std::shared_ptr<Aeron> g_aeron;
std::mutex g_publications_lock;
std::array<std::shared_ptr<Publication>, 128> g_publications;
std::mutex g_subscriptions_lock;
std::array<std::shared_ptr<Subscription>, 16> g_subscriptions;

int aeron_initialize(char *aeron_dir) {
    try {
        aeron::Context context;
        context.aeronDir(aeron_dir);
        context.newSubscriptionHandler(
            [](const std::string& channel, std::int32_t streamId, std::int64_t correlationId) {
                std::cout << "Subscription: " << channel << " " << correlationId << ":" << streamId << std::endl;
            }
        );
        context.availableImageHandler(
            [](Image &image) {
                std::cout << "Available image correlationId=" << image.correlationId() << " sessionId=" << image.sessionId()
                    << std::endl;
            }
        );
        context.unavailableImageHandler(
            [](Image &image) {
                std::cout << "Unavailable image correlationId=" << image.correlationId() << " sessionId=" << image.sessionId()
                    << std::endl;
            }
        );
        g_aeron = Aeron::connect(context);
        return 0;
    } catch (std::exception const& e) {
        std::cerr << "aeron_initialize: exception - " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "aeron_initialize: unknown exception" << std::endl;
    }
    return -1;
}

void aeron_destroy() {
    g_aeron.reset();
}

// return: publication index
int aeron_add_publication(char *channel, int stream_id) {
    auto id = g_aeron->addPublication(channel, stream_id);
    auto p = g_aeron->findPublication(id);
    while (!p) {
        std::this_thread::yield();
        p = g_aeron->findPublication(id);
    }
    {
        std::lock_guard<std::mutex> _(g_publications_lock);
        for (size_t i = 0; i < g_publications.size(); ++i) {
            if (!g_publications[i]) {
                g_publications[i] = p;
                return i;
            }
        }
    }
    return -1;
}

void aeron_remove_publication(int publication_idx) {
    g_publications[publication_idx].reset();
}

int aeron_add_subscription(char *channel, int stream_id) {
    std::cout << "subing: " << std::endl;
    auto id = g_aeron->addSubscription(channel, stream_id);
    std::cout << "sub: " << id << std::endl;
    auto s = g_aeron->findSubscription(id);
    while (!s) {
        std::this_thread::yield();
        s = g_aeron->findSubscription(id);
    }
    {
        std::lock_guard<std::mutex> _(g_subscriptions_lock);
        for (size_t i = 0; i < g_subscriptions.size(); ++i) {
            if (!g_subscriptions[i]) {
                g_subscriptions[i] = s;
                return i;
            }
        }
    }
    return -1;
}

void aeron_publish(int publication_idx, char* msg, int msg_len) {
    std::array<uint8_t, 256> buffer __attribute__((aligned(16)));
    concurrent::AtomicBuffer srcBuffer(&buffer[0], buffer.size());
    srcBuffer.putBytes(0, reinterpret_cast<uint8_t*>(msg), msg_len);

    // no locks needed here, since g_publications is fixed sized
    g_publications[publication_idx]->offer(srcBuffer, 0, msg_len);
}

void aeron_poll(int subscription_idx) {
    auto handler = [](const AtomicBuffer& buffer, util::index_t offset, util::index_t length, const Header& header) {
        std::cout << "Message to stream " << header.streamId() << " from session " << header.sessionId();
        std::cout << std::string(reinterpret_cast<const char*>(buffer.buffer()) + offset, static_cast<std::size_t>(length)) << std::endl;
    };
    SleepingIdleStrategy idle(std::chrono::milliseconds(1));

    const int fragments_read = g_subscriptions[subscription_idx]->poll(handler, 10);
    idle.idle(fragments_read);
}