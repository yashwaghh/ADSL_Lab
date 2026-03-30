#include "TextEditor.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <limits>

TextEditor::TextEditor() 
    : buffer(std::make_unique<TextBuffer>()),
      highlighter(std::make_unique<SyntaxHighlighter>()),
      search(std::make_unique<SearchReplace>()),
      fileManager(std::make_unique<FileManager>()),
      mode(EditorMode::NORMAL),
      scrollLine(0),
      scrollCol(0) {
    screenWidth = 120;
    screenHeight = 30;
}

TextEditor::~TextEditor() {}

void TextEditor::initializeNCurses() {
    #ifdef _WIN32
        system("chcp 65001 > nul");  // Set UTF-8 for Windows
    #endif
}

void TextEditor::cleanupNCurses() {}

void TextEditor::renderMainWindow() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    
    const auto& lines = buffer->getLines();
    int cursorLine = buffer->getCursorLine();
    int cursorCol = buffer->getCursorCol();
    
    if (cursorLine < scrollLine) scrollLine = cursorLine;
    if (cursorLine >= scrollLine + screenHeight - 3) scrollLine = cursorLine - (screenHeight - 3) + 1;
    if (cursorCol < scrollCol) scrollCol = cursorCol;
    if (cursorCol >= scrollCol + screenWidth - 15) scrollCol = cursorCol - (screenWidth - 15) + 1;
    
    // Print lines
    for (int y = 0; y < screenHeight - 3 && scrollLine + y < lines.size(); ++y) {
        int lineNum = scrollLine + y;
        std::cout << std::setw(4) << (lineNum + 1) << " | ";
        
        const std::string& line = lines[lineNum];
        int visibleCol = 0;
        for (size_t i = 0; i < line.length() && visibleCol < screenWidth - 10; ++i, ++visibleCol) {
            std::cout << line[i];
        }
        std::cout << "\n";
    }
}

void TextEditor::renderLine(int screenY, int lineNum) {}

void TextEditor::renderStatusBar() {
    std::string status = "Line:" + std::to_string(buffer->getCursorLine() + 1);
    status += " Col:" + std::to_string(buffer->getCursorCol() + 1);
    status += " | " + (fileManager->getCurrentFile().empty() ? "Untitled" : fileManager->getCurrentFile());
    if (fileManager->getIsModified()) status += " [*]";
    
    std::cout << "\n+" << std::string(screenWidth - 2, '-') << "+\n";
    std::cout << "| " << status;
    for (int i = status.length(); i < screenWidth - 3; ++i) std::cout << " ";
    std::cout << " |\n";
    std::cout << "+" << std::string(screenWidth - 2, '-') << "+\n";
}

void TextEditor::autoIndent() {
    if (buffer->getCursorLine() > 0) {
        const auto& prevLine = buffer->getLines()[buffer->getCursorLine() - 1];
        int indent = 0;
        for (char c : prevLine) {
            if (c == ' ') indent++;
            else if (c == '\t') indent += 4;
            else break;
        }
        for (int i = 0; i < indent; ++i) buffer->insertChar(' ');
    }
}

void TextEditor::handleNormalMode(int ch) {
    switch (ch) {
        case 'w': buffer->cursorUp(); break;
        case 's': buffer->cursorDown(); break;
        case 'a': buffer->cursorLeft(); break;
        case 'd': buffer->cursorRight(); break;
        case 'h': buffer->cursorHome(); break;
        case 'e': buffer->cursorEnd(); break;
        case 'f':
            mode = EditorMode::SEARCH;
            inputBuffer.clear();
            std::cout << "\nFind: ";
            std::cin >> inputBuffer;
            search->setSearchTerm(inputBuffer);
            performSearch();
            mode = EditorMode::NORMAL;
            break;
        case 'r': {
            mode = EditorMode::REPLACE;
            std::cout << "\nFind: ";
            std::string findTerm, replaceTerm;
            std::cin >> findTerm >> replaceTerm;
            search->setSearchTerm(findTerm);
            search->setReplaceTerm(replaceTerm);
            performReplace();
            mode = EditorMode::NORMAL;
            break;
        }
        case 'i': {
            std::cout << "\nInsert text (type '.' on new line to finish):\n";
            std::string line;
            while (std::getline(std::cin, line)) {
                if (line == ".") break;
                for (char c : line) buffer->insertChar(c);
                buffer->newLine();
            }
            fileManager->setIsModified(true);
            break;
        }
        case '\n': {
            buffer->newLine();
            autoIndent();
            fileManager->setIsModified(true);
            break;
        }
        case '\t': {
            buffer->insertString("    ");
            fileManager->setIsModified(true);
            break;
        }
        case 'z': buffer->undo(); break;
        case 'y': buffer->redo(); break;
        case 'c': {
            if (fileManager->getCurrentFile().empty()) {
                std::cout << "\nFilename: ";
                std::string filename;
                std::getline(std::cin, filename);
                fileManager->saveFile(filename, buffer->getLines());
            } else {
                fileManager->saveFile(fileManager->getCurrentFile(), buffer->getLines());
            }
            fileManager->setIsModified(false);
            break;
        }
        case 'q': return; // Exit
        case '\b': {
            buffer->deleteBackspace();
            fileManager->setIsModified(true);
            break;
        }
        default:
            if (ch >= 32 && ch < 127) {
                buffer->insertChar(ch);
                fileManager->setIsModified(true);
            }
            break;
    }
}

void TextEditor::handleSearchMode(int ch) {}
void TextEditor::handleReplaceMode(int ch) {}
void TextEditor::handleSaveAsMode(int ch) {}

void TextEditor::performSearch() {
    auto result = search->findNext(buffer->getLines(), buffer->getCursorLine(), buffer->getCursorCol());
    if (result.line != -1) {
        buffer->moveCursor(result.line, result.column);
        std::cout << "Found at line " << (result.line + 1) << ", column " << (result.column + 1) << "\n";
    } else {
        std::cout << "Not found!\n";
    }
}

void TextEditor::performReplace() {
    auto& linesRef = const_cast<std::vector<std::string>&>(buffer->getLines());
    int line = buffer->getCursorLine();
    int col = buffer->getCursorCol();
    search->replaceNext(linesRef, line, col);
    buffer->moveCursor(line, col);
    fileManager->setIsModified(true);
}

void TextEditor::openFile(const std::string& filepath) {
    std::vector<std::string> lines;
    if (fileManager->loadFile(filepath, lines)) {
        buffer->setText(fileManager->getText());
        highlighter->setLanguage(filepath);
    }
}

void TextEditor::newFile() {
    buffer = std::make_unique<TextBuffer>();
}

void TextEditor::run() {
    std::cout << "\n╔════════════════════════════════════╗\n";
    std::cout << "║  Smart Text Editor v1.0 - Console  ║\n";
    std::cout << "╚════════════════════════════════════╝\n\n";
    std::cout << "Commands:\n";
    std::cout << "  w/a/s/d : Move cursor\n";
    std::cout << "  i       : Insert text\n";
    std::cout << "  f       : Find\n";
    std::cout << "  r       : Replace\n";
    std::cout << "  c       : Save (commit)\n";
    std::cout << "  z       : Undo\n";
    std::cout << "  y       : Redo\n";
    std::cout << "  q       : Quit\n";
    std::cout << "  h/e     : Home/End\n\n";
    
    bool quit = false;
    while (!quit) {
        renderMainWindow();
        renderStatusBar();
        
        std::cout << "\nCommand: ";
        std::string input;
        std::getline(std::cin, input);
        
        if (input.empty()) continue;
        
        for (char ch : input) {
            handleNormalMode(ch);
            if (ch == 'q') {
                quit = true;
                break;
            }
        }
    }
    
    std::cout << "\nGoodbye!\n";
}
