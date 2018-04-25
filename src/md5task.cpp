#include <string>
#include <unordered_map>
#include <mutex>
#include <iostream>

#include "header/md5task.h"
#include "header/md5.h"
#include "header/hashes.h"

using std::string;
using std::unordered_map;

void MD5Task::run(Hashes &hashes) {
    string hash = md5(line_);

    if(hashes.find(hash)) {
        hashes.set(hash, line_);
    }
}