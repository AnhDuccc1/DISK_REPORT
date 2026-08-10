#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <filesystem>
#include <unordered_set>
#include <sys/stat.h>
#include "file_info.h"

namespace fs = std::filesystem;

class DirectoryScanner {
private:
    std::unordered_set<uint64_t> visited_inodes;
    uint64_t get_file_inode(const fs::path& file_path);

public:
    std::vector<FileEntry> files;
    std::vector<DirectoryEntry> directories;
    std::map<std::string, ExtensionEntry> extension_map;
    
    uint64_t total_size = 0;
    uint64_t total_files = 0;
    uint64_t total_directories = 0;

    DirectoryScanner() = default;
    void scan_directory(const fs::path& target_path);
};

#endif // SCANNER_H
