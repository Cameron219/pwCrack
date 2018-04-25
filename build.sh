#!/bin/bash

echo "Building..."
g++ -pthread -std=c++14 src/*.cpp -o pwCrack
