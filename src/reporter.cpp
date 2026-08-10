#include "reporter.h"
#include <iomanip>
#include <sstream>

// Chuyển đổi dung lượng byte sang định dạng dễ đọc (B, KB, MB, GB)
std::string Reporter::format_size(uint64_t bytes) {
    double size = static_cast<double>(bytes);
    std::ostringstream out;
    out << std::fixed << std::setprecision(1);

    if (bytes < 1024) {
        return std::to_string(bytes) + " B";
    } else if (bytes < 1024 * 1024) {
        out << (size / 1024.0) << " KB";
    } else if (bytes < 1024 * 1024 * 1024) {
        out << (size / (1024.0 * 1024.0)) << " MB";
    } else {
        out << (size / (1024.0 * 1024.0 * 1024.0)) << " GB";
    }
    return out.str();
}

// Xác định đường dẫn lưu report: ~/.drp/<folder_name>_report/
std::string Reporter::get_report_dir_path(const fs::path& target_path) {
    std::string folder_name = fs::absolute(target_path).filename().string();
    if (folder_name.empty() || folder_name == ".") {
        folder_name = fs::absolute(target_path).parent_path().filename().string();
    }
    
    std::string home_dir = getenv("HOME") ? getenv("HOME") : ".";
    return home_dir + "/.drp/" + folder_name + "_report/";
}

void Reporter::sort_data(DirectoryScanner& scanner) {
    // 1. Sort Files theo dung lượng giảm dần
    std::sort(scanner.files.begin(), scanner.files.end(), [](const FileEntry& a, const FileEntry& b) {
        return a.size_bytes > b.size_bytes;
    });

    // 2. Sort Directories theo dung lượng giảm dần
    std::sort(scanner.directories.begin(), scanner.directories.end(), [](const DirectoryEntry& a, const DirectoryEntry& b) {
        return a.size_bytes > b.size_bytes;
    });
}

void Reporter::print_terminal_report(const fs::path& target_path, const DirectoryScanner& scanner) {
    std::cout << "\nScanning " << target_path << "...\n\n";
    std::cout << "Found: " << scanner.total_files << " files, " 
              << scanner.total_directories << " directories\n";
    std::cout << "Total: " << format_size(scanner.total_size) << "\n\n";

    // In Top 5 Largest Files
    std::cout << "Top 5 largest files:\n";
    size_t file_limit = std::min<size_t>(5, scanner.files.size());
    for (size_t i = 0; i < file_limit; ++i) {
        std::cout << (i + 1) << ". " << std::left << std::setw(25) 
                  << scanner.files[i].name << format_size(scanner.files[i].size_bytes) << "\n";
    }

    // In Top 5 Largest Folders
    std::cout << "\nTop 5 largest folders:\n";
    size_t dir_limit = std::min<size_t>(5, scanner.directories.size());
    for (size_t i = 0; i < dir_limit; ++i) {
        std::cout << (i + 1) << ". " << std::left << std::setw(25) 
                  << (scanner.directories[i].name + "/") << format_size(scanner.directories[i].size_bytes) << "\n";
    }

    std::cout << "\nDetailed reports generated at:\n" << get_report_dir_path(target_path) << "\n";
}

void Reporter::generate_csv_reports(const fs::path& target_path, const DirectoryScanner& scanner) {
    std::string report_dir = get_report_dir_path(target_path);
    fs::create_directories(report_dir);

    // 1. Xuất summary.csv
    std::ofstream summary_file(report_dir + "summary.csv");
    if (summary_file.is_open()) {
        summary_file << "metric,value\n";
        summary_file << "scan_path," << fs::absolute(target_path).string() << "\n";
        summary_file << "total_files," << scanner.total_files << "\n";
        summary_file << "total_directories," << scanner.total_directories << "\n";
        summary_file << "total_size_bytes," << scanner.total_size << "\n";
        
        if (!scanner.files.empty()) {
            summary_file << "largest_file," << scanner.files[0].name << "\n";
            summary_file << "largest_file_size_bytes," << scanner.files[0].size_bytes << "\n";
        }
        if (!scanner.directories.empty()) {
            summary_file << "largest_directory," << scanner.directories[0].name << "\n";
            summary_file << "largest_directory_size_bytes," << scanner.directories[0].size_bytes << "\n";
        }
        summary_file.close();
    }

    // 2. Xuất files.csv
    std::ofstream files_file(report_dir + "files.csv");
    if (files_file.is_open()) {
        files_file << "rank,name,extension,size_bytes,size,path\n";
        for (size_t i = 0; i < scanner.files.size(); ++i) {
            const auto& f = scanner.files[i];
            files_file << (i + 1) << "," << f.name << "," << f.extension << "," 
                       << f.size_bytes << "," << format_size(f.size_bytes) << "," << f.path << "\n";
        }
        files_file.close();
    }

    // 3. Xuất directories.csv
    std::ofstream dirs_file(report_dir + "directories.csv");
    if (dirs_file.is_open()) {
        dirs_file << "rank,name,size_bytes,size,file_count,path\n";
        for (size_t i = 0; i < scanner.directories.size(); ++i) {
            const auto& d = scanner.directories[i];
            dirs_file << (i + 1) << "," << d.name << "," << d.size_bytes << "," 
                      << format_size(d.size_bytes) << "," << d.file_count << "," << d.path << "\n";
        }
        dirs_file.close();
    }

    // 4. Xuất extensions.csv
    std::ofstream exts_file(report_dir + "extensions.csv");
    if (exts_file.is_open()) {
        exts_file << "rank,extension,file_count,total_size_bytes,total_size\n";
        
        // Chuyển map sang vector để sort
        std::vector<ExtensionEntry> ext_list;
        for (const auto& pair : scanner.extension_map) {
            ext_list.push_back(pair.second);
        }
        std::sort(ext_list.begin(), ext_list.end(), [](const ExtensionEntry& a, const ExtensionEntry& b) {
            return a.total_size_bytes > b.total_size_bytes;
        });

        for (size_t i = 0; i < ext_list.size(); ++i) {
            const auto& ext = ext_list[i];
            exts_file << (i + 1) << "," << ext.extension << "," << ext.file_count << "," 
                      << ext.total_size_bytes << "," << format_size(ext.total_size_bytes) << "\n";
        }
        exts_file.close();
    }
}
