#include "StringCalculator.h"
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <algorithm>
using namespace std;

namespace {
    string extractDelimiter(const string& header) {
        if (header.size() > 1 && header.front() == '[' && header.back() == ']')
            return header.substr(1, header.size() - 2);
        return header;
    }

    vector<int> splitNumbers(const string& nums, const string& delimiter) {
        vector<int> result;
        string token;
        string modified = nums;
        size_t pos = 0, len = delimiter.length();

        while ((pos = modified.find(delimiter, pos)) != string::npos) {
            modified.replace(pos, len, ",");
            pos += 1;
        }

        stringstream ss(modified);
        while (getline(ss, token, ',')) {
            if (!token.empty()) {
                int val = stoi(token);
                if (val <= 1000) result.push_back(val);
            }
        }
        return result;
    }

    string joinNegatives(const vector<int>& negatives) {
        string result;
        for (size_t i = 0; i < negatives.size(); ++i) {
            if (i) result += ",";
            result += to_string(negatives[i]);
        }
        return result;
    }

    void checkNegatives(const vector<int>& values) {
        vector<int> negatives;
        for (int n : values)
            if (n < 0) negatives.push_back(n);
        if (!negatives.empty())
            throw invalid_argument("negatives not allowed " + joinNegatives(negatives));
    }

    int sumValues(const vector<int>& values) {
        int sum = 0;
        for (int v : values) sum += v;
        return sum;
    }
}

int StringCalculator::Add(const string& numbers) {
    if (numbers.empty()) return 0;

    string delimiter = ",|\n";
    string nums = numbers;

    if (numbers.rfind("//", 0) == 0) {
        size_t delimStart = numbers.find("//") + 2;
        size_t delimEnd = numbers.find("\n", delimStart);
        delimiter = extractDelimiter(numbers.substr(delimStart, delimEnd - delimStart));
        nums = numbers.substr(delimEnd + 1);
    }

    vector<int> values = splitNumbers(nums, delimiter);
    checkNegatives(values);
    return sumValues(values);
}
