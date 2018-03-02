#ifndef __TEST__
#define __TEST__
#include "gtest/gtest.h"

int main(int argc, char* argv[])
{
	/*The method is initializes the Google framework and must be called before RUN_ALL_TESTS */
	::testing::initGoogleTest(&argc, argv);
	
	/*
	RUN_ALL_TESTS automatically detects and runs all the tests defined using the TEST macro.
    It's must be called only once in the code because multiple calls lead to conflicts and,
    therefore, are not supported.
    */
	return RUN_ALL_TESTS();
}

/*
int _tmain(int argc, TCHAR* argv[])
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
*/

#endif