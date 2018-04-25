#ifndef CHANNEL_H
#define CHANNEL_H

#include "semaphore.h"

#include <string>
#include <mutex>
#include <list>

class Channel {
public:
    void write(std::string);
    std::string read();
    void done();

private:
    std::list<std::string> buffer;
    std::mutex buffer_mutex;
    Semaphore sem;
};

#endif