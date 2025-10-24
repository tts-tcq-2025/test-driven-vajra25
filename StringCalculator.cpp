#include "StringCalculator.h"
#include <string>
#include <stdexcept>

int StringCalculator::Add(const std::string& numbers) {
    if (numbers.empty()) return 0;

    std::string delimiter = ",";
    std::string content = numbers;

    // Custom delimiter
    if (numbers.substr(0, 2) == "//") {
        size_t pos = numbers.find('\n');
        delimiter = numbers.substr(2, pos - 2);
        content = numbers.substr(pos + 1);

        // Remove brackets for long delimiters
        if (delimiter.size() > 2 && delimiter.front() == '[' && delimiter.back() == ']')
            delimiter = delimiter.substr(1, delimiter.size() - 2);
    }

    // Replace newlines with delimiter
    for (size_t i = 0; i < content.size(); ++i)
        if (content[i] == '\n') content[i] = delimiter[0];

    // Split and process numbers
    int sum = 0;
    std::string temp;
    std::string negatives;
    for (size_t i = 0; i <= content.size(); ++i) {
        if (i == content.size() || content[i] == delimiter[0]) {
            if (!temp.empty()) {
                int num = std::stoi(temp);
                if (num < 0) {
                    if (!negatives.empty()) negatives += ",";
                    negatives += std::to_string(num);
                } else if (num <= 1000) {
                    sum += num;
                }
                temp.clear();
            }
        } else {
            temp += content[i];
        }
    }

    if (!negatives.empty())
        throw std::invalid_argument("negatives not allowed: " + negatives);

    return sum;
}
