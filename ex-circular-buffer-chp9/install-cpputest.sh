#!/bin/bash

# Clone the CppUTest repository
git clone https://github.com/cpputest/cpputest.git

# Change to the cpputest repo
cd ./cpputest/

# Build it using Autotools
autoreconf . -i 
./configure
make tdd

# Go back to project directory
cd ..