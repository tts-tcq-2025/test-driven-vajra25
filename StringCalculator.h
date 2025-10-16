#ifndef STRINGCALCULATOR_H
#define STRINGCALCULATOR_H

#include <string>
#include <vector>

class StringCalculator {
public:
    int Add(const std::string& numbers);

private:
    std::vector<std::string> split(const std::string& str, const std::vector<std::string>& delimiters);
    std::string extractCustomDelimiter(std::string& numbers);
};

#endif // STRINGCALCULATOR_H
