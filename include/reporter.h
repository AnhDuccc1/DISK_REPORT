#ifndef REPORTER_H
#define REPORTER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <filesystem>
#include "scanner.h"

namespace fs = std::filesystem;

class Reporter {
private:
    std::string format_size(uint64_t bytes);
    std::string get_report_dir_path(const fs::path& target_path);

public:
    Reporter() = default;

    // Sắp xếp dữ liệu thu thập từ scanner
    void sort_data(DirectoryScanner& scanner);

    // In kết quả Top 5 ra terminal
    void print_terminal_report(const fs::path& target_path, const DirectoryScanner& scanner);

    // Xuất 4 file CSV
    void generate_csv_reports(const fs::path& target_path, const DirectoryScanner& scanner);
};

#endif // REPORTER_H
