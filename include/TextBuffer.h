#ifndef TEXTBUFFER_H
#define TEXTBUFFER_H

#include <string>
#include <vector>
#include <memory>

struct UndoRedoAction {
    std::string action;
    std::string oldText;
    std::string newText;
    int line;
    int column;
};

class TextBuffer {
private:
    std::vector<std::string> lines;
    std::vector<UndoRedoAction> undoStack;
    std::vector<UndoRedoAction> redoStack;
    int cursorLine;
    int cursorCol;

public:
    TextBuffer();
    
    // Basic operations
    void insertChar(char c);
    void insertString(const std::string& str);
    void deleteChar();
    void deleteBackspace();
    void newLine();
    
    // Navigation
    void moveCursor(int line, int col);
    void cursorUp();
    void cursorDown();
    void cursorLeft();
    void cursorRight();
    void cursorHome();
    void cursorEnd();
    void cursorPageUp(int pageHeight);
    void cursorPageDown(int pageHeight);
    
    // Undo/Redo
    void undo();
    void redo();
    void recordAction(const std::string& action, const std::string& oldText, 
                      const std::string& newText);
    
    // Content access
    const std::vector<std::string>& getLines() const { return lines; }
    std::string getText() const;
    void setText(const std::string& text);
    
    // Cursor position
    int getCursorLine() const { return cursorLine; }
    int getCursorCol() const { return cursorCol; }
    
    // Utility
    bool isEmpty() const;
    int getLineCount() const { return lines.size(); }
    int getLineLength(int lineNum) const;
};

#endif
