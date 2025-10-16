#ifndef STRINGCALCULATOR_H
#define STRINGCALCULATOR_H

#include <string>
#include <vector>

class StringCalculator {
public:
    int Add(const std::string &numbers);

private:
    std::string getDelimiter(std::string &numbers);
    std::vector<std::string> split(const std::string &s, const std::string &delims);
    int toInt(const std::string &token, std::vector<int> &negatives);
    void throwIfNegatives(const std::vector<int> &negatives);
};

#endif
