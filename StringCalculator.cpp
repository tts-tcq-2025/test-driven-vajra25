#include "StringCalculator.h"
#include <sstream>
#include <stdexcept>

std::string StringCalculator::getDelimiter(std::string &numbers) {
    if (numbers.rfind("//", 0) != 0) return ",\n";
    size_t n = numbers.find('\n');
    std::string d = numbers.substr(2, n - 2);
    if (d.size() > 2 && d[0] == '[' && d.back() == ']')
        d = d.substr(1, d.size() - 2);
    numbers = numbers.substr(n + 1);
    return d;
}

std::vector<std::string> StringCalculator::split(const std::string &s, const std::string &delims) {
    std::vector<std::string> out;
    size_t start = 0;
    for (size_t i = 0; i <= s.size(); ++i) {
        if (i == s.size() || delims.find(s[i]) != std::string::npos) {
            if (i > start) out.push_back(s.substr(start, i - start));
            start = i + 1;
        }
    }
    return out;
}

int StringCalculator::toInt(const std::string &token, std::vector<int> &negatives) {
    if (token.empty()) return 0;
    int n = std::stoi(token);
    if (n < 0) negatives.push_back(n);
    return (n > 1000) ? 0 : n;
}

void StringCalculator::throwIfNegatives(const std::vector<int> &negatives) {
    if (negatives.empty()) return;
    std::ostringstream oss;
    oss << "negatives not allowed: ";
    for (size_t i = 0; i < negatives.size(); ++i) {
        oss << negatives[i];
        if (i + 1 < negatives.size()) oss << ", ";
    }
    throw std::invalid_argument(oss.str());
}

int StringCalculator::Add(const std::string &input) {
    if (input.empty()) return 0;

    std::string numbers = input;
    std::string delims = getDelimiter(numbers);
    std::vector<std::string> parts = split(numbers, delims);
    std::vector<int> negatives;
    int sum = 0;

    for (const auto &p : parts)
        sum += toInt(p, negatives);

    throwIfNegatives(negatives);
    return sum;
}
