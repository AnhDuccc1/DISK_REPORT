# DRP - Disk Report CLI Tool (v1.0)

DRP là công cụ dòng lệnh (CLI) chạy trên hệ điều hành Linux dùng để quét thư mục, phân tích dung lượng file/thư mục và tự động xuất các báo cáo chi tiết dưới dạng file CSV.

## 🛠️ Yêu cầu hệ thống (Requirements)

- **OS:** Linux (Ubuntu/Debian...)
- **Compiler:** `g++` hỗ trợ C++17 trở lên
- **Build tool:** `CMake` (v3.10+)

## 🚀 Cài đặt (Installation)

### Bước 1: Tải mã nguồn về máy
```bash
git clone https://github.com/AnhDuccc1/DISK_REPORT.git
cd DISK_REPORT
```
### Bước 2: Chạy script cài đặt tự động
```bash
chmod +x scripts/install.sh scripts/uninstall.sh
./scripts/install.sh
```
### Hướng dẫn sử dụng
# Quét thư mục hiện tại
```bash
drp .
```
# Quét một thư mục cụ thể
```bash
drp /path/to/directory
```
##🧪 Kiểm thử (Testing)

### Biên dịch dự án 
```bash
cmake -B build && cmake --build build
```
### Chạy bộ kiểm thử tự động
```bash
./tests/run_tests.sh
```

