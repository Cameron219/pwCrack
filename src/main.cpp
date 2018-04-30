/*
    This is a linux based multi-threaded password cracking tool.
    It supports MD5, SHA1 & SHA256 password cracking.
    Flags:
        -d : Dictionary File
        -h : Hashes File
        -t : Hash Type (Optional, Default: MD5, Accepts: MD5, SHA1 & SHA256)
        -o : Output File (Optional, Default: cracked.txt)
    
    Example:
        ./pwCrack -d /usr/share/dict/words -h hashes/md5.txt -t MD5 -o crackedMD5.txt

    
    Author: Cameron McCallion
*/

// Include necessary header files
#include "header/args.h"
#include "header/farm.h"
#include "header/task.h"
#include "header/hashes.h"
#include "header/md5task.h"
#include "header/sha1task.h"
#include "header/sha256task.h"

// Include necessary source files
#include <string>
#include <chrono>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <algorithm>

// Using declarations
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
using std::chrono::steady_clock;

const string DEFAULT_OUTPUT_FILE = "cracked.txt";
const string DEFAULT_HASH_TYPE = "MD5";

/**
 * Load a file from the disk
 * &file: Input Stream
 * &path: Path to file on disk
 */
bool loadFile(ifstream &file, string &path) {
    file.open(path);
    // If file does not exist, throw an exception
    if(file.fail() || !file.is_open()) {
        return false;
    }
    return true;
}

/**
 * Reads input stream and stores each line into hashes map
 * &ifstream: Input file stream
 * &hashes: Hashes object
 */
void storeHashes(ifstream &file, Hashes &hashes) {
    string line;

    // Loop through each line of the file
    while(getline(file, line)) {
        // Skip empty lines
        if(!line.empty()) {
            // Add line to hashes map
            hashes.addHash(line);
        }
    }
}

/**
 * Create tasks for each line of dictionary file, create and run the farm.
 * 
 * &dict: Dictionary file
 * &hashes: Hashes object
 * &type: Type of hash
 */
void crackHashes(ifstream &dict, Hashes &hashes, string &type) {
    Farm farm;
    string line;

    // Loop through each line of dictionary file
    while(getline(dict, line)) {
        // If the line contains at least one character
        if(!line.empty()) {
            // Create task and add to task queue based on hash type
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
    
    // Run the farm
    farm.run(hashes);
}

/**
 * Validate the hash type input
 */
bool validateType(string &type) {
    if(type == "MD5" || type == "SHA1" || type == "SHA256") {
        return true;
    }
    return false;
}

/**
 * Handles and validates arguments passed
 */
int main(int argc, char *argv[]) {
    Args args(argc, argv);
    Hashes hashes;
    
    // Make sure that dictionary and hashes are specified
    if(args.containsKey('d') && args.containsKey('h')) {
        // Get dictionary file path from args
        string dictionary_path = args.getValue('d');
        // Get hash file path from args
        string hashes_path = args.getValue('h');
        // Get output file path from args, if none specified then use default
        string output_path = args.containsKey('o') ? args.getValue('o') : DEFAULT_OUTPUT_FILE;
        // Get hash type from args, if none specified then use MD5
        string hashType = args.containsKey('t') ? args.getValue('t') : DEFAULT_HASH_TYPE;

        // Set the dictionary path within hashes object
        hashes.setDictionaryPath(dictionary_path);
        // Set the output path within hashes object
        hashes.setOutputPath(output_path);

        // Convert hashType to uppercase
        std::transform(hashType.begin(), hashType.end(), hashType.begin(), ::toupper);

        // If invalid type soecified, print error message and stop execution
        if(!validateType(hashType)) {
            std::cerr << "Invalid Hash Type specified" << endl
                      << hashType << endl;
            return 1;
        }

        // Load dictionary file
        cout << "Loading Dictionary: " << dictionary_path << endl;
        ifstream dictionary_file;

        // If file is not loaded, print error message to user and stop execution
        if(!loadFile(dictionary_file, dictionary_path)) {
            std::cerr << "Unable to load dictionary file specified." << endl
                      << dictionary_path << endl;
            return 1;
        }

        // Load hashes file
        cout << "Loading Hashes: " << hashes_path << endl << endl;
        ifstream hashes_file;
        
        // If file is not loaded, print error message to user and stop execution
        if(!loadFile(hashes_file, hashes_path)) {
            std::cerr << "Unable to load hashes file specified." << endl
                      << hashes_path << endl;
            return 1;
        }

        // Read hashes from file and store in unordered map
        storeHashes(hashes_file, hashes);
        // Close the hashes file, as no longer needed
        hashes_file.close();
        
        cout << "Attempting to crack hashes..." << endl << endl;

        // Store start time
        steady_clock::time_point start = steady_clock::now();

        // Attempt to crack hashes
        crackHashes(dictionary_file, hashes, hashType);

        // Store end time
        steady_clock::time_point end = steady_clock::now();

        // Close dictionary file, as no longer needed.
        dictionary_file.close();

        if(hashes.getNumCracked() > 0) {
            // Print output path
            cout << endl << "Finished. Cracked " << hashes.getNumCracked() << "/" << hashes.getTotalHashes() << " hashes." << endl;
            cout << "Outputted to: " << output_path << endl;

            // Calculate time taken and print
            auto time_taken = duration_cast<milliseconds>(end - start).count();
            cout << endl << "Cracking took " << time_taken << " ms." << endl;
        } else {
            cout << endl << "Finished. No hashes were cracked." << endl;
        }
    }
    else { // If no arguments are specified, display welcome / help message
        cout << "This is a linux based multi-threaded password cracking tool. \n"
             << "It supports MD5, SHA1 & SHA256 hashes. \n"
             << "Created By: Cameron McCallion. \n\n"
             << "Flags:\n\t"
             << "-d : Dictionary File (Mandatory)\n\t"
             << "-h : Hashes File (Mandatory)\n\t"
             << "-t : Hash Type (Optional, Default: MD5, Accepts: MD5, SHA1 & SHA256)\n\t"
             << "-o : Output File (Optional, Default: ./cracked.txt)\n\n"
             << "Examples:\n\t"
             << "./pwCrack -d /usr/share/dict/words -h hashes/md5.txt -t MD5 -o crackedMD5.txt\n\t"
             << "./pwCrack -d /usr/share/dict/words -h hashes/sha256.txt -t SHA256\n\t"
             << "./pwCrack -d dict/wordlist.txt -h hashes/md5.txt" << endl;
    }

    return 0;
}