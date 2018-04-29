#include "header/args.h"

#include <string>

using std::string;

/**
 * Constructor
 * Split up args and place within map
 */
Args::Args(int argc, char *argv[]) {
    // Loop through number of arguments. Skip 0 as it just contains program name
    for(int i = 1; i < argc; i++) {
        // Store argument
        string arg = argv[i];
        // Check to see if argument begins with - and has an argument after it
        if(arg[0] == '-' && argc > (i + 1)) {
            // Store character after - as key, next argument in argv as value
            args[arg.at(1)] = argv[++i];
        }
    }
}

/**
 * Check to see if argument exists
 * Return: true if exists, false otherwise
 */
bool Args::containsKey(char key) {
    return args.find(key) != args.end();
}

/**
 * Get value pertaining to specified key
 * key: Argument to look for
 * Return: Value tied to key, if key exists, otherwise empty string
 */
string Args::getValue(char key) {
    return containsKey(key) ? args.find(key)->second : "";
}