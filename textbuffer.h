#pragma once
#include <string>

struct TextNode {
    char data;
    TextNode* prev;
    TextNode* next;

    TextNode(char c) : data(c), prev(nullptr), next(nullptr) {}
};

class TextBuffer {
private:
    TextNode* head;
    TextNode* tail;
    TextNode* cursor;  // Points to character BEFORE cursor
    int cursorRow;
    int cursorCol;

public:
    TextBuffer();

    void insertChar(char c);
    void deleteChar();
    void moveLeft();
    void moveRight();
    void display() const;
    std::string getText() const;

    // (Optional) you might later add clear(), loadFromString(), etc.
};
