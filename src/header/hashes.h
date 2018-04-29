#ifndef HASHES_H
#define HASHES_H

#include "channel.h"

#include <string>
#include <unordered_map>
#include <mutex>
#include <shared_mutex>

/**
 * Class that holds the hashes to be cracked.
 * Also acts as a container for any info that might need to be accessed accross threads.
 * 
 */
class Hashes {
public:
    // Add hash to map
    void addHash(std::string&);
    // Set hash as cracked, set value as cracked pass
    void set(std::string&, const std::string&);
    // Write to channel
    void write(std::string);
    // Set the output file path
    void setOutputPath(std::string&);
    // Set the dictionary file path
    void setDictionaryPath(std::string&);

    // Check if all hashes are cracked
    bool areCracked();
    // Find a hash within map, return true if found, false otherwise
    bool find(std::string&);
    
    // Read from channel
    std::string read();
    // Get the output file path
    std::string getOutputPath();
    // Get the dictionary file path
    std::string getDictionaryPath();

private:
    // Number of total hashes in map
    int numOfHashes = 0;
    // Number of cracked hashes within map
    int numCracked = 0;

    // Output file path
    std::string outputPath;
    // Dictionary file path
    std::string dictionaryPath;
    // Store hashes and cracked passwords. Key = hash, value = pass
    std::unordered_map<std::string, std::string> hashes;
    // Mutex used when accessing variables within hashes object
    // Allows multiple threads to read, assuming no threads are writing
    std::shared_timed_mutex mutex_;
    
    // Channel declaration. Allows data passed between threads.
    Channel channel;
};

#endif