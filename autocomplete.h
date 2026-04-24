#pragma once
#include <string>
#include <vector>

struct TrieNode {
    TrieNode* children[26];
    bool isWordEnd;

    TrieNode() : isWordEnd(false) {
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
    }
};

class AutoComplete {
private:
    TrieNode* root;

    void insertWord(const std::string& word);
    void collectWords(TrieNode* node,
                      const std::string& prefix,
                      std::vector<std::string>& suggestions);

public:
    AutoComplete();
    std::vector<std::string> getSuggestions(const std::string& prefix);
};
