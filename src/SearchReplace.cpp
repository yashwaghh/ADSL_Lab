#include "SearchReplace.h"
#include <algorithm>

SearchReplace::SearchReplace() {}

std::vector<SearchResult> SearchReplace::findAll(const std::vector<std::string>& lines) {
    std::vector<SearchResult> results;
    
    if (searchTerm.empty()) return results;
    
    for (int i = 0; i < lines.size(); ++i) {
        const std::string& line = lines[i];
        size_t pos = 0;
        
        while ((pos = line.find(searchTerm, pos)) != std::string::npos) {
            results.push_back({i, (int)pos, (int)searchTerm.length()});
            pos += 1;
        }
    }
    
    return results;
}

SearchResult SearchReplace::findNext(const std::vector<std::string>& lines, 
                                      int startLine, int startCol) {
    if (searchTerm.empty()) return {-1, -1, -1};
    
    for (int i = startLine; i < lines.size(); ++i) {
        const std::string& line = lines[i];
        size_t searchStart = (i == startLine) ? startCol : 0;
        size_t pos = line.find(searchTerm, searchStart);
        
        if (pos != std::string::npos) {
            return {i, (int)pos, (int)searchTerm.length()};
        }
    }
    
    // Wrap around search
    for (int i = 0; i < startLine; ++i) {
        const std::string& line = lines[i];
        size_t pos = line.find(searchTerm);
        
        if (pos != std::string::npos) {
            return {i, (int)pos, (int)searchTerm.length()};
        }
    }
    
    return {-1, -1, -1};
}

SearchResult SearchReplace::findPrevious(const std::vector<std::string>& lines, 
                                         int startLine, int startCol) {
    if (searchTerm.empty()) return {-1, -1, -1};
    
    for (int i = startLine; i >= 0; --i) {
        const std::string& line = lines[i];
        size_t searchEnd = (i == startLine) ? startCol : line.length();
        size_t pos = line.rfind(searchTerm, searchEnd > 0 ? searchEnd - 1 : 0);
        
        if (pos != std::string::npos) {
            return {i, (int)pos, (int)searchTerm.length()};
        }
    }
    
    // Wrap around search
    for (int i = lines.size() - 1; i > startLine; --i) {
        const std::string& line = lines[i];
        size_t pos = line.rfind(searchTerm);
        
        if (pos != std::string::npos) {
            return {i, (int)pos, (int)searchTerm.length()};
        }
    }
    
    return {-1, -1, -1};
}

std::string SearchReplace::replaceAll(std::vector<std::string>& lines) {
    int count = 0;
    
    for (auto& line : lines) {
        size_t pos = 0;
        while ((pos = line.find(searchTerm, pos)) != std::string::npos) {
            line.replace(pos, searchTerm.length(), replaceTerm);
            pos += replaceTerm.length();
            count++;
        }
    }
    
    return "Replaced " + std::to_string(count) + " occurrences";
}

bool SearchReplace::replaceNext(std::vector<std::string>& lines, int& curLine, int& curCol) {
    SearchResult result = findNext(lines, curLine, curCol);
    
    if (result.line != -1) {
        lines[result.line].replace(result.column, result.length, replaceTerm);
        curLine = result.line;
        curCol = result.column + replaceTerm.length();
        return true;
    }
    
    return false;
}
