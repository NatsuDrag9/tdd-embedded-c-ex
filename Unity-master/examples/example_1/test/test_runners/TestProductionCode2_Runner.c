/* AUTOGENERATED FILE. DO NOT EDIT. */

/*=======Automagically Detected Files To Include=====*/
#include "unity.h"
#include "ProductionCode2.h"

/*=======External Functions This Runner Calls=====*/
extern void setUp(void);
extern void tearDown(void);
extern void test_IgnoredTest(void);
extern void test_AnotherIgnoredTest(void);
extern void test_ThisFunctionHasNotBeenTested_NeedsToBeImplemented(void);


/*=======Mock Management=====*/
static void CMock_Init(void)
{
}
static void CMock_Verify(void)
{
}
static void CMock_Destroy(void)
{
}

/*=======Test Reset Options=====*/
void resetTest(void);
void resetTest(void)
{
  tearDown();
  CMock_Verify();
  CMock_Destroy();
  CMock_Init();
  setUp();
}
void verifyTest(void);
void verifyTest(void)
{
  CMock_Verify();
}

/*=======Test Runner Used To Run Each Test=====*/
static void run_test(UnityTestFunction func, const char* name, UNITY_LINE_TYPE line_num)
{
    Unity.CurrentTestName = name;
    Unity.CurrentTestLineNumber = line_num;
#ifdef UNITY_USE_COMMAND_LINE_ARGS
    if (!UnityTestMatches())
        return;
#endif
    Unity.NumberOfTests++;
    UNITY_CLR_DETAILS();
    UNITY_EXEC_TIME_START();
    CMock_Init();
    if (TEST_PROTECT())
    {
        setUp();
        func();
    }
    if (TEST_PROTECT())
    {
        tearDown();
        CMock_Verify();
    }
    CMock_Destroy();
    UNITY_EXEC_TIME_STOP();
    UnityConcludeTest();
}

/*=======MAIN=====*/
int main(void)
{
  UnityBegin("test/TestProductionCode2.c");
  run_test(test_IgnoredTest, "test_IgnoredTest", 18);
  run_test(test_AnotherIgnoredTest, "test_AnotherIgnoredTest", 23);
  run_test(test_ThisFunctionHasNotBeenTested_NeedsToBeImplemented, "test_ThisFunctionHasNotBeenTested_NeedsToBeImplemented", 28);

  return UnityEnd();
}
