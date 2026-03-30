#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include "TextBuffer.h"
#include "SyntaxHighlighter.h"
#include "SearchReplace.h"
#include "FileManager.h"
#include <string>
#include <memory>

enum class EditorMode {
    NORMAL,
    SEARCH,
    REPLACE,
    SAVE_AS
};

class TextEditor {
private:
    std::unique_ptr<TextBuffer> buffer;
    std::unique_ptr<SyntaxHighlighter> highlighter;
    std::unique_ptr<SearchReplace> search;
    std::unique_ptr<FileManager> fileManager;
    
    EditorMode mode;
    int screenWidth;
    int screenHeight;
    int scrollLine;
    int scrollCol;
    std::string inputBuffer;
    
    // UI state (simplified for console)
    
    void initializeNCurses();
    void cleanupNCurses();
    void renderMainWindow();
    void renderStatusBar();
    void renderLine(int screenY, int lineNum);
    void handleNormalMode(int ch);
    void handleSearchMode(int ch);
    void handleReplaceMode(int ch);
    void handleSaveAsMode(int ch);
    void performSearch();
    void performReplace();
    void autoIndent();
    
public:
    TextEditor();
    ~TextEditor();
    
    void run();
    void openFile(const std::string& filepath);
    void newFile();
};

#endif
