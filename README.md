# Smart Text Editor in C++

A feature-rich terminal-based text editor written in C++ with syntax highlighting, undo/redo, search & replace, and more.

## Features

- **Syntax Highlighting**: Support for C++ and Python with color-coded keywords, strings, comments, and numbers
- **Code Formatting**: Auto-indentation for better code organization
- **Search & Replace**: Find and replace text with support for find next/previous
- **Undo/Redo**: Revert or redo changes made to your document
- **File I/O**: Open, save, and save-as functionality
- **Terminal UI**: Built with ncurses for a smooth terminal experience
- **Line Numbers**: Display line numbers for easy navigation
- **Cursor Navigation**: Full keyboard support for cursor movement

## Project Structure

```
.
├── include/              # Header files
│   ├── TextBuffer.h      # Core text buffer management
│   ├── SyntaxHighlighter.h  # Syntax highlighting engine
│   ├── SearchReplace.h   # Search and replace functionality
│   ├── FileManager.h     # File I/O operations
│   └── TextEditor.h      # Main editor class
├── src/                  # Implementation files
│   ├── TextBuffer.cpp
│   ├── SyntaxHighlighter.cpp
│   ├── SearchReplace.cpp
│   ├── FileManager.cpp
│   ├── TextEditor.cpp
│   └── main.cpp
├── CMakeLists.txt        # Build configuration
└── README.md             # This file
```

## Requirements

- C++17 or later
- CMake 3.10 or later
- ncurses library (or PDCurses on Windows)

### Installing Dependencies

**Linux (Ubuntu/Debian):**
```bash
sudo apt-get install libncurses-dev cmake build-essential
```

**macOS:**
```bash
brew install ncurses cmake
```

**Windows:**
- Install Visual Studio C++ build tools
- Install CMake
- Install PDCurses or use Windows build of ncurses

## Building the Project

1. Create a build directory:
```bash
mkdir build
cd build
```

2. Generate build files with CMake:
```bash
cmake ..
```

3. Build the project:
```bash
cmake --build .
```

Or on Linux/macOS:
```bash
make
```

## Running the Editor

To start with a new file:
```bash
./bin/smart_editor
```

Or to open an existing file:
```bash
./bin/smart_editor path/to/your/file.cpp
```

## Keyboard Shortcuts

| Shortcut | Action |
|----------|--------|
| `Arrow Keys` | Move cursor |
| `Home/End` | Go to line start/end |
| `Page Up/Down` | Scroll page up/down |
| `Ctrl+F` | Find text |
| `Ctrl+H` | Replace text |
| `Ctrl+S` | Save file |
| `Ctrl+Z` | Undo |
| `Ctrl+Y` | Redo |
| `Ctrl+Q` | Quit editor |
| `Delete` | Delete character at cursor |
| `Backspace` | Delete character before cursor |
| `Tab` | Insert 4 spaces |
| `Enter` | New line with auto-indent |

## Supported Languages

- **C++**: Keywords, types, preprocessor directives, strings, comments, and numbers
- **Python**: Keywords, strings, comments, and numbers

The editor automatically detects the language based on file extension:
- `.cpp`, `.cc`, `.cxx`, `.h` → C++
- `.py` → Python

## Color Scheme

- **Green**: Keywords
- **Red**: Strings
- **Blue**: Comments
- **Yellow**: Numbers
- **Magenta**: Operators
- **Cyan**: Preprocessor directives and functions

## Architecture

The editor is built with a modular architecture:

- **TextBuffer**: Manages the text document, cursor position, and basic editing operations
- **SyntaxHighlighter**: Tokenizes code and provides syntax highlighting information
- **SearchReplace**: Handles search and replacement operations
- **FileManager**: Manages file I/O operations
- **TextEditor**: Main UI controller that ties all components together

## Limitations & Future Enhancements

### Current Limitations:
- Undo/redo stack has basic implementation (can be enhanced with full state snapshots)
- Single window display (no split views)
- No mouse support
- No plugin system

### Future Enhancements:
- Additional language support (Java, JavaScript, etc.)
- Multi-file tab support
- Find & replace with regex
- Bracket matching and highlighting
- Code snippets
- Themes and customizable colors
- Line wrapping
- Column selection/rectangular selection
- Minimap for large files

## Building on Different Platforms

### Ubuntu/Debian:
```bash
cd build
cmake ..
make
./bin/smart_editor
```

### macOS:
```bash
cd build
cmake -DCMAKE_PREFIX_PATH=$(brew --prefix ncurses) ..
make
./bin/smart_editor
```

### Windows (with Visual Studio):
```bash
cd build
cmake -G "Visual Studio 16 2019" ..
cmake --build . --config Release
.\bin\smart_editor.exe
```

## License

This project is provided as-is for educational purposes.

## Author

Built for Data Structures and Algorithms (ADS) Mini Project
