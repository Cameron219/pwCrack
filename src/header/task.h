#ifndef TASK_H
#define TASK_H

#include "hashes.h"

#include <string>
#include <mutex>
#include <unordered_map>

class Task {
public:
    virtual ~Task() {

    }

    virtual void run(Hashes&) = 0;
};

#endif