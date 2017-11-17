#include <thread>
#include <chrono>
#include <iostream>
#include <Aeron.h>
#include "aeron.h"

using namespace aeron;

int AeronPollCallback(unsigned char* buf, int len) {
    std::cout << "AeronPollCallback: " << std::string{(char *)buf, len} << std::endl;
}

int main(int argc, char **argv) {
    int ret = aeron_initialize((char*)"/opt/yi/data/aeron/quas");
    if (ret < 0)
        return -1;

    std::cout << "inited" << std::endl;
    if (argv[1] == std::string("pub")) {
        auto pub_idx = aeron_add_publication(argv[2], 1);
        for (int i = 0; i < 100000; ++i) {
            char buf[32];
            sprintf(buf, "pub: %d", i);
            aeron_publish(pub_idx, buf, 8);
            std::cout << buf << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    } else {
        aeron_poll(argv[2], 1);
        std::cout << "polling......." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(100));
    }
    aeron_destroy();
}