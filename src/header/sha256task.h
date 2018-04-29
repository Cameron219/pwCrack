#ifndef SHA256TASK_H
#define SHA256TASK_H

#include <string>
#include <unordered_map>
#include <mutex>
#include "task.h"
#include "hashes.h"

using std::string;

/**
 * Task that stores and attempts to crack SHA1 hash
 */
class SHA256Task : public Task {
public:
    // Store SHA256 Hash String
    SHA256Task(const std::string &line_) : line_(line_) {};
    // Run task
    void run(Hashes &hashes);

private:
    // SHA256 Hash String
    const std::string line_;

};

#endif