#include "StringCalculator.h"
#include <sstream>
#include <stdexcept>
#include <algorithm>

std::string StringCalculator::getDelimiter(std::string &numbers) {
    if (numbers.substr(0, 2) == "//") {
        size_t pos = numbers.find('\n');
        std::string delimiter = numbers.substr(2, pos - 2);
        numbers = numbers.substr(pos + 1);
        return delimiter;
    }
    return ",";
}

std::vector<std::string> StringCalculator::split(const std::string &s, const std::string &delims) {
    std::vector<std::string> result;
    size_t last = 0;
    size_t next = 0;
    while ((next = s.find_first_of(delims, last)) != std::string::npos) {
        result.push_back(s.substr(last, next - last));
        last = next + 1;
    }
    result.push_back(s.substr(last));
    return result;
}

int StringCalculator::toInt(const std::string &token, std::vector<int> &negatives) {
    if (token.empty()) return 0;
    int num = std::stoi(token);
    if (num < 0) negatives.push_back(num);
    return (num > 1000) ? 0 : num;
}

void StringCalculator::throwIfNegatives(const std::vector<int> &negatives) {
    if (!negatives.empty()) {
        std::ostringstream oss;
        oss << "negatives not allowed:";
        for (int n : negatives) oss << " " << n;
        throw std::runtime_error(oss.str());
    }
}

int StringCalculator::Add(const std::string &numbers) {
    if (numbers.empty()) return 0;
    std::string nums = numbers;
    std::string delimiter = getDelimiter(nums);
    std::vector<std::string> tokens = split(nums, delimiter + "\n,");
    std::vector<int> negatives;
    int sum = 0;
    for (const auto &token : tokens) {
        sum += toInt(token, negatives);
    }
    throwIfNegatives(negatives);
    return sum;
}
