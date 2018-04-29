#include "header/channel.h"

/**
 * Write file to buffer, signal that there's something to be read
 */
void Channel::write(std::string s) {
    // Lock the buffer_mutex
    std::unique_lock<std::mutex> lock(buffer_mutex);
    // Push string to buffer
    buffer.push_back(s);
    // Signal that something has been placed in the buffer
    sem.signal();
}

/**
 * Wait for signal. when signalled, read from buffer and return it
 */
std::string Channel::read() {
    // Wait for signal from write
    sem.wait();
    std::unique_lock<std::mutex> lock(buffer_mutex);
    
    // Peek at the value at the front of the buffer
    std::string s = buffer.front();
    // Pop the value off the front of the buffer
    buffer.pop_front();

    return s;
}