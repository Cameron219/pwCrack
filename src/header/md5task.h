#ifndef MD5TASK_H
#define MD5TASK_H

#include <string>
#include <unordered_map>
#include <mutex>
#include "task.h"
#include "hashes.h"

using std::string;

class MD5Task : public Task {
public:
    MD5Task(const std::string &line_) : line_(line_) {};
    void run(Hashes&);

private:
    const std::string line_;

};

#endif