#include "SyntaxHighlighter.h"
#include <cctype>
#include <sstream>

SyntaxHighlighter::SyntaxHighlighter() : language(Language::CPP) {
    initCppKeywords();
    initPythonKeywords();
    #ifdef USE_NCURSES
        initColorPairs();
    #endif
}

void SyntaxHighlighter::initCppKeywords() {
    cppKeywords = {
        "if", "else", "while", "for", "do", "switch", "case", "default",
        "break", "continue", "return", "goto", "try", "catch", "throw",
        "using", "namespace", "class", "struct", "union", "enum",
        "public", "private", "protected", "virtual", "static", "const",
        "volatile", "extern", "inline", "template", "typename", "sizeof",
        "new", "delete", "this", "nullptr", "true", "false"
    };
    
    cppTypes = {
        "void", "int", "float", "double", "char", "bool", "long", "short",
        "unsigned", "signed", "auto", "std"
    };
}

void SyntaxHighlighter::initPythonKeywords() {
    pythonKeywords = {
        "if", "elif", "else", "while", "for", "break", "continue",
        "return", "def", "class", "try", "except", "finally", "raise",
        "import", "from", "as", "with", "pass", "assert", "yield",
        "lambda", "and", "or", "not", "in", "is", "None", "True", "False"
    };
}

void SyntaxHighlighter::initColorPairs() {
    // Color pairs initialization (only used with ncurses, which is not required for this build)
}

Language SyntaxHighlighter::detectLanguage(const std::string& filename) {
    if (filename.find(".cpp") != std::string::npos || 
        filename.find(".cc") != std::string::npos ||
        filename.find(".cxx") != std::string::npos ||
        filename.find(".h") != std::string::npos) {
        return Language::CPP;
    } else if (filename.find(".py") != std::string::npos) {
        return Language::PYTHON;
    }
    return Language::UNKNOWN;
}

void SyntaxHighlighter::setLanguage(const std::string& filename) {
    language = detectLanguage(filename);
}

TokenType SyntaxHighlighter::identifyToken(const std::string& token, bool afterHash) {
    if (token.empty()) return TokenType::NORMAL;
    
    // Check for numbers
    if (std::isdigit(token[0]) || (token[0] == '.' && token.length() > 1)) {
        return TokenType::NUMBER;
    }
    
    // Check for preprocessor (C++)
    if (afterHash) {
        return TokenType::PREPROCESSOR;
    }
    
    // Check for keywords and types
    if (language == Language::CPP) {
        if (cppKeywords.count(token)) return TokenType::KEYWORD;
        if (cppTypes.count(token)) return TokenType::TYPE;
    } else if (language == Language::PYTHON) {
        if (pythonKeywords.count(token)) return TokenType::KEYWORD;
    }
    
    // Check for operators
    if (token.length() == 1 && std::string("+-*/%=<>!&|^~()[]{}.,;:?").find(token[0]) != std::string::npos) {
        return TokenType::OPERATOR;
    }
    
    return TokenType::NORMAL;
}

std::vector<Token> SyntaxHighlighter::tokenizeLine(const std::string& line) {
    std::vector<Token> tokens;
    std::string token;
    bool inString = false;
    bool inComment = false;
    char stringChar = 0;
    
    for (size_t i = 0; i < line.length(); ++i) {
        char ch = line[i];
        
        // Handle C++ comments
        if (!inString && i < line.length() - 1 && ch == '/' && line[i + 1] == '/') {
            tokens.push_back(Token(TokenType::COMMENT, i, line.length() - i));
            break;
        }
        
        // Handle strings
        if ((ch == '"' || ch == '\'') && (i == 0 || line[i - 1] != '\\')) {
            if (!inString) {
                inString = true;
                stringChar = ch;
                token.clear();
            } else if (ch == stringChar) {
                inString = false;
                tokens.push_back(Token(TokenType::STRING, i - token.length() - 1, token.length() + 2));
                token.clear();
                continue;
            }
        }
        
        if (inString) {
            token += ch;
            continue;
        }
        
        // Tokenize normal text
        if (std::isalnum(ch) || ch == '_') {
            token += ch;
        } else {
            if (!token.empty()) {
                TokenType type = identifyToken(token, i > 0 && line[i - 1] == '#');
                tokens.push_back(Token(type, i - token.length(), token.length()));
                token.clear();
            }
            
            if (!std::isspace(ch)) {
                TokenType opType = identifyToken(std::string(1, ch));
                tokens.push_back(Token(opType, i, 1));
            }
        }
    }
    
    if (!token.empty()) {
        TokenType type = identifyToken(token);
        tokens.push_back(Token(type, line.length() - token.length(), token.length()));
    }
    
    return tokens;
}

int SyntaxHighlighter::getColorPair(TokenType type) const {
    #ifdef USE_NCURSES
        switch (type) {
            case TokenType::KEYWORD:
                return COLOR_PAIR(1);
            case TokenType::STRING:
                return COLOR_PAIR(2);
            case TokenType::COMMENT:
                return COLOR_PAIR(3);
            case TokenType::NUMBER:
                return COLOR_PAIR(4);
            case TokenType::OPERATOR:
                return COLOR_PAIR(5);
            case TokenType::PREPROCESSOR:
            case TokenType::FUNCTION:
                return COLOR_PAIR(6);
            default:
                return COLOR_PAIR(0);
        }
    #else
        // For Windows Console or other platforms, just return the type value
        return (int)type;
    #endif
}
