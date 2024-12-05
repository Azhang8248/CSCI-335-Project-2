#include <iostream>
#include <vector>
#include "FileAVL.hpp"
#include "FileTrie.hpp"
#include "File.hpp"  

int main() {
    FileTrie fileTrie;

    File* file1 = new File("pic.jpg", "This is a small file content.", nullptr);  
    File* file2 = new File("pic2.jpg", "This is a medium-sized file content with more words.", nullptr);  
    File* file3 = new File("pic3.jpg", "This file has a much larger amount of content to demonstrate varying sizes. The content can go on and on, simulating a large file.", nullptr);  // File with large content
    File* file4 = new File("notes.txt", "Another file..", nullptr);  
    File* file5 = new File("notes.doc", "A short file.", nullptr);
    File* file6 = new File("notes.pdf", "file.", nullptr);  

    FileAVL tree;

    tree.insert(file1);
    tree.insert(file2);
    tree.insert(file3);
    tree.insert(file4);
    tree.insert(file5);
    tree.insert(file6);

    size_t minSize = 1;
    size_t maxSize = 9;
    std::vector<File*> result = tree.query(minSize, maxSize);

    std::cout << "Files within size range [" << minSize << ", " << maxSize << "]:" << std::endl;
    for (File* f : result) {
        std::cout << f->getName() << " (Size: " << f->getSize() << ")" << std::endl;
    }

    minSize = 10;
    maxSize = 20;
    result = tree.query(minSize, maxSize);

    std::cout << "\nFiles within size range [" << minSize << ", " << maxSize << "]:" << std::endl;
    for (File* f : result) {
        std::cout << f->getName() << " (Size: " << f->getSize() << ")" << std::endl;
    }

    delete file1;
    delete file2;
    delete file3;
    delete file4;
    delete file5;
    delete file5;

    return 0;
}
