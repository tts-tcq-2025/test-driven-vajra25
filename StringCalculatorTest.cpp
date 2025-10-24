#include "StringCalculator.h"
#include <cassert>
#include <iostream>
#include <stdexcept>

int main() {
    StringCalculator calc;

    // Empty string
    assert(calc.Add("") == 0);

    // Single number
    assert(calc.Add("1") == 1);

    // Two numbers
    assert(calc.Add("1,2") == 3);

    // Newlines
    assert(calc.Add("1\n2,3") == 6);

    // Custom delimiter
    assert(calc.Add("//;\n1;2") == 3);

    // Long delimiter
    assert(calc.Add("//[***]\n1***2***3") == 6);

    // Ignore numbers >1000
    assert(calc.Add("2,1001") == 2);

    // Negatives
    try {
        calc.Add("1,-2,3,-4");
        assert(false);
    } catch (const std::invalid_argument& e) {
        std::string msg = e.what();
        assert(msg.find("negatives not allowed") != std::string::npos);
    }

    std::cout << "✅ All test cases passed!" << std::endl;
    return 0;
}
