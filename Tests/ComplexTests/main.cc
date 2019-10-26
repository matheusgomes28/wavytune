/* Nothing to see here... 
#define GTEST_HAS_TR1_TUPLE 0
#define GTEST_HAS_STD_TUPLE 1
#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING
#include "stdafx.h"
#include <gtest/gtest.h>

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
*/

int main(int argc, const char** argv)
{
	const char* var = "Need to sort out the google tests at some point.";
	return 0;
}