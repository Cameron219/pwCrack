#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <mutex>
#include <condition_variable>

/**
 * Controls access of data between multiple threads
 */
class Semaphore {
public:
    // Increment counter
    void signal();
    // Decrement counter
    void wait();
private:
    // Mutex to lock count
    std::mutex mutex_;
    // Condition variable to notify / wait on count
    std::condition_variable cv;
    // Peices of data available
    int count_ = 0;
};

#endif