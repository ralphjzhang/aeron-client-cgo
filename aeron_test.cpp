#include <thread>
#include <chrono>
#include <iostream>
#include "aeron.h"

int main(int argc, char **argv) {
    aeron_initialize((char*)"/dev/shm/yi-quas");

    int pub_idx = aeron_add_publication("aeron:udp?endpoint=localhost:40123", 10);
    while (true) {
        aeron_publish(pub_idx, (char*)"hello", 6);
        std::cout << "pubed" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}