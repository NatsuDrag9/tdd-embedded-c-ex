#include <stdio.h>
#include <string.h>
#include "unity_fixture.h"

TEST_GROUP(sprintf);

static char output[100];
static const char* expected;

TEST_SETUP(sprintf){
    memset(output, 0xaa, sizeof(output));
    expected = "";
}

TEST_TEAR_DOWN(sprintf){
    // no cleanup work for this test group
}

static void expect(const char* s){
    expected = s;
}

static void given(int charsWritten){
    TEST_ASSERT_EQUAL(strlen(expected), charsWritten);
    TEST_ASSERT_EQUAL_STRING(expected, output);
    TEST_ASSERT_BYTES_EQUAL(0xaa, output[strlen(expected)+1]);
}

TEST(sprintf, NoFormatOperations){
    expect("hey");
    given(sprintf(output, "hey"));
}

TEST(sprintf, InsertString){
   expect("Hello World\n");
   given(sprintf(output, "Hello %s\n", "World"));
}