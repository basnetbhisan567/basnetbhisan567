#include "FileManager.h"
#include <fstream>

bool FileManager::saveToFile(const std::string& filename, const std::string& content) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    file << content;
    file.close();
    return true;
}

std::string FileManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return "";
    }

    std::string content;
    std::string line;
    while (std::getline(file, line)) {
        content += line + "\n";
    }
    file.close();

    if (!content.empty() && content.back() == '\n') {
        content.pop_back();
    }

    return content;
}
