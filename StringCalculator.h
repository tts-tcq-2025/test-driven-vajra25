#ifndef STRINGCALCULATOR_H
#define STRINGCALCULATOR_H

#include <string>
#include <vector>

class StringCalculator {
public:
    int Add(const std::string& numbers);

private:
    std::string extractCustomDelimiter(std::string& numbers);
    std::vector<std::string> split(const std::string& str, const std::vector<std::string>& delimiters);
    int computeSum(const std::vector<std::string>& tokens);
    void checkNegatives(const std::vector<int>& negatives);
};

#endif // STRINGCALCULATOR_H
