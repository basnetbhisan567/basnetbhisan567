#include "AutoComplete.h"
#include <cctype>

AutoComplete::AutoComplete() {
    root = new TrieNode();

    // Preload with some common words
    insertWord("int");
    insertWord("float");
    insertWord("double");
    insertWord("char");
    insertWord("void");
    insertWord("for");
    insertWord("while");
    insertWord("if");
    insertWord("else");
    insertWord("return");
    insertWord("class");
    insertWord("struct");
    insertWord("public");
    insertWord("private");
    insertWord("include");
    insertWord("using");
    insertWord("namespace");
    insertWord("std");
    insertWord("cout");
    insertWord("cin");
}

void AutoComplete::insertWord(const std::string& word) {
    TrieNode* current = root;
    for (char c : word) {
        int index = std::tolower(static_cast<unsigned char>(c)) - 'a';
        if (index < 0 || index >= 26) continue;

        if (!current->children[index]) {
            current->children[index] = new TrieNode();
        }
        current = current->children[index];
    }
    current->isWordEnd = true;
}

void AutoComplete::collectWords(TrieNode* node,
                                const std::string& prefix,
                                std::vector<std::string>& suggestions) {
    if (node->isWordEnd) {
        suggestions.push_back(prefix);
    }

    for (int i = 0; i < 26; i++) {
        if (node->children[i]) {
            char c = 'a' + i;
            collectWords(node->children[i], prefix + c, suggestions);
        }
    }
}

std::vector<std::string> AutoComplete::getSuggestions(const std::string& prefix) {
    std::vector<std::string> suggestions;
    TrieNode* current = root;

    for (char c : prefix) {
        int index = std::tolower(static_cast<unsigned char>(c)) - 'a';
        if (index < 0 || index >= 26 || !current->children[index]) {
            return suggestions;
        }
        current = current->children[index];
    }

    collectWords(current, prefix, suggestions);
    return suggestions;
}
