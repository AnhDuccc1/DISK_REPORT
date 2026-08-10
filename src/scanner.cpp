#include "scanner.h"
#include <algorithm>

uint64_t DirectoryScanner::get_file_inode(const fs::path& file_path) {
    struct stat file_stat;
    if (lstat(file_path.c_str(), &file_stat) == 0) {
        return static_cast<uint64_t>(file_stat.st_ino);
    }
    return 0;
}

void DirectoryScanner::scan_directory(const fs::path& target_path) {
    std::error_code ec;

    if (!fs::exists(target_path, ec)) {
        std::cerr << "Error: Path does not exist -> " << target_path << std::endl;
        return;
    }

    auto options = fs::directory_options::none;

    // Map dùng để tích lũy dung lượng và số lượng file cho từng thư mục
    std::map<std::string, DirectoryEntry> dir_map;

    for (const auto& entry : fs::recursive_directory_iterator(target_path, options, ec)) {
        if (ec) {
            ec.clear();
            continue;
        }

        const auto& path = entry.path();

        // 1. Bỏ qua Symlink
        if (entry.is_symlink()) {
            continue;
        }

        // 2. Nếu là thư mục, khởi tạo bản ghi trong map
        if (entry.is_directory()) {
            total_directories++;
            std::string dir_str = path.string();
            if (dir_map.find(dir_str) == dir_map.end()) {
                DirectoryEntry d_info;
                d_info.name = path.filename().string();
                d_info.path = dir_str;
                d_info.size_bytes = 0;
                d_info.file_count = 0;
                dir_map[dir_str] = d_info;
            }
        } 
        // 3. Nếu là file, cộng dung lượng cho file và cộng dồn cho tất cả thư mục cha
        else if (entry.is_regular_file()) {
            uint64_t inode = get_file_inode(path);
            if (inode != 0) {
                if (visited_inodes.find(inode) != visited_inodes.end()) {
                    continue; // Bỏ qua Hard link trùng
                }
                visited_inodes.insert(inode);
            }

            uint64_t file_sz = entry.file_size(ec);
            if (!ec) {
                total_size += file_sz;
                total_files++;

                // Lưu thông tin File
                FileEntry f_info;
                f_info.name = path.filename().string();
                f_info.extension = path.has_extension() ? path.extension().string() : "[no extension]";
                f_info.size_bytes = file_sz;
                f_info.path = path.string();
                files.push_back(f_info);

                // Thống kê Extension
                auto& ext_info = extension_map[f_info.extension];
                ext_info.extension = f_info.extension;
                ext_info.file_count++;
                ext_info.total_size_bytes += file_sz;

                // CỘNG DỒN DUNG LƯỢNG VÀO TẤT CẢ CÁC THƯ MỤC CHA
                fs::path parent = path.parent_path();
                while (!parent.empty() && parent != target_path.parent_path()) {
                    std::string parent_str = parent.string();
                    
                    // Nếu chưa có trong map thì tạo mới
                    if (dir_map.find(parent_str) == dir_map.end()) {
                        DirectoryEntry d_info;
                        d_info.name = parent.filename().string();
                        d_info.path = parent_str;
                        d_info.size_bytes = 0;
                        d_info.file_count = 0;
                        dir_map[parent_str] = d_info;
                    }

                    dir_map[parent_str].size_bytes += file_sz;
                    dir_map[parent_str].file_count += 1;

                    parent = parent.parent_path();
                }
            } else {
                ec.clear();
            }
        }
    }

    // Chuyển dữ liệu từ dir_map vào danh sách vector directories
    for (const auto& pair : dir_map) {
        directories.push_back(pair.second);
    }
}
