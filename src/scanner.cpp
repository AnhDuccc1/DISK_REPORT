#include "scanner.h"

// Lấy mã inode duy nhất của file trên hệ điều hành Linux
uint64_t DirectoryScanner::get_file_inode(const fs::path& file_path) {
    struct stat file_stat;
    if (lstat(file_path.c_str(), &file_stat) == 0) {
        return static_cast<uint64_t>(file_stat.st_ino);
    }
    return 0;
}

uint64_t DirectoryScanner::scan_directory(const fs::path& target_path) {
    uint64_t total_size = 0;
    std::error_code ec;

    // Đảm bảo đường dẫn tồn tại
    if (!fs::exists(target_path, ec)) {
        std::cerr << "Error: Path does not exist -> " << target_path << std::endl;
        return 0;
    }

    // Cấu hình không tự động đuổi theo (follow) Symlink
    auto options = fs::directory_options::none;

    for (const auto& entry : fs::recursive_directory_iterator(target_path, options, ec)) {
        // Nếu gặp lỗi phân quyền (Permission denied) hoặc file hỏng -> Bỏ qua
        if (ec) {
            ec.clear();
            continue;
        }

        const auto& path = entry.path();

        // -------------------------------------------------------------
        // 1. XỬ LÝ SYMLINK: Bỏ qua không lặp sâu vào Symlink
        // -------------------------------------------------------------
        if (entry.is_symlink()) {
            continue; 
        }

        // -------------------------------------------------------------
        // 2. XỬ LÝ HARD LINK & TÍNH SIZE FILE
        // -------------------------------------------------------------
        if (entry.is_regular_file()) {
            uint64_t inode = get_file_inode(path);

            if (inode != 0) {
                // Nếu inode này đã được tính trước đó -> Bỏ qua (chống trùng Hard link)
                if (visited_inodes.find(inode) != visited_inodes.end()) {
                    continue;
                }
                // Đánh dấu inode đã duyệt
                visited_inodes.insert(inode);
            }

            // Cộng dồn dung lượng file thực tế
            uint64_t file_sz = entry.file_size(ec);
            if (!ec) {
                total_size += file_sz;
            } else {
                ec.clear();
            }
        }
    }

    return total_size;
}
