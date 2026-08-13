# Test Data Fixtures for DRP

Thư mục này chứa các bộ dữ liệu mẫu phục vụ kiểm thử tự động cho công cụ DRP:

- `normal_dir/`: Thư mục thông thường chứa hỗn hợp file và thư mục con (TC01)
- `empty_dir/`: Thư mục trống (TC02)
- `nested_dirs/`: Thư mục lồng nhau nhiều cấp (TC05)
- `mixed_sizes/`: Các file với dung lượng khác nhau từ 0 byte đến vài MB (TC06)
- `no_extension/`: File không có đuôi mở rộng (TC07)
- `with spaces/`: Thư mục và file có chứa dấu cách (TC08)
- `restricted/`: Thư mục bị bỏ quyền truy cập `chmod 000` (TC09)
- `few_files/`: Thư mục có dưới 5 file (TC10)
