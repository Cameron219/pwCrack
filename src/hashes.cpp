#include "header/hashes.h"

#include <iostream>
#include <string>
#include <unordered_map>
#include <condition_variable>

using std::string;
using std::unordered_map;
using std::condition_variable;

void Hashes::addHash(string &hash) {
    if(hashes.find(hash) == hashes.end()){
        hashes[hash] = "";
        numOfHashes++;
    }
}

bool Hashes::areCracked() {
    std::shared_lock<std::shared_timed_mutex> lock(mutex_);
    return numOfHashes == numCracked;
}

bool Hashes::find(string& hash) {
    std::shared_lock<std::shared_timed_mutex> lock(mutex_);
    return hashes.find(hash) != hashes.end();
}

void Hashes::set(string& hash, const string &pass) {
    std::unique_lock<std::shared_timed_mutex> lock(mutex_);
    if(hashes[hash] == ""){
        numCracked++;
        write(hash + " : " + pass);
        hashes[hash] = pass;
        
    }
}

string Hashes::read() {
    return channel.read();
}

void Hashes::write(string s) {
    channel.write(s);
}

void Hashes::setOutputPath(string &path) {
    outputPath = path;
}

void Hashes::setDictionaryPath(string &path) {
    dictionaryPath = path;
}

string Hashes::getOutputPath(){
    return outputPath;
}

string Hashes::getDictionaryPath(){
    return dictionaryPath;
}

unordered_map<string, string> Hashes::getHashes(){
    return hashes;
}