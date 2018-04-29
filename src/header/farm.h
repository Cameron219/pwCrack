#ifndef FARM_H
#define FARM_H

#include "task.h"
#include "hashes.h"

#include <queue>
#include <mutex>
#include <unordered_map>
#include <string>

/**
 * Handles worker threads and tasks
 * Distributes load of tasks between worker threads
 */
class Farm {
public:
    // Add task to task queue
    void add_task(Task*);
    // Run the farm
    void run(Hashes&);

private:
    // Queue of tasks
    std::queue<Task *> tasks;
    // Tasks mutex
    std::mutex tasks_mutex;
};

#endif