#include "StringCalculator.h"
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <cctype>

int StringCalculator::Add(const std::string& input)
{
    if (input.empty()) return 0;

    std::string numbers = input;
    std::vector<std::string> delimiters = { ",", "\n" };

    // Step 1: Handle custom delimiter
    if (numbers.rfind("//", 0) == 0) {
        std::string delimiter = extractCustomDelimiter(numbers);
        delimiters = { delimiter };
    }

    // Step 2: Split numbers by delimiters
    std::vector<std::string> tokens = split(numbers, delimiters);
    std::vector<int> negatives;
    int sum = 0;

    for (auto& token : tokens) {
        if (token.empty()) continue;
        int num = std::stoi(token);
        if (num < 0) negatives.push_back(num);
        if (num <= 1000) sum += num;
    }

    if (!negatives.empty()) {
        std::ostringstream oss;
        oss << "negatives not allowed: ";
        for (size_t i = 0; i < negatives.size(); ++i) {
            oss << negatives[i];
            if (i < negatives.size() - 1) oss << ", ";
        }
        throw std::invalid_argument(oss.str());
    }

    return sum;
}

// Extracts delimiter from input of format: //;\n1;2 or //[***]\n1***2***3
std::string StringCalculator::extractCustomDelimiter(std::string& numbers)
{
    std::string delimiter;
    size_t newlinePos = numbers.find('\n');

    if (numbers[2] == '[') {
        // Handle multiple characters delimiters
        size_t start = numbers.find('[') + 1;
        size_t end = numbers.find(']');
        delimiter = numbers.substr(start, end - start);
    } else {
        // Single character delimiter
        delimiter = numbers.substr(2, newlinePos - 2);
    }

    numbers = numbers.substr(newlinePos + 1);
    return delimiter;
}

// Split string using multiple delimiters
std::vector<std::string> StringCalculator::split(const std::string& str, const std::vector<std::string>& delimiters)
{
    std::vector<std::string> tokens;
    size_t start = 0, end = 0;
    std::string token;
    size_t len = str.length();

    while (start < len) {
        end = len;
        size_t minPos = std::string::npos;

        // Find the next occurrence of any delimiter
        for (const auto& delim : delimiters) {
            size_t pos = str.find(delim, start);
            if (pos != std::string::npos && pos < minPos)
                minPos = pos;
        }

        if (minPos != std::string::npos) {
            token = str.substr(start, minPos - start);
            start = minPos + 1;
            // Adjust for multi-char delimiter
            for (const auto& delim : delimiters) {
                if (str.substr(minPos, delim.size()) == delim) {
                    start = minPos + delim.size();
                    break;
                }
            }
        } else {
            token = str.substr(start);
            start = len;
        }

        if (!token.empty())
            tokens.push_back(token);
    }

    return tokens;
}
