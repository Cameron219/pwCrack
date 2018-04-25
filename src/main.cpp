#include "header/args.h"
#include "header/farm.h"
#include "header/task.h"
#include "header/hashes.h"
#include "header/md5task.h"
#include "header/sha1task.h"
#include "header/sha256task.h"

#include <string>
#include <chrono>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <unordered_map>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
using std::getline;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::unordered_map;

typedef std::chrono::steady_clock the_clock;

void loadFile(ifstream &file, string &path) {
    file.open(path);
    if(file.fail() || !file.is_open()) {
        throw std::invalid_argument("Unable to load file: " + path);
    }
}

void storeHashes(ifstream &file, Hashes &hashes) {
    string line;

    while(getline(file, line)) {
        if(!line.empty()) {
            hashes.addHash(line);
        }
    }
}

void crackHashes(ifstream &dict, Hashes &hashes, string &type) {
    Farm farm;
    string line;

    while(getline(dict, line)) {
        if(!line.empty()) {
            if(type == "MD5"){
                farm.add_task(new MD5Task(line));
            }
            else if(type == "SHA1"){
                farm.add_task(new SHA1Task(line));
            }
            else if(type == "SHA256") {
                farm.add_task(new SHA256Task(line));
            }
        }
    }
    
    farm.run(hashes);
}

int main(int argc, char *argv[]) {
    Args args(argc, argv);
    Hashes hashes;
    
    if(args.containsKey('d') && args.containsKey('h')) {
        string dictionary_path = args.getValue('d');
        string hashes_path = args.getValue('h');
        string output_path = args.containsKey('o') ? args.getValue('o') : "cracked.txt";
        string hashType = args.containsKey('t') ? args.getValue('t') : "MD5";

        hashes.setDictionaryPath(dictionary_path);
        hashes.setOutputPath(output_path);

        cout << "Loading Dictionary: " << dictionary_path << endl;
        // Load dictionary file
        ifstream dictionary_file;
        loadFile(dictionary_file, dictionary_path);

        cout << "Loading Hashes: " << hashes_path << endl << endl;
        // Load hashes file
        ifstream hashes_file;
        loadFile(hashes_file, hashes_path);

        // Read hashes from file and store in unordered map
        storeHashes(hashes_file, hashes);
        hashes_file.close();
        
        // Attempt to crack the hashes
        cout << "Attempting to crack hashes..." << endl << endl;

        the_clock::time_point start = the_clock::now();
        crackHashes(dictionary_file, hashes, hashType);
        the_clock::time_point end = the_clock::now();
        dictionary_file.close();

        cout << endl << "Finished. Outputted to: " << output_path << endl;

        auto time_taken = duration_cast<milliseconds>(end - start).count();
        cout << endl << "Cracking took " << time_taken << " ms." << endl;
    } else {
        cout << "Welcome to my password cracker!" << endl
             << "Please specify a dictionary file with -d" << endl
             << "And specify hashes file with -h" << endl
             << "Example: ./pwCrack -d rockyou.txt -h hashes.txt" << endl
             << "Optionally an output file can be specified as well with -o" << endl;
    }
}