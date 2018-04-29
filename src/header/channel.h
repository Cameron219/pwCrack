#ifndef CHANNEL_H
#define CHANNEL_H

#include "semaphore.h"

#include <string>
#include <mutex>
#include <list>

/**
 * C++ Implementation of a Channel
 * Used to write and read data between threads
 */
class Channel {
public:
    // Write data into buffer
    void write(std::string);
    // Read data from buffer
    std::string read();

private:
    // Buffer of strings to be outputted
    std::list<std::string> buffer;
    // Lock for buffer
    std::mutex buffer_mutex;
    // Semaphore for signaling when buffer is ready
    Semaphore sem;
};

#endif