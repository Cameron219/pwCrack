#include "header/semaphore.h"

/**
 * Increment the counter
 */
void Semaphore::signal() {
    std::unique_lock<std::mutex> lock(mutex_);
    ++count_;
    cv.notify_one();
}

/**
 * Decrement the counter
 * If counter becomes 0, wait for signal to be called
 */
void Semaphore::wait() {
    std::unique_lock<std::mutex> lock(mutex_);
    while(!count_) {
        cv.wait(lock);
    }
    --count_;
}