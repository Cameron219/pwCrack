#include "header/args.h"

#include <string>

using std::string;

Args::Args(int argc, char *argv[]) {
    for(int i = 1; i < argc; i++) {
        string arg = argv[i];
        if(arg[0] == '-' && argc > (i + 1)) {
            args[arg.at(1)] = argv[++i];
        }
    }
}

bool Args::containsKey(char key) {
    return args.find(key) != args.end();
}

string Args::getValue(char key) {
    return containsKey(key) ? args.find(key)->second : "";
}