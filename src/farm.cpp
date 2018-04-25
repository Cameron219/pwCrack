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

void Farm::add_task(Task *task) {
    tasks.push(task);
}

void Farm::run(Hashes &hashes) {
    int threadCount = std::thread::hardware_concurrency();
    // int threadCount = 2;
    int threadsFinished = 0;
    thread *threads[threadCount];

    for(int i = 0; i < threadCount; i++) {
        threads[i] = new thread([&] {
            while(true) {
                tasks_mutex.lock();
                // if((tasks.empty() && noMoreInput == true) || hashes.areCracked()){
                if(tasks.empty() || hashes.areCracked()){
                    threadsFinished++;
                    tasks_mutex.unlock();
                    // Hate this, fix it later
                    hashes.write("");
                    return;
                }
                Task *task;
                
                task = tasks.front();
                tasks.pop();
                tasks_mutex.unlock();

                task->run(hashes);
                delete task;
            }
        });
    }

    thread outputThread = thread([&] {
        ofstream outputFile;
        outputFile.open(hashes.getOutputPath(), std::ofstream::out | std::ofstream::app);
        outputFile << "----- " << hashes.getDictionaryPath() << " -----" << std::endl;

        while(threadCount > threadsFinished) {
            string s = hashes.read();
            if(s.empty()) continue;
            std::cout << s << std::endl;
            outputFile << s << std::endl;
        }

        outputFile << std::endl;
        return;
    });

    for(int i = 0; i < threadCount; i++) {
        threads[i]->join();
    }
    outputThread.join();
}