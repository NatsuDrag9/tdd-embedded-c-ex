# Set the unit-test directory name
CPPUTEST_DIR=unit-tests

# Clone the cpputest-starter-project repository
git clone https://github.com/jwgrenning/cpputest-starter-project.git ${CPPUTEST_DIR}

# Change to the repo
cd ${CPPUTEST_DIR}/

# # Set the path for CPPUTEST_HOME variable
# export CPPUTEST_HOME=../cpputest

# Remove all test files from the repo to run the led-scheduler test files
rm makefile

cd tests/
rm *.cpp

# Change to Docker's working directory
cd ..
cd ..

# Move the test.cpp files to ${CPPUTEST_DIR}/tests
mv ./*.cpp ${CPPUTEST_DIR}/tests/

# Move the makefile to ${CPPUTEST_DIR}/
mv ./makefile ${CPPUTEST_DIR}/

# Change to ${CPPUTEST_DIR}/
cd ${CPPUTEST_DIR}/

# Run the makefile
# make
