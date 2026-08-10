#include <iostream>
#include "scanner.h"
#include "reporter.h"

int main(int argc, char* argv[]) {
    // 1. Kiểm tra tham số đầu vào
    if (argc < 2) {
        std::cout << "Usage: drp <directory_path>" << std::endl;
        return 1;
    }

    fs::path target_dir = argv[1];

    // 2. Tiến hành Scan thư mục
    DirectoryScanner scanner;
    scanner.scan_directory(target_dir);

    // 3. Sắp xếp dữ liệu và xuất báo cáo (Terminal + CSV)
    Reporter reporter;
    reporter.sort_data(scanner);
    reporter.print_terminal_report(target_dir, scanner);
    reporter.generate_csv_reports(target_dir, scanner);

    return 0;
}
