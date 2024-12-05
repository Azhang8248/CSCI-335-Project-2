#include "FileAVL.hpp"
#include "File.hpp"
#include "FileTrie.hpp"

// ALL YOUR CODE SHOULD BE IN THIS FILE. NO MODIFICATIONS SHOULD BE MADE TO FILEAVL / FILE CLASSES
// You are permitted to make helper functions (and most likely will need to)
// You must declare them "inline" | declare & implement them at the top of this file, before query()
// Below query(), implement and document all methods declared in FileTrie.hpp

inline void queryHelper(Node* node, size_t min, size_t max, std::vector<File*>& result);

inline std::string toLower(const std::string& str) {
    std::string result;
    for (char c : str) {
        result += std::tolower(c);
    }
    return result;
}

inline bool isValidChar(char c) {
    return std::isalnum(c) || c == '.';
}

inline void queryHelper(Node* node, size_t min, size_t max, std::vector<File*>& result) {
    if (node == nullptr) {
        return;
    }

    if (node->size_ >= min && node->size_ <= max) {
        result.insert(result.end(), node->files_.begin(), node->files_.end());
    }

    if (node->size_ > min) {
        queryHelper(node->left_, min, max, result);  // Recurse left if size > min
    }
    if (node->size_ < max) {
        queryHelper(node->right_, min, max, result);  // Recurse right if size < max
    }
}

/**
 * @brief Retrieves all files in the FileAVL whose file sizes are within [min, max]
 * 
 * @param min The min value of the file size query range.
 * @param max The max value of the file size query range.
 * @return std::vector<File*> storing pointers to all files in the tree within the given range.
 * @note If the query interval is in descending order (ie. the given parameters min >= max), 
        the interval from [max, min] is searched (since max >= min)
*/
std::vector<File*> FileAVL::query(size_t min, size_t max) {
    // Ensure the range is valid by swapping if min > max
    if (min > max) {
        std::swap(min, max);
    }

    std::vector<File*> result;
    queryHelper(root_, min, max, result);

    // Sort the result vector by file size
    std::sort(result.begin(), result.end(), [](File* a, File* b) {
        return a->getSize() < b->getSize();  // Assuming File has a method getSize() to return its size
    });

    return result;
}

FileTrie::FileTrie() : head(new FileTrieNode()) {}

// Add a file to the trie
void FileTrie::addFile(File* f) {
    if (!f) return;

    std::string filename = toLower(f->getName());

    // Validate filename: reject filenames with invalid characters
    for (char c : filename) {
        if (!isValidChar(c)) {
            std::cerr << "Invalid filename '" << f->getName() << "' ignored." << std::endl;
            return;
        }
    }

    FileTrieNode* current = head;

    current->matching.insert(f); 

    for (char c : filename) {
        if (current->next.find(c) == current->next.end()) {
            current->next[c] = new FileTrieNode(c);
        }
        current = current->next[c];
        current->matching.insert(f); 
    }
}

std::unordered_set<File*> FileTrie::getFilesWithPrefix(const std::string& prefix) const {
    std::string lowerPrefix = toLower(prefix);
    FileTrieNode* current = head;

    for (char c : lowerPrefix) {
        if (!isValidChar(c)) return {}; 
        if (current->next.find(c) == current->next.end()) {
            return {}; 
        }
        current = current->next[c];
    }

    return current->matching;
}

FileTrie::~FileTrie() { delete head; }