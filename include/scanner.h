#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>
#include <string>
#include <filesystem>
#include <unordered_set>
#include <sys/stat.h>

namespace fs = std::filesystem;

// Cấu trúc lưu trữ thông tin kết quả quét của một Item
struct DiskItem {
    std::string path;
    uint64_t size_bytes = 0;
    bool is_directory = false;
};

class DirectoryScanner {
private:
    // Set lưu vết các inode đã được tính dung lượng (dùng cho Hard link)
    std::unordered_set<uint64_t> visited_inodes;

    // Hàm bổ trợ lấy mã inode trên Linux
    uint64_t get_file_inode(const fs::path& file_path);

public:
    DirectoryScanner() = default;

    // Hàm chính quét và tính tổng dung lượng thư mục
    uint64_t scan_directory(const fs::path& target_path);
};

#endif // SCANNER_H
