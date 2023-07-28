#!/bin/bash

# Check if the parent directory name is provided as an argument
if [ -z "$1" ]; then
    echo "Usage: $0 <parent_directory_name>"
    exit 1
fi

# Store the parent directory name from the first argument
parent_dir="$1"

# Create the parent directory
mkdir -p "$parent_dir"
echo "Created directory: $parent_dir"

# Create subdirectories inside the parent directory
mkdir -p $parent_dir/src
mkdir -p $parent_dir/test
mkdir -p $parent_dir/test/test-runner
echo "Created subdirectories inside $parent_dir"

# Create files
file1="Makefile"
file2="all_tests.c"
if [ -f "${file1}" ]; then
    echo "${file1} already exists"
else
    touch "$parent_dir/${file1}"
    echo "Created ${file1} at ${parent_dir}"
fi

if [ -f "${file2}" ]; then
    echo "${file1} already exists"
else
    touch "$parent_dir/test/test-runner/${file2}"
    echo "Created ${file2} at ${parent_dir}/test/test-runner"
fi

# Copy UNITY Test Framework files into $parent_dir
cp unity* "${parent_dir}"
cp Runtime* "${parent_dir}"
echo "Copied files successfully."

# Display folder structure
echo "Folder structure created:"
tree "${parent_dir}"