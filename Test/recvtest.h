#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "messenger.h"

class RecvTest: public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(CalculatorTest);
    
	CPPUNIT_TEST( test ); // Test List
    
	CPPUNIT_TEST_SUITE_END();
	
public:
	RecvTest();
	~RecvTest();

	void setUp();
	void tearDown();
	
	void test();
	
	// Functions to be tested
	
};