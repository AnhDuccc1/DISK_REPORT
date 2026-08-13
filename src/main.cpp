#include <iostream>
#include <filesystem>
#include "scanner.h"
#include "reporter.h"
// Giữ nguyên các header hiện tại của bạn (vd: #include "scanner.h", "reporter.h")

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    // 1. Kiểm tra tham số đầu vào
    if (argc < 2) {
        std::cout << "Usage: drp <directory_path>" << std::endl;
        return 1;
    }

    fs::path target_dir = argv[1];

    // --- Bổ sung validate để sửa TC03 & TC04 (Đúng theo tài liệu SRS) ---
    if (!fs::exists(target_dir)) {
        std::cerr << "Error: Directory does not exist." << std::endl;
        return 1; // Exit code khác 0 cho TC03
    }

    if (!fs::is_directory(target_dir)) {
        std::cerr << "Error: Input must be a directory." << std::endl;
        return 1; // Exit code khác 0 cho TC04
    }
    // -------------------------------------------------------------------

    // 2. Tiến hành Scan thư mục (Giữ nguyên)
    DirectoryScanner scanner;
    scanner.scan_directory(target_dir);

    // 3. Sắp xếp dữ liệu và xuất báo cáo (Terminal + CSV) (Giữ nguyên)
    Reporter reporter;
    reporter.sort_data(scanner);
    reporter.print_terminal_report(target_dir, scanner);
    reporter.generate_csv_reports(target_dir, scanner);

    return 0;
}
