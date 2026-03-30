#ifndef SYNTAXHIGHLIGHTER_H
#define SYNTAXHIGHLIGHTER_H

#include <string>
#include <vector>
#include <unordered_set>

enum class TokenType {
    NORMAL,
    KEYWORD,
    STRING,
    COMMENT,
    NUMBER,
    OPERATOR,
    PREPROCESSOR,
    FUNCTION,
    TYPE
};

enum class Language {
    CPP,
    PYTHON,
    UNKNOWN
};

class Token {
public:
    TokenType type;
    int start;
    int length;
    
    Token(TokenType t, int s, int l) : type(t), start(s), length(l) {}
};

class SyntaxHighlighter {
private:
    Language language;
    std::unordered_set<std::string> cppKeywords;
    std::unordered_set<std::string> pythonKeywords;
    std::unordered_set<std::string> cppTypes;
    
    void initCppKeywords();
    void initPythonKeywords();
    void initColorPairs();
    Language detectLanguage(const std::string& filename);
    TokenType identifyToken(const std::string& token, bool afterHash = false);
    
public:
    SyntaxHighlighter();
    
    void setLanguage(const std::string& filename);
    std::vector<Token> tokenizeLine(const std::string& line);
    int getColorPair(TokenType type) const;
    Language getLanguage() const { return language; }
};

#endif
