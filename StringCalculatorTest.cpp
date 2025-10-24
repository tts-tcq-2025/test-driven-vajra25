#include "StringCalculator.h"
#include <cassert>
#include <iostream>
#include <stdexcept>

int main() {
    StringCalculator calc;

    // Step 1: empty string
    assert(calc.Add("") == 0);

    // Step 2: single number
    assert(calc.Add("1") == 1);

    // Step 3: two numbers
    assert(calc.Add("1,2") == 3);

    // Step 4: newlines as separators
    assert(calc.Add("1\n2,3") == 6);

    // Step 5: custom delimiter
    assert(calc.Add("//;\n1;2") == 3);

    // Step 6: long delimiter
    assert(calc.Add("//[***]\n1***2***3") == 6);

    // Step 7: ignore numbers >1000
    assert(calc.Add("2,1001") == 2);

    // Step 8: negatives
    try {
        calc.Add("1,-2,3,-4");
        assert(false); // should not reach
    } catch (const std::invalid_argument& e) {
        std::string msg = e.what();
        assert(msg.find("negatives not allowed") != std::string::npos);
    }

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}
