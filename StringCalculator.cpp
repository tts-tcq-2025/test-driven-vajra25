#include "StringCalculator.h"
#include <sstream>
#include <vector>
#include <stdexcept>
#include <cctype>

namespace {
    std::vector<std::string> split(const std::string& str, const std::string& delimiter) {
        std::vector<std::string> tokens;
        size_t start = 0, end;
        while ((end = str.find(delimiter, start)) != std::string::npos) {
            tokens.push_back(str.substr(start, end - start));
            start = end + delimiter.length();
        }
        tokens.push_back(str.substr(start));
        return tokens;
    }

    void checkNegatives(const std::vector<int>& nums) {
        std::vector<int> negatives;
        for (int n : nums) {
            if (n < 0) negatives.push_back(n);
        }
        if (!negatives.empty()) {
            std::ostringstream oss;
            oss << "negatives not allowed: ";
            for (size_t i = 0; i < negatives.size(); ++i) {
                if (i > 0) oss << ", ";
                oss << negatives[i];
            }
            throw std::invalid_argument(oss.str());
        }
    }
}

int StringCalculator::Add(const std::string& numbers) {
    if (numbers.empty()) return 0;

    std::string numStr = numbers;
    std::string delimiter = ",|\n";
    if (numbers.rfind("//", 0) == 0) {
        auto endPos = numbers.find('\n');
        delimiter = numbers.substr(2, endPos - 2);
        numStr = numbers.substr(endPos + 1);
        if (delimiter.size() > 2 && delimiter.front() == '[' && delimiter.back() == ']')
            delimiter = delimiter.substr(1, delimiter.size() - 2);
    }

    for (char& c : numStr)
        if (c == '\n') c = delimiter[0];

    std::vector<std::string> parts = split(numStr, std::string(1, delimiter[0]));
    std::vector<int> nums;
    for (const auto& p : parts) {
        if (p.empty()) continue;
        int val = std::stoi(p);
        if (val <= 1000) nums.push_back(val);
    }

    checkNegatives(nums);

    int sum = 0;
    for (int n : nums) sum += n;
    return sum;
}
