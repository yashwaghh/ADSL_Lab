#ifndef SEARCHREPLACE_H
#define SEARCHREPLACE_H

#include <string>
#include <vector>

struct SearchResult {
    int line;
    int column;
    int length;
};

class SearchReplace {
private:
    std::string searchTerm;
    std::string replaceTerm;
    
public:
    SearchReplace();
    
    void setSearchTerm(const std::string& term) { searchTerm = term; }
    void setReplaceTerm(const std::string& term) { replaceTerm = term; }
    
    std::vector<SearchResult> findAll(const std::vector<std::string>& lines);
    SearchResult findNext(const std::vector<std::string>& lines, int startLine, int startCol);
    SearchResult findPrevious(const std::vector<std::string>& lines, int startLine, int startCol);
    
    std::string replaceAll(std::vector<std::string>& lines);
    bool replaceNext(std::vector<std::string>& lines, int& curLine, int& curCol);
};

#endif
