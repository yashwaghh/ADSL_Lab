#include "TextBuffer.h"
#include <algorithm>
#include <sstream>

TextBuffer::TextBuffer() : cursorLine(0), cursorCol(0) {
    lines.push_back("");
}

void TextBuffer::insertChar(char c) {
    if (cursorLine >= lines.size()) {
        lines.resize(cursorLine + 1, "");
    }
    
    std::string& currentLine = lines[cursorLine];
    if (cursorCol > currentLine.length()) {
        cursorCol = currentLine.length();
    }
    
    currentLine.insert(cursorCol, 1, c);
    cursorCol++;
}

void TextBuffer::insertString(const std::string& str) {
    for (char c : str) {
        if (c == '\n') {
            newLine();
        } else {
            insertChar(c);
        }
    }
}

void TextBuffer::deleteChar() {
    if (cursorLine >= lines.size()) return;
    
    std::string& currentLine = lines[cursorLine];
    if (cursorCol < currentLine.length()) {
        currentLine.erase(cursorCol, 1);
    } else if (cursorLine < lines.size() - 1) {
        // Merge with next line
        lines[cursorLine] += lines[cursorLine + 1];
        lines.erase(lines.begin() + cursorLine + 1);
    }
}

void TextBuffer::deleteBackspace() {
    if (cursorLine >= lines.size()) return;
    
    std::string& currentLine = lines[cursorLine];
    
    if (cursorCol > 0) {
        currentLine.erase(cursorCol - 1, 1);
        cursorCol--;
    } else if (cursorLine > 0) {
        // Merge with previous line
        int prevLineLen = lines[cursorLine - 1].length();
        lines[cursorLine - 1] += currentLine;
        lines.erase(lines.begin() + cursorLine);
        cursorLine--;
        cursorCol = prevLineLen;
    }
}

void TextBuffer::newLine() {
    if (cursorLine >= lines.size()) {
        lines.resize(cursorLine + 1, "");
    }
    
    std::string& currentLine = lines[cursorLine];
    std::string newLineContent = currentLine.substr(cursorCol);
    currentLine = currentLine.substr(0, cursorCol);
    
    lines.insert(lines.begin() + cursorLine + 1, newLineContent);
    cursorLine++;
    cursorCol = 0;
}

void TextBuffer::moveCursor(int line, int col) {
    cursorLine = std::max(0, std::min(line, (int)lines.size() - 1));
    if (cursorLine < lines.size()) {
        cursorCol = std::max(0, std::min(col, (int)lines[cursorLine].length()));
    } else {
        cursorCol = 0;
    }
}

void TextBuffer::cursorUp() {
    if (cursorLine > 0) {
        cursorLine--;
        if (cursorCol > lines[cursorLine].length()) {
            cursorCol = lines[cursorLine].length();
        }
    }
}

void TextBuffer::cursorDown() {
    if (cursorLine < lines.size() - 1) {
        cursorLine++;
        if (cursorCol > lines[cursorLine].length()) {
            cursorCol = lines[cursorLine].length();
        }
    }
}

void TextBuffer::cursorLeft() {
    if (cursorCol > 0) {
        cursorCol--;
    } else if (cursorLine > 0) {
        cursorLine--;
        cursorCol = lines[cursorLine].length();
    }
}

void TextBuffer::cursorRight() {
    if (cursorLine < lines.size()) {
        if (cursorCol < lines[cursorLine].length()) {
            cursorCol++;
        } else if (cursorLine < lines.size() - 1) {
            cursorLine++;
            cursorCol = 0;
        }
    }
}

void TextBuffer::cursorHome() {
    cursorCol = 0;
}

void TextBuffer::cursorEnd() {
    if (cursorLine < lines.size()) {
        cursorCol = lines[cursorLine].length();
    }
}

void TextBuffer::cursorPageUp(int pageHeight) {
    cursorLine = std::max(0, cursorLine - pageHeight);
}

void TextBuffer::cursorPageDown(int pageHeight) {
    cursorLine = std::min((int)lines.size() - 1, cursorLine + pageHeight);
}

void TextBuffer::undo() {
    if (!undoStack.empty()) {
        UndoRedoAction action = undoStack.back();
        undoStack.pop_back();
        redoStack.push_back(action);
        
        // Apply undo operation
        // This is a simplified version; a real implementation would track actual changes
    }
}

void TextBuffer::redo() {
    if (!redoStack.empty()) {
        UndoRedoAction action = redoStack.back();
        redoStack.pop_back();
        undoStack.push_back(action);
    }
}

void TextBuffer::recordAction(const std::string& action, const std::string& oldText,
                              const std::string& newText) {
    UndoRedoAction ua;
    ua.action = action;
    ua.oldText = oldText;
    ua.newText = newText;
    ua.line = cursorLine;
    ua.column = cursorCol;
    
    undoStack.push_back(ua);
    redoStack.clear();
}

std::string TextBuffer::getText() const {
    std::stringstream ss;
    for (size_t i = 0; i < lines.size(); ++i) {
        ss << lines[i];
        if (i < lines.size() - 1) {
            ss << "\n";
        }
    }
    return ss.str();
}

void TextBuffer::setText(const std::string& text) {
    lines.clear();
    std::stringstream ss(text);
    std::string line;
    
    while (std::getline(ss, line)) {
        lines.push_back(line);
    }
    
    if (lines.empty()) {
        lines.push_back("");
    }
    
    cursorLine = 0;
    cursorCol = 0;
}

bool TextBuffer::isEmpty() const {
    return lines.size() == 1 && lines[0].empty();
}

int TextBuffer::getLineLength(int lineNum) const {
    if (lineNum >= 0 && lineNum < lines.size()) {
        return lines[lineNum].length();
    }
    return 0;
}
