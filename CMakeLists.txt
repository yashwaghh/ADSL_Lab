cmake_minimum_required(VERSION 3.10)
project(SmartTextEditor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Source files
set(SOURCES
    src/TextBuffer.cpp
    src/SyntaxHighlighter.cpp
    src/SearchReplace.cpp
    src/FileManager.cpp
    src/TextEditor.cpp
    src/main.cpp
)

# Create executable
add_executable(smart_editor ${SOURCES})

# Set output directory
set_target_properties(smart_editor PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
