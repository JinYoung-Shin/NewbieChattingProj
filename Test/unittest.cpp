#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
	
#ifdef _DEBUG
#pragma comment(lib, "cppunitd.lib")
#else
#pragma comment(lib, "cppunit.lib")
#endif


// 전체 test클래스를 테스트할지의 여부.
// #define FULL_TEST

int main(int argc, char* argv[])
{
    // Adds the test to the list of test to run
    CPPUNIT_NS::TextUi::TestRunner runner;

#ifdef FULL_TEST
    // Get the top level suite from the registry
    CPPUNIT_NS::Test* suite = CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest();


    runner.addTest( suite );

    // Change the default outputter to a compiler error format outputter
    runner.setOutputter( new CPPUNIT_NS::CompilerOutputter( &runner.result(),
        CPPUNIT_NS::stdCOut() ));
#else
    // 특정 테스트클래스만 테스트하고 싶을때 여기처럼
    // 특정 테스트클래스만을 suite로 만들어서 사용합니다.
    RecvTest test;
    runner.addTest( test.suite() );

    // Change the default outputter to a compiler error format outputter
    runner.setOutputter( new CPPUNIT_NS::CompilerOutputter( &runner.result(),
        CPPUNIT_NS::stdCOut() ));
#endif

    // Run the test.
    bool wasSucessful = runner.run();

    // Return error code 1 if the one of test failed.
    return wasSucessful ? 0 : 1;
}