#pragma once
#include <string>
#include <vector>

class TextSearcher {
private:
    std::vector<int> computeLPS(const std::string& pattern);

public:
    std::vector<int> kmpSearch(const std::string& text, const std::string& pattern);
    std::string replaceAll(const std::string& text,
                           const std::string& oldStr,
                           const std::string& newStr);
    std::vector<int> boyerMooreSearch(const std::string& text,
                                      const std::string& pattern);
};
