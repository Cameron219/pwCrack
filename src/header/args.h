#ifndef ARGS_H
#define ARGS_H

#include <string>
#include <unordered_map>

class Args {
public: 
    Args(int count, char *list[]);

    bool containsKey(char);
    std::string getValue(char);
    void displayArguments();

private:
    int count;
    std::unordered_map<char, std::string> args;
};

#endif