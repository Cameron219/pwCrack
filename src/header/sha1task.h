#ifndef SHA1TASK_H
#define SHA1TASK_H

#include <string>
#include <unordered_map>
#include <mutex>
#include "task.h"
#include "hashes.h"

using std::string;

class SHA1Task : public Task {
public:
    SHA1Task(const std::string &line_) : line_(line_) {};
    void run(Hashes &hashes);

private:
    const std::string line_;

};

#endif