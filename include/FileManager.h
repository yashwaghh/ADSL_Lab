#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>

class FileManager {
private:
    std::string currentFilePath;
    bool isModified;
    
public:
    FileManager();
    
    bool loadFile(const std::string& filepath, std::vector<std::string>& lines);
    bool saveFile(const std::string& filepath, const std::vector<std::string>& lines);
    bool saveAsFile(const std::string& filepath, const std::vector<std::string>& lines);
    
    std::string getCurrentFile() const { return currentFilePath; }
    void setCurrentFile(const std::string& path) { currentFilePath = path; }
    
    bool getIsModified() const { return isModified; }
    void setIsModified(bool modified) { isModified = modified; }
    
    std::string getFileExtension(const std::string& filepath) const;
    std::string getText() const;
};

#endif
