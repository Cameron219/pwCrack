#ifndef MD5TASK_H
#define MD5TASK_H

#include <string>
#include <unordered_map>
#include <mutex>
#include "task.h"
#include "hashes.h"

using std::string;

/**
 * Task that stores and attempts to crack MD5 hash
 */
class MD5Task : public Task {
public:
    // Store MD5 Hash String
    MD5Task(const std::string &line_) : line_(line_) {};
    // Run task
    void run(Hashes&);

private:
    // MD5 Hash String
    const std::string line_;

};

#endif