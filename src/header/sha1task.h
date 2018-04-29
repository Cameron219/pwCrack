#ifndef SHA1TASK_H
#define SHA1TASK_H

#include <string>
#include <unordered_map>
#include <mutex>
#include "task.h"
#include "hashes.h"

using std::string;

/**
 * Task that stores and attempts to crack SHA1 hash
 */
class SHA1Task : public Task {
public:
    // Store SHA1 Hash String
    SHA1Task(const std::string &line_) : line_(line_) {};
    // Run task
    void run(Hashes &hashes);

private:
    //SHA1 Hash String
    const std::string line_;

};

#endif