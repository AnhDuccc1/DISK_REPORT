#ifndef FILE_INFO_H
#define FILE_INFO_H

#include <string>

struct FileEntry {
    std::string name;
    std::string extension;
    uint64_t size_bytes = 0;
    std::string path;
};

struct DirectoryEntry {
    std::string name;
    uint64_t size_bytes = 0;
    uint64_t file_count = 0;
    std::string path;
};

struct ExtensionEntry {
    std::string extension;
    uint64_t file_count = 0;
    uint64_t total_size_bytes = 0;
};

#endif // FILE_INFO_H
