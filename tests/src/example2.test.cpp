#include <boost/test/unit_test.hpp>

#define BOOST_TEST_MODULE TestExample2

BOOST_AUTO_TEST_CASE(Example2Success)
{
	bool value = true;

	BOOST_CHECK_EQUAL(true, value);
}