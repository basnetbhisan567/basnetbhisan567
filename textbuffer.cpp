#include "TextBuffer.h"
#include <iostream>

TextBuffer::TextBuffer() {
    head = tail = nullptr;
    cursor = nullptr;
    cursorRow = cursorCol = 0;
}

void TextBuffer::insertChar(char c) {
    TextNode* newNode = new TextNode(c);

    if (head == nullptr) {
        // First character
        head = tail = newNode;
        cursor = newNode;  // Cursor after this character
    } else if (cursor == nullptr) {
        // Insert at beginning
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
        cursor = newNode;
    } else {
        // Insert in middle or end
        newNode->prev = cursor;
        newNode->next = cursor->next;

        if (cursor->next != nullptr) {
            cursor->next->prev = newNode;
        }
        cursor->next = newNode;

        if (cursor == tail) {
            tail = newNode;
        }
        cursor = newNode;
    }

    if (c == '\n') {
        cursorRow++;
        cursorCol = 0;
    } else {
        cursorCol++;
    }
}

void TextBuffer::deleteChar() {
    if (cursor == nullptr) return;

    TextNode* toDelete = cursor;

    if (cursor->prev != nullptr) {
        cursor->prev->next = cursor->next;
    } else {
        head = cursor->next;
    }

    if (cursor->next != nullptr) {
        cursor->next->prev = cursor->prev;
    } else {
        tail = cursor->prev;
    }

    cursor = cursor->prev;
    delete toDelete;
}

void TextBuffer::moveLeft() {
    if (cursor == nullptr) return;

    if (cursor->prev != nullptr) {
        cursor = cursor->prev;
        cursorCol--;
    }
}

void TextBuffer::moveRight() {
    if (cursor == nullptr) {
        if (head != nullptr) cursor = head;
    } else if (cursor->next != nullptr) {
        cursor = cursor->next;
        cursorCol++;
    }
}

void TextBuffer::display() const {
    TextNode* current = head;

    std::cout << "Text Buffer Content:\n";
    std::cout << "====================\n";

    while (current != nullptr) {
        if (current == cursor) {
            std::cout << "|";  // Cursor indicator
        }
        std::cout << current->data;
        current = current->next;
    }
    if (cursor == nullptr) std::cout << "|";
    std::cout << "\n====================\n";
}

std::string TextBuffer::getText() const {
    std::string result;
    TextNode* current = head;

    while (current != nullptr) {
        result += current->data;
        current = current->next;
    }

    return result;
}
