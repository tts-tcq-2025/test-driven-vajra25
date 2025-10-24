#include "StringCalculator.h"
#include <cassert>
#include <iostream>

int main() {
    StringCalculator calc;

    // Step 1: Empty string
    assert(calc.Add("") == 0);

    // Step 2: Single number
    assert(calc.Add("1") == 1);

    // Step 3: Two numbers
    assert(calc.Add("1,2") == 3);

    // Step 4: Newline between numbers
    assert(calc.Add("1\n2,3") == 6);

    // Step 5: Custom delimiter
    assert(calc.Add("//;\n1;2") == 3);

    // Step 6: Custom long delimiter
    assert(calc.Add("//[***]\n1***2***3") == 6);

    // Step 7: Ignore >1000
    assert(calc.Add("2,1001") == 2);

    // Step 8: Negatives (should throw)
    try {
        calc.Add("1,-2,3,-4");
        assert(false); // should not reach here
    } catch (const std::invalid_argument& e) {
        std::string msg = e.what();
        assert(msg.find("negatives not allowed") != std::string::npos);
    }

    std::cout << "✅ All TDD test cases passed successfully!" << std::endl;
    return 0;
}
