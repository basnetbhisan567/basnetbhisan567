#include "TextSearcher.h"
#include <algorithm>

std::vector<int> TextSearcher::computeLPS(const std::string& pattern) {
    int n = pattern.length();
    std::vector<int> lps(n, 0);
    int len = 0;
    int i = 1;

    while (i < n) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }

    return lps;
}

std::vector<int> TextSearcher::kmpSearch(const std::string& text,
                                         const std::string& pattern) {
    std::vector<int> positions;
    if (pattern.empty()) return positions;

    std::vector<int> lps = computeLPS(pattern);
    int i = 0;  // index for text
    int j = 0;  // index for pattern
    int n = text.length();
    int m = pattern.length();

    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == m) {
            positions.push_back(i - j);
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }

    return positions;
}

std::string TextSearcher::replaceAll(const std::string& text,
                                     const std::string& oldStr,
                                     const std::string& newStr) {
    std::vector<int> positions = kmpSearch(text, oldStr);
    if (positions.empty()) return text;

    std::string result;
    int lastPos = 0;

    for (int pos : positions) {
        result += text.substr(lastPos, pos - lastPos);
        result += newStr;
        lastPos = pos + static_cast<int>(oldStr.length());
    }
    result += text.substr(lastPos);

    return result;
}

std::vector<int> TextSearcher::boyerMooreSearch(const std::string& text,
                                                const std::string& pattern) {
    std::vector<int> positions;
    int n = text.length();
    int m = pattern.length();

    if (m == 0) return positions;

    // Bad character heuristic table
    std::vector<int> badChar(256, -1);
    for (int i = 0; i < m; i++) {
        badChar[static_cast<unsigned char>(pattern[i])] = i;
    }

    int shift = 0;
    while (shift <= n - m) {
        int j = m - 1;

        while (j >= 0 && pattern[j] == text[shift + j]) {
            j--;
        }

        if (j < 0) {
            positions.push_back(shift);
            shift += (shift + m < n) ? m - badChar[static_cast<unsigned char>(text[shift + m])] : 1;
        } else {
            shift += std::max(1, j - badChar[static_cast<unsigned char>(text[shift + j])]);
        }
    }

    return positions;
}
