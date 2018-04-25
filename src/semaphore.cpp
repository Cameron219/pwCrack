#include "header/semaphore.h"

void Semaphore::signal() {
    std::unique_lock<std::mutex> lock(mutex_);
    ++count_;
    cv.notify_one();
}

void Semaphore::wait() {
    std::unique_lock<std::mutex> lock(mutex_);
    while(!count_) {
        cv.wait(lock);
    }
    --count_;
}

bool Semaphore::try_wait() {
    std::unique_lock<std::mutex> lock(mutex_);
    if(count_) {
        --count_;
        return true;
    }
    return false;
}