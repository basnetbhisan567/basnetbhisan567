#pragma once
#include <string>

class FileManager {
public:
    static bool saveToFile(const std::string& filename, const std::string& content);
    static std::string loadFromFile(const std::string& filename);
};
