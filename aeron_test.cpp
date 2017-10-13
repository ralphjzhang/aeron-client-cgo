#include <thread>
#include <chrono>
#include <iostream>
#include "aeron.h"

int main(int argc, char **argv) {
    int ret = aeron_initialize((char*)"/dev/shm/yi-quas");
    if (ret < 0)
        return -1;

    int pub_idx = aeron_add_publication("aeron:udp?endpoint=localhost:40123", 10);
    for (int i = 0; i < 5; ++i) {
        char buf[16];
        sprintf(buf, "hello%d", i);
        aeron_publish(pub_idx, (char*)buf, 7);
        std::cout << "pubed" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
    //aeron_remove_publication(pub_idx);
    //aeron_destroy();
}