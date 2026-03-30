#include "TextEditor.h"
#include <iostream>

int main(int argc, char* argv[]) {
    try {
        TextEditor editor;
        
        if (argc > 1) {
            editor.openFile(argv[1]);
        } else {
            editor.newFile();
        }
        
        editor.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
