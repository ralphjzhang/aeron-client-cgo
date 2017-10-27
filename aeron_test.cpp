#include <thread>
#include <chrono>
#include <iostream>
#include "aeron.h"

int main(int argc, char **argv) {
    int ret = aeron_initialize((char*)"/opt/yi/data/aeron/quas");
    if (ret < 0)
        return -1;

    std::cout << "inited" << std::endl;
    int sub_idx = aeron_add_subscription("aeron:ipc", 11);
    std::cout << "sub idx: " << sub_idx << std::endl;
    aeron_poll(sub_idx);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    //aeron_remove_publication(pub_idx);
    //aeron_destroy();
}