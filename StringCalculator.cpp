#include "StringCalculator.h"
#include <string>
#include <sstream>
#include <vector>
#include <stdexcept>

int StringCalculator::Add(const std::string& numbers) {
    if (numbers.empty()) return 0;

    std::string nums = numbers;
    std::string delimiter = ","; // default delimiter

    // Check for custom delimiter
    if (numbers.rfind("//", 0) == 0) {
        size_t newlinePos = numbers.find('\n');
        delimiter = numbers.substr(2, newlinePos - 2);
        if (delimiter.size() >= 2 && delimiter.front() == '[' && delimiter.back() == ']')
            delimiter = delimiter.substr(1, delimiter.size() - 2); // remove [ ]
        nums = numbers.substr(newlinePos + 1);
    }

    // Replace newlines and custom delimiters with comma
    for (size_t pos = 0; pos < nums.size(); ++pos) {
        if (nums[pos] == '\n') nums[pos] = ',';
    }

    size_t pos = 0;
    while ((pos = nums.find(delimiter, pos)) != std::string::npos) {
        nums.replace(pos, delimiter.length(), ",");
        pos += 1;
    }

    // Split numbers
    std::vector<int> values;
    std::string token;
    std::stringstream ss(nums);
    while (getline(ss, token, ',')) {
        if (!token.empty()) {
            int val = std::stoi(token);
            if (val <= 1000) values.push_back(val);
        }
    }

    // Check negatives
    std::string negs;
    for (int n : values) {
        if (n < 0) negs += (negs.empty() ? "" : ",") + std::to_string(n);
    }
    if (!negs.empty()) throw std::invalid_argument("negatives not allowed " + negs);

    // Sum
    int sum = 0;
    for (int n : values) sum += n;
    return sum;
}
