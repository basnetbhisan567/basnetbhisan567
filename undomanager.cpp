#include "UndoManager.h"

void UndoManager::recordAction(const std::string& type, char c, int pos) {
    EditAction action(type, c, pos);
    undoStack.push(action);

    // Clear redo stack when new action is recorded
    while (!redoStack.empty()) redoStack.pop();
}

EditAction UndoManager::undo() {
    if (undoStack.empty()) {
        return EditAction("none", ' ', -1);
    }

    EditAction action = undoStack.top();
    undoStack.pop();
    redoStack.push(action);
    return action;
}

EditAction UndoManager::redo() {
    if (redoStack.empty()) {
        return EditAction("none", ' ', -1);
    }

    EditAction action = redoStack.top();
    redoStack.pop();
    undoStack.push(action);
    return action;
}

void UndoManager::clear() {
    while (!undoStack.empty()) undoStack.pop();
    while (!redoStack.empty()) redoStack.pop();
}
