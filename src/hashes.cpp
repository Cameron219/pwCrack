#include "header/hashes.h"

#include <iostream>
#include <string>
#include <unordered_map>
#include <condition_variable>

using std::string;
using std::unordered_map;
using std::condition_variable;

/**
 * Add hash to hashes map
 * Value is set to empty string, to indicate it has not been cracked yet.
 * &hash: Hash to add
 */
void Hashes::addHash(string &hash) {
    if(hashes.find(hash) == hashes.end()){
        hashes[hash] = "";
        numOfHashes++;
    }
}

/**
 * Checks to see if all hashes in map have been cracked.
 * Returns true if all cracked, false otherwise.
 */
bool Hashes::areCracked() {
    std::shared_lock<std::shared_timed_mutex> lock(mutex_);
    return numOfHashes == numCracked;
}

/**
 * Checks to see if a hash can be found within the map.
 * Returns true if found, false otherwise.
 */
bool Hashes::find(string& hash) {
    std::shared_lock<std::shared_timed_mutex> lock(mutex_);
    return hashes.find(hash) != hashes.end();
}

/**
 * Set the value of an existing hash in the map.
 * This is used to store the cracked password value.
 * Increments the number of cracked hashes.
 * Calls write, to pass the hash and cracked password to the output thread.
 */
void Hashes::set(string& hash, const string &pass) {
    std::unique_lock<std::shared_timed_mutex> lock(mutex_);
    if(hashes[hash] == ""){
        numCracked++;
        write(hash + " : " + pass);
        hashes[hash] = pass;
    }
}

/**
 * Read data from the channel
 */
string Hashes::read() {
    return channel.read();
}

/**
 * Write data to the channel
 */
void Hashes::write(string s) {
    channel.write(s);
}

/**
 * Set the output file path
 * &path: Path to file
 */
void Hashes::setOutputPath(string &path) {
    outputPath = path;
}

/**
 * Set the dictionary file path
 * &path: Path to file
 */
void Hashes::setDictionaryPath(string &path) {
    dictionaryPath = path;
}

/**
 * Get the output file path
 */
string Hashes::getOutputPath(){
    return outputPath;
}

/**
 * Get the dictionary file path
 */
string Hashes::getDictionaryPath(){
    return dictionaryPath;
}