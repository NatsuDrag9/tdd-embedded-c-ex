# Clone the cpputest-starter-project repository
git clone https://github.com/jwgrenning/cpputest-starter-project.git unit-tests

UNITTEST_DIR=unit-tests

# Change to the repo
cd ${UNITTEST_DIR}/

# Set the path for CPPUTEST_HOME variable
export CPPUTEST_HOME=../cpputest

# Remove all test files from the repo to run the alarm-clock-service test files
rm makefile

cd tests/
rm *.cpp

# Change Docker's working directory
cd ..
cd ..

# Move the test.cpp files to ${UNITTEST_DIR}/tests
mv ./*.cpp ${UNITTEST_DIR}/tests/

# Move the makefile to ${UNITTEST_DIR}/
mv ./makefile ${UNITTEST_DIR}/

# Change to ${UNITTEST_DIR}/
cd ${UNITTEST_DIR}/

# Run the makefile
# make
