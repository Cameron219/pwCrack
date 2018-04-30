#include "header/farm.h"
#include "header/md5task.h"
#include "header/hashes.h"

#include <iostream>
#include <thread>
#include <fstream>

using std::mutex;
using std::thread;
using std::string;
using std::ofstream;

/**
 * Add a task to the task queue
 */
void Farm::add_task(Task *task) {
    tasks.push(task);
}

/**
 * Get the number of available cores on the system and create that many worker threads.
 * Each worker thread pulls tasks from the task queue and runs them, until there are no tasks left.
 * The output thread waits for a worker thread to crack a hash and then outputs it to the console and file
 */
void Farm::run(Hashes &hashes) {
    // Get the number of cores on the system
    int threadCount = std::thread::hardware_concurrency();
    // int threadCount = 2;
    int threadsFinished = 0;
    thread *threads[threadCount];

    // Thread that listens for output from the other threads
    thread outputThread = thread([&] {
        ofstream outputFile;
        outputFile.open(hashes.getOutputPath(), std::ofstream::out | std::ofstream::app);
        // Display what dictionary was used
        outputFile << "----- " << hashes.getDictionaryPath() << " -----" << std::endl;

        // While there are still worker threads running or there are strings in the buffer to be read
        while(threadCount > threadsFinished || !hashes.isWriteBufferEmpty()) {
            // Read from worker threads write calls
            string s = hashes.read();

            // If empty write is passed
            if(s.empty()) continue;
            // Output hash : pass to file
            outputFile << s << std::endl;
            // Print hash : pass to terminal
            std::cout << s << std::endl;
        }

        outputFile << std::endl;
        return;
    });

    for(int i = 0; i < threadCount; i++) {
        // Create new worker thread
        threads[i] = new thread([&] {
            while(true) {
                tasks_mutex.lock();
                // if((tasks.empty() && noMoreInput == true) || hashes.areCracked()){
                // If there are no more tasks to run or all hashes have been cracked.
                // Then use empty write call to wake up the output thread and close this thread with return
                if(tasks.empty() || hashes.areCracked()){
                    threadsFinished++;
                    tasks_mutex.unlock();
                    // Hate this, fix it later (exit condition for output thread)
                    hashes.write("");
                    return;
                }
                Task *task;
                
                // Get task off the task queue
                task = tasks.front();
                tasks.pop();
                tasks_mutex.unlock();

                // Run the task
                task->run(hashes);
                delete task;
            }
        });
    }

    // Join threads
    for(int i = 0; i < threadCount; i++) {
        threads[i]->join();
    }
    outputThread.join();
}