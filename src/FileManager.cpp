#include "FileManager.h"
#include <fstream>
#include <sstream>

FileManager::FileManager() : isModified(false) {}

bool FileManager::loadFile(const std::string& filepath, std::vector<std::string>& lines) {
    std::ifstream file(filepath);
    
    if (!file.is_open()) {
        return false;
    }
    
    lines.clear();
    std::string line;
    
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    
    if (lines.empty()) {
        lines.push_back("");
    }
    
    file.close();
    currentFilePath = filepath;
    isModified = false;
    
    return true;
}

bool FileManager::saveFile(const std::string& filepath, const std::vector<std::string>& lines) {
    std::ofstream file(filepath);
    
    if (!file.is_open()) {
        return false;
    }
    
    for (size_t i = 0; i < lines.size(); ++i) {
        file << lines[i];
        if (i < lines.size() - 1) {
            file << "\n";
        }
    }
    
    file.close();
    currentFilePath = filepath;
    isModified = false;
    
    return true;
}

bool FileManager::saveAsFile(const std::string& filepath, const std::vector<std::string>& lines) {
    return saveFile(filepath, lines);
}

std::string FileManager::getFileExtension(const std::string& filepath) const {
    size_t dotPos = filepath.find_last_of(".");
    
    if (dotPos == std::string::npos) {
        return "";
    }
    
    return filepath.substr(dotPos);
}

std::string FileManager::getText() const {
    return "";
}
