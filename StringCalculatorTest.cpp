#include "StringCalculator.h"
#include <cassert>
#include <iostream>

int main() {
    StringCalculator calc;

    assert(calc.Add("") == 0);          // Empty string
    assert(calc.Add("1") == 1);         // Single number
    assert(calc.Add("1,2") == 3);       // Two numbers
    assert(calc.Add("1\n2,3") == 6);    // Newline as delimiter
    assert(calc.Add("//;\n1;2") == 3);  // Custom delimiter
    assert(calc.Add("//[***]\n1***2***3") == 6); // Long delimiter
    assert(calc.Add("2,1001") == 2);    // Ignore >1000

    // Check negatives
    try {
        calc.Add("1,-2,3,-4");
        assert(false);
    } catch (const std::invalid_argument& e) {
        std::string msg = e.what();
        assert(msg.find("negatives not allowed") != std::string::npos);
    }

    std::cout << "✅ All tests passed!" << std::endl;
    return 0;
}
