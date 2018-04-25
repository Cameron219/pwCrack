#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <mutex>
#include <condition_variable>

class Semaphore {
public:
    void signal();
    void wait();
    bool try_wait();
private:
    std::mutex mutex_;
    std::condition_variable cv;
    int count_ = 0;
};

#endif