#ifndef SHA256TASK_H
#define SHA256TASK_H

#include <string>
#include <unordered_map>
#include <mutex>
#include "task.h"
#include "hashes.h"

using std::string;

class SHA256Task : public Task {
public:
    SHA256Task(const std::string &line_) : line_(line_) {};
    void run(Hashes &hashes);

private:
    const std::string line_;

};

#endif