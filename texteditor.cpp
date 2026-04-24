#include "TextEditor.h"
#include <iostream>

TextEditor::TextEditor() {
    filename = "untitled.txt";
}

void TextEditor::run() {
    char command;
    bool running = true;

    std::cout << "=== SIMPLE TEXT EDITOR ===\n";
    std::cout << "Commands:\n";
    std::cout << "  i - Insert mode\n";
    std::cout << "  d - Delete character\n";
    std::cout << "  l - Move cursor left\n";
    std::cout << "  r - Move cursor right\n";
    std::cout << "  s - Save to file\n";
    std::cout << "  o - Open file\n";
    std::cout << "  f - Find text\n";
    std::cout << "  a - Auto-complete\n";
    std::cout << "  u - Undo (not fully implemented)\n";
    std::cout << "  z - Redo (not fully implemented)\n";
    std::cout << "  p - Print buffer\n";
    std::cout << "  q - Quit\n";
    std::cout << "=========================\n";

    while (running) {
        std::cout << "\nCommand: ";
        std::cin >> command;
        std::cin.ignore();  // Clear newline

        switch (command) {
            case "i"[0]: {
                std::cout << "Enter text (end with ~): ";
                std::string input;
                std::getline(std::cin, input, '~');

                for (char c : input) {
                    if (c == '~') break;
                    buffer.insertChar(c);
                    undoManager.recordAction("insert", c, 0);  // Simplified position
                }
                break;
            }

            case "d"[0]:
                buffer.deleteChar();
                break;

            case "l"[0]:
                buffer.moveLeft();
                break;

            case "r"[0]:
                buffer.moveRight();
                break;

            case "s"[0]: {
                std::cout << "Enter filename to save: ";
                std::string saveFile;
                std::getline(std::cin, saveFile);

                if (FileManager::saveToFile(saveFile, buffer.getText())) {
                    std::cout << "File saved successfully!\n";
                    filename = saveFile;
                } else {
                    std::cout << "Error saving file!\n";
                }
                break;
            }

            case "o"[0]: {
                std::cout << "Enter filename to open: ";
                std::string openFile;
                std::getline(std::cin, openFile);

                std::string content = FileManager::loadFromFile(openFile);
                if (!content.empty()) {
                    TextBuffer newBuffer;
                    buffer = newBuffer;  // NOTE: this uses default copy, still simplified

                    for (char c : content) {
                        buffer.insertChar(c);
                    }
                    filename = openFile;
                    std::cout << "File loaded successfully!\n";
                } else {
                    std::cout << "Error loading file!\n";
                }
                break;
            }

            case "f"[0]: {
                std::cout << "Enter text to find: ";
                std::string pattern;
                std::getline(std::cin, pattern);

                std::vector<int> positions =
                    searcher.kmpSearch(buffer.getText(), pattern);

                if (positions.empty()) {
                    std::cout << "Pattern not found.\n";
                } else {
                    std::cout << "Found " << positions.size()
                              << " occurrence(s) at positions: ";
                    for (int pos : positions) {
                        std::cout << pos << " ";
                    }
                    std::cout << "\n";

                    std::cout << "Replace with? (leave blank to skip): ";
                    std::string replaceWith;
                    std::getline(std::cin, replaceWith);

                    if (!replaceWith.empty()) {
                        std::string newText =
                            searcher.replaceAll(buffer.getText(), pattern, replaceWith);
                        // Right now we don't reload newText into buffer (simplified)
                        std::cout << "Replacements made (buffer not yet updated in code).\n";
                    }
                }
                break;
            }

            case "a"[0]: {
                std::cout << "Enter prefix for auto-complete: ";
                std::string prefix;
                std::getline(std::cin, prefix);

                std::vector<std::string> suggestions =
                    autoComplete.getSuggestions(prefix);

                if (suggestions.empty()) {
                    std::cout << "No suggestions found.\n";
                } else {
                    std::cout << "Suggestions: ";
                    for (const std::string& word : suggestions) {
                        std::cout << word << " ";
                    }
                    std::cout << "\n";
                }
                break;
            }

            case "u"[0]:
                std::cout << "Undo not fully implemented yet.\n";
                break;

            case "z"[0]:
                std::cout << "Redo not fully implemented yet.\n";
                break;

            case "p"[0]:
                buffer.display();
                break;

            case "q"[0]:
                running = false;
                std::cout << "Goodbye!\n";
                break;

            default:
                std::cout << "Unknown command. Try again.\n";
        }
    }
}
