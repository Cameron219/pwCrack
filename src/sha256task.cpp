#include <string>
#include <unordered_map>
#include <mutex>
#include <iostream>

#include "header/sha256task.h"
#include "header/sha256.h"
#include "header/hashes.h"

using std::string;
using std::unordered_map;

void SHA256Task::run(Hashes &hashes) {
    string hash = sha256(line_);

    if(hashes.find(hash)) {
        hashes.set(hash, line_);
    }
}