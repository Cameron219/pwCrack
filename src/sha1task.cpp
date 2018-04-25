#include <string>
#include <unordered_map>
#include <mutex>
#include <iostream>

#include "header/sha1task.h"
#include "header/sha1.h"
#include "header/hashes.h"

using std::string;
using std::unordered_map;

void SHA1Task::run(Hashes &hashes) {
    string hash = sha1(line_);

    if(hashes.find(hash)) {
        hashes.set(hash, line_);
    }
}