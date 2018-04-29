#ifndef ARGS_H
#define ARGS_H

#include <string>
#include <unordered_map>

/**
 * Holds arguments passed in an easy to lookup way
 */
class Args {
public: 
    Args(int count, char *list[]);

    // Return true if argument exists, false otherwise
    bool containsKey(char);
    // Get the value pertaining to key
    std::string getValue(char);

private:
    // Map to store arguments in. Key is character flag, Value is next argument
    std::unordered_map<char, std::string> args;
};

#endif