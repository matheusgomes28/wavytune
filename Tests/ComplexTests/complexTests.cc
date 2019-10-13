#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING
#include <gtest/gtest.h>
#include "Fourier/complex.h"


TEST(ComplexTests, TestingOperators)
{
	Complex a(1, 1);
	Complex b(2, 2);

	Complex c = a + b;
	EXPECT_EQ(c, Complex(3, 3));
}