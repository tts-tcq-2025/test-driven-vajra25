#include "StringCalculator.h"
#include <gtest/gtest.h>

class StringCalculatorTest : public ::testing::Test {
protected:
    StringCalculator calculator;
};

TEST_F(StringCalculatorTest, EmptyStringReturnsZero) {
    EXPECT_EQ(calculator.Add(""), 0);
}

TEST_F(StringCalculatorTest, SingleNumberReturnsItself) {
    EXPECT_EQ(calculator.Add("1"), 1);
}

TEST_F(StringCalculatorTest, TwoNumbersCommaSeparated) {
    EXPECT_EQ(calculator.Add("1,2"), 3);
}

TEST_F(StringCalculatorTest, MultipleNumbersCommaSeparated) {
    EXPECT_EQ(calculator.Add("1,2,3,4"), 10);
}

TEST_F(StringCalculatorTest, HandlesNewlineAsDelimiter) {
    EXPECT_EQ(calculator.Add("1\n2,3"), 6);
}

TEST_F(StringCalculatorTest, SupportsCustomDelimiter) {
    EXPECT_EQ(calculator.Add("//;\n1;2"), 3);
}

TEST_F(StringCalculatorTest, ThrowsOnNegativeNumbers) {
    try {
        calculator.Add("1,-2,3,-4");
        FAIL() << "Expected std::invalid_argument";
    } catch (std::invalid_argument const &err) {
        EXPECT_EQ(std::string(err.what()), "negatives not allowed: -2, -4");
    } catch (...) {
        FAIL() << "Expected std::invalid_argument";
    }
}

TEST_F(StringCalculatorTest, IgnoresNumbersGreaterThan1000) {
    EXPECT_EQ(calculator.Add("2,1001"), 2);
}

TEST_F(StringCalculatorTest, SupportsDelimitersOfAnyLength) {
    EXPECT_EQ(calculator.Add("//[***]\n1***2***3"), 6);
}
