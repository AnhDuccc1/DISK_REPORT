cmake_minimum_required(VERSION 3.10)
project(drp VERSION 1.0 LANGUAGES CXX)

# Bắt buộc sử dụng C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Chỉ định thư mục chứa các file header (.h)
include_directories(include)

# Khai báo các file mã nguồn C++ cần biên dịch
set(SOURCES
    src/main.cpp
    src/scanner.cpp
)

# Tạo file thực thi 'drp' từ các file mã nguồn trên
add_executable(drp ${SOURCES})
