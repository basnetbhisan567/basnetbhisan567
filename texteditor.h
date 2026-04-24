#pragma once
#include <string>
#include <vector>

#include "TextBuffer.h"
#include "UndoManager.h"
#include "TextSearcher.h"
#include "AutoComplete.h"
#include "FileManager.h"

class TextEditor {
private:
    TextBuffer buffer;
    UndoManager undoManager;
    TextSearcher searcher;
    AutoComplete autoComplete;
    std::string filename;

public:
    TextEditor();
    void run();
};
