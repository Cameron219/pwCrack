#ifndef HASHES_H
#define HASHES_H

#include "channel.h"

#include <string>
#include <unordered_map>
#include <mutex>
#include <shared_mutex>

class Hashes {
public:
    void addHash(std::string&);
    void set(std::string&, const std::string&);
    void write(std::string);
    void setOutputPath(std::string&);
    void setDictionaryPath(std::string&);

    bool areCracked();
    bool find(std::string&);
    
    std::string read();
    std::string getOutputPath();
    std::string getDictionaryPath();
    std::unordered_map<std::string, std::string> getHashes();

private:
    int numOfHashes = 0;
    int numCracked = 0;
    bool newHashCracked = false;

    std::string outputPath;
    std::string dictionaryPath;
    std::unordered_map<std::string, std::string> hashes;
    std::shared_timed_mutex mutex_;
    
    Channel channel;
};

#endif