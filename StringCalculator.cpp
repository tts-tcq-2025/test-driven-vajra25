#include "StringCalculator.h"
#include <sstream>
#include <stdexcept>
#include <algorithm>

int StringCalculator::Add(const std::string& input)
{
    if (input.empty()) return 0;

    std::string numbers = input;
    std::vector<std::string> delimiters = { ",", "\n" };

    if (numbers.rfind("//", 0) == 0) {
        std::string custom = extractCustomDelimiter(numbers);
        delimiters = { custom };
    }

    std::vector<std::string> tokens = split(numbers, delimiters);
    return computeSum(tokens);
}

// Extract delimiter (supports single or multi-length like //[***]\n)
std::string StringCalculator::extractCustomDelimiter(std::string& numbers)
{
    size_t newlinePos = numbers.find('\n');
    std::string delimiter;

    if (numbers[2] == '[') {
        size_t start = numbers.find('[') + 1;
        size_t end = numbers.find(']');
        delimiter = numbers.substr(start, end - start);
    } else {
        delimiter = numbers.substr(2, newlinePos - 2);
    }

    numbers = numbers.substr(newlinePos + 1);
    return delimiter;
}

// Split by all delimiters
std::vector<std::string> StringCalculator::split(const std::string& str, const std::vector<std::string>& delimiters)
{
    std::vector<std::string> result;
    size_t start = 0;

    while (start < str.size()) {
        size_t minPos = std::string::npos;
        std::string usedDelim;

        for (const auto& d : delimiters) {
            size_t pos = str.find(d, start);
            if (pos != std::string::npos && pos < minPos) {
                minPos = pos;
                usedDelim = d;
            }
        }

        if (minPos == std::string::npos) {
            result.push_back(str.substr(start));
            break;
        }

        result.push_back(str.substr(start, minPos - start));
        start = minPos + usedDelim.size();
    }

    return result;
}

// Compute sum with rules: negatives → exception, >1000 → ignored
int StringCalculator::computeSum(const std::vector<std::string>& tokens)
{
    int sum = 0;
    std::vector<int> negatives;

    for (const auto& token : tokens) {
        if (token.empty()) continue;
        int num = std::stoi(token);
        if (num < 0) negatives.push_back(num);
        if (num <= 1000) sum += num;
    }

    checkNegatives(negatives);
    return sum;
}

void StringCalculator::checkNegatives(const std::vector<int>& negatives)
{
    if (negatives.empty()) return;

    std::ostringstream oss;
    oss << "negatives not allowed: ";
    for (size_t i = 0; i < negatives.size(); ++i) {
        oss << negatives[i];
        if (i < negatives.size() - 1) oss << ", ";
    }
    throw std::invalid_argument(oss.str());
}
