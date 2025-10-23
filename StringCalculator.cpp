#include "StringCalculator.h"
#include <string>
#include <sstream>
#include <vector>
#include <stdexcept>

using namespace std;

namespace {
    // Extracts delimiter and content separately
    string getDelimiter(const string& input, string& content) {
        if (input.rfind("//", 0) == 0) {
            size_t newline = input.find('\n');
            string header = input.substr(2, newline - 2);
            if (header.size() > 1 && header.front() == '[' && header.back() == ']')
                header = header.substr(1, header.size() - 2);
            content = input.substr(newline + 1);
            return header;
        }
        content = input;
        return ",|\n"; // default delimiters: comma or newline
    }

    // Splits the input string into tokens using the given delimiter
    vector<string> splitTokens(const string& input, const string& delimiter) {
        vector<string> tokens;
        string temp = input;
        size_t pos = 0;

        while ((pos = temp.find(delimiter)) != string::npos)
            temp.replace(pos, delimiter.size(), ",");

        string token;
        stringstream ss(temp);
        while (getline(ss, token, ',')) {
            if (!token.empty()) tokens.push_back(token);
        }
        return tokens;
    }

    // Validates if any negative numbers exist
    void validateNegatives(const vector<int>& nums) {
        string negatives;
        for (int n : nums)
            if (n < 0) negatives += (negatives.empty() ? "" : ",") + to_string(n);
        if (!negatives.empty())
            throw invalid_argument("negatives not allowed " + negatives);
    }
}

// Main Add function
int StringCalculator::Add(const string& numbers) {
    if (numbers.empty()) return 0;

    string content;
    string delimiter = getDelimiter(numbers, content);
    vector<string> tokens = splitTokens(content, delimiter);

    vector<int> nums;
    for (const auto& t : tokens) {
        int val = stoi(t);
        if (val <= 1000) nums.push_back(val);
    }

    validateNegatives(nums);

    int sum = 0;
    for (int n : nums) sum += n;
    return sum;
}
