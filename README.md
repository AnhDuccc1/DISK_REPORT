# DRP - Disk Report CLI Tool (v1.0)

DRP là công cụ dòng lệnh (CLI) chạy trên hệ điều hành Linux dùng để quét thư mục, phân tích dung lượng file/thư mục và tự động xuất các báo cáo chi tiết dưới dạng file CSV.

## 🛠️ Yêu cầu hệ thống (Requirements)
* **OS:** Linux (Ubuntu/Debian...)
* **Compiler:** `g++` hỗ trợ C++17 trở lên
* **Build tool:** `CMake` (v3.10+)

## 🚀 Cài đặt (Installation)
Chạy script cài đặt tự động để đưa lệnh `drp` vào hệ thống:

```bash
chmod +x scripts/install.sh scripts/uninstall.sh
./scripts/install.sh

## 🧪 Kiểm thử (Testing)

Dự án đã tích hợp kịch bản kiểm thử tự động cho 10 kịch bản (TC01 – TC10):

1. **Biên dịch dự án:**
   ```bash
   cmake -B build && cmake --build build
