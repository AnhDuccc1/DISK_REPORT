#include <iostream>
#include "scanner.h"

int main(int argc, char* argv[]) {
    // Kiểm tra đầu vào người dùng truyền vào đường dẫn chưa
    if (argc < 2) {
        std::cout << "Usage: drp <directory_path>" << std::endl;
        return 1;
    }

    fs::path target_dir = argv[1];

    std::cout << "Scanning directory: " << target_dir << " ..." << std::endl;

    DirectoryScanner scanner;
    uint64_t total_bytes = scanner.scan_directory(target_dir);

    // Đổi dung lượng sang MB cho dễ đọc
    double total_mb = static_cast<double>(total_bytes) / (1024 * 1024);

    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Total Size: " << total_bytes << " bytes (~" << total_mb << " MB)" << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    return 0;
}
