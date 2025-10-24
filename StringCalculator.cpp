#include "StringCalculator.h"
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>

int StringCalculator::Add(const std::string& numbers) {
    if (numbers.empty()) return 0;

    std::string delimiter = ",";
    std::string content = numbers;

    // Custom delimiter
    if (numbers.size() >= 2 && numbers[0] == '/' && numbers[1] == '/') {
        size_t newlinePos = numbers.find('\n');
        delimiter = numbers.substr(2, newlinePos - 2);
        content = numbers.substr(newlinePos + 1);

        // Remove brackets for long delimiter
        if (delimiter.size() > 2 && delimiter.front() == '[' && delimiter.back() == ']')
            delimiter = delimiter.substr(1, delimiter.size() - 2);
    }

    // Replace newlines with delimiter
    for (size_t i = 0; i < content.size(); ++i) {
        if (content[i] == '\n') content[i] = delimiter[0];
    }

    // Split and convert to integers
    std::vector<int> nums;
    std::stringstream ss(content);
    std::string token;
    while (getline(ss, token, delimiter[0])) {
        if (token.empty()) continue;
        int val = std::stoi(token);
        if (val <= 1000) nums.push_back(val);
    }

    // Check negatives
    std::string negs;
    for (size_t i = 0; i < nums.size(); ++i) {
        if (nums[i] < 0) {
            if (!negs.empty()) negs += ",";
            negs += std::to_string(nums[i]);
        }
    }
    if (!negs.empty()) throw std::invalid_argument("negatives not allowed: " + negs);

    // Sum
    int sum = 0;
    for (int n : nums) sum += n;
    return sum;
}
