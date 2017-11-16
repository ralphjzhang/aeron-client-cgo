#include <cstdint>
#include <cstdio>
#include <thread>
#include <Aeron.h>
#include <string>


using namespace aeron::util;
using namespace aeron;

extern std::shared_ptr<Aeron> g_aeron;

fragment_handler_t printStringMessage()
{
    return [&](const AtomicBuffer& buffer, util::index_t offset, util::index_t length, const Header& header)
    {
        std::cout << "Message to stream " << header.streamId() << " from session " << header.sessionId();
        std::cout << "(" << length << "@" << offset << ") <<";
        std::cout << std::string(reinterpret_cast<const char *>(buffer.buffer()) + offset, static_cast<std::size_t>(length)) << ">>" << std::endl;
    };
}

int main(int argc, char** argv)
{
    aeron::Context context;
    context.aeronDir("/opt/yi/data/aeron/quas");

    g_aeron = Aeron::connect(context);

    std::int64_t id = g_aeron->addSubscription("aeron:ipc", 1);
    std::shared_ptr<Subscription> subscription = g_aeron->findSubscription(id);
    while (!subscription)
    {
        std::this_thread::yield();
        subscription = g_aeron->findSubscription(id);
    }

    fragment_handler_t handler = printStringMessage();
    SleepingIdleStrategy idleStrategy(std::chrono::milliseconds(1));

    while (true)
    {
        const int fragmentsRead = subscription->poll(handler, 10);
        idleStrategy.idle(fragmentsRead);
    }

    return 0;
}