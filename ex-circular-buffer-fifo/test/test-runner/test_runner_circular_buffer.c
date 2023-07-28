#include "unity_fixture.h"

TEST_GROUP_RUNNER(CircularBuffer){
    RUN_TEST_CASE(CircularBuffer, CreateCircularBuffer);
    RUN_TEST_CASE(CircularBuffer, ReadPtrSetToNullAfterCreation);
    RUN_TEST_CASE(CircularBuffer, WritePtrSetToNullAfterCreation);
    RUN_TEST_CASE(CircularBuffer, ArrValSetToZeroAfterInitialization);
    RUN_TEST_CASE(CircularBuffer, FlagsAfterInitialization);
    RUN_TEST_CASE(CircularBuffer, ReadPtrPointsToFirstElementAfterInitialization);
    RUN_TEST_CASE(CircularBuffer, WritePtrPointsToFirstElementAfterInitialization);
    RUN_TEST_CASE(CircularBuffer, WriteToCircularBuffer);
    RUN_TEST_CASE(CircularBuffer, ReadFromCircularBuffer);
    RUN_TEST_CASE(CircularBuffer, WritePtrCircularBufferWrap);
    RUN_TEST_CASE(CircularBuffer, ReadPtrCircularBufferWrap);
    RUN_TEST_CASE(CircularBuffer, WritePtrCircularBufferLowerOutofBound);
    RUN_TEST_CASE(CircularBuffer, WritePtrCircularBufferUpperOutofBound);
    RUN_TEST_CASE(CircularBuffer, ReadPtrCircularBufferLowerOutofBound);
    RUN_TEST_CASE(CircularBuffer, CircularBufferFull);
    RUN_TEST_CASE(CircularBuffer, CircularBufferEmpty);
    RUN_TEST_CASE(CircularBuffer, NullPtrReceptionProducesRuntimeErrorInDestroy);
    RUN_TEST_CASE(CircularBuffer, DestroyCreatedCircularBuffer);
}