#pragma once
#include <stack>
#include <string>

struct EditAction {
    std::string type;  // "insert" or "delete"
    char character;
    int position;      // Simplified position for now

    EditAction(std::string t, char c, int p)
        : type(std::move(t)), character(c), position(p) {}
};

class UndoManager {
private:
    std::stack<EditAction> undoStack;
    std::stack<EditAction> redoStack;

public:
    void recordAction(const std::string& type, char c, int pos);
    EditAction undo();
    EditAction redo();
    void clear();
};
