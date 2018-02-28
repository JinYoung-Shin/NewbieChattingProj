#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "messenger.h"

class SendTest: public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(CalculatorTest);
    
	CPPUNIT_TEST( test ); // Test List
    
	CPPUNIT_TEST_SUITE_END();
	
public:
	SendTest();
	~SendTest();

	void setUp();
	void tearDown();
	
	// Functions to be tested
	
};