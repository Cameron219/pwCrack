#include "header/channel.h"

void Channel::write(std::string s) {
    std::unique_lock<std::mutex> lock(buffer_mutex);
    buffer.push_back(s);
    sem.signal();
}

std::string Channel::read() {
    sem.wait();
    std::unique_lock<std::mutex> lock(buffer_mutex);
    std::string s = buffer.front();
    buffer.pop_front();
    return s;
}