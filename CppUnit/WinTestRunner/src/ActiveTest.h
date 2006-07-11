//
// ActiveTest.h
//
// $Id: //poco/1.1.0/CppUnit/WinTestRunner/src/ActiveTest.h#1 $
//


#ifndef ActiveTest_INCLUDED
#define ActiveTest_INCLUDED


#ifndef CppUnit_CppUnit_INCLUDED
#include "CppUnit/CppUnit.h"
#endif
#ifndef CppUnit_TestDecorator_INCLUDED
#include "CppUnit/TestDecorator.h"
#endif
#include <afxmt.h>


CppUnit_BEGIN


/* A Microsoft-specific active test
 *
 * An active test manages its own
 * thread of execution.  This one
 * is very simple and only sufficient
 * for the limited use we put it through
 * in the TestRunner.  It spawns a thread
 * on run (TestResult *) and signals
 * completion of the test.
 *
 * We assume that only one thread
 * will be active at once for each
 * instance.
 *
 */
class ActiveTest: public TestDecorator
{
public:
	ActiveTest(Test* test);
	~ActiveTest();

    void run(TestResult* result);

protected:
    HANDLE      _threadHandle;
    CEvent      _runCompleted;
    TestResult* _currentTestResult;

    void run ();
    void setTestResult(TestResult* result);
    static UINT threadFunction(LPVOID thisInstance);
};


// Construct the active test
inline ActiveTest::ActiveTest(Test *test): TestDecorator(test)
{
	_currentTestResult = NULL; 
	_threadHandle = INVALID_HANDLE_VALUE;
}


// Pend until the test has completed
inline ActiveTest::~ActiveTest()
{
	CSingleLock(&_runCompleted, TRUE); 
	CloseHandle(_threadHandle);
}


// Set the test result that we are to run
inline void ActiveTest::setTestResult(TestResult* result)
{
	_currentTestResult = result; 
}


// Run our test result
inline void ActiveTest::run()
{
	TestDecorator::run(_currentTestResult);
}


CppUnit_END


#endif // ActiveTest_INCLUDED


