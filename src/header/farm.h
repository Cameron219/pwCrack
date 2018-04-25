#ifndef FARM_H
#define FARM_H

#include "task.h"
#include "hashes.h"

#include <queue>
#include <mutex>
#include <unordered_map>
#include <string>

class Farm {
public:
    void add_task(Task *task);
    void run(Hashes &hashes);

private:
    std::queue<Task *> tasks;
    std::mutex tasks_mutex;

    int numCracked = 0;
};

#endif