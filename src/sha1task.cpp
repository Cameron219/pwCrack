#include <string>
#include <unordered_map>
#include <mutex>
#include <iostream>

#include "header/sha1task.h"
#include "header/sha1.h"
#include "header/hashes.h"

using std::string;
using std::unordered_map;

/**
 * Hash SHA1 String, then check and see if it exists within hashes map.
 * If it does then set the hash as cracked.
 */
void SHA1Task::run(Hashes &hashes) {
    string hash = sha1(line_);

    if(hashes.find(hash)) {
        hashes.set(hash, line_);
    }
}