# Contributing Guide

## 1. Repository Setup

1. Create the Git repository.
2. Add project members as Collaborators.
3. Clone the repository.
4. Create the initial project structure.
5. Commit the initial setup.

## 2. Git Workflow

Không commit trực tiếp vào `main`.

Mỗi task tạo một branch riêng từ `main`:

```bash id="86d6bd"
git checkout main
git pull
git checkout -b <branch-name>
```

Naming:

```text id="84hwd4"
feature/directory-scanner
feature/csv-report
fix/permission-error
test/scanner
docs/readme
```

Workflow:

```text id="kzjl1g"
main
 ↓
create branch
 ↓
implement
 ↓
test
 ↓
commit
 ↓
push
 ↓
Pull Request
 ↓
review
 ↓
merge main
```

## 3. Commit

Mỗi commit nên chứa một thay đổi có ý nghĩa.

Recommended format:

```text id="y0rmnr"
<type>: <short description>
```

Examples:

```text id="3x1ttm"
feat: add directory scanner
feat: generate csv reports
fix: handle permission denied
test: add scanner tests
docs: update build instructions
refactor: simplify file sorting
```

Tránh commit message như:

```text id="swnb4w"
update
fix
change code
done
final
```

## 4. Pull Request

Trước khi tạo Pull Request:

* Build thành công.
* Chạy các test liên quan.
* Review lại code của chính mình.
* Xóa debug code không cần thiết.

Pull Request cần mô tả ngắn:

```text id="hkwq4s"
What:
Implement directory scanner.

Test:
Tested with normal, empty and nested directories.
```

Ít nhất một người còn lại review trước khi merge.

## 5. Project Structure

Tách riêng header và source files.

```text id="pb7i36"
drp/
├── include/
│   ├── scanner.h
│   ├── file_info.h
│   └── reporter.h
│
├── src/
│   ├── main.cpp
│   ├── scanner.cpp
│   ├── file_info.cpp
│   └── reporter.cpp
│
├── tests/
├── scripts/
├── CMakeLists.txt
├── README.md
└── CONTRIBUTING.md
```

General rules:

* `.h` chứa declarations/interfaces.
* `.cpp` chứa implementations.
* Không đặt toàn bộ logic trong `main.cpp`.
* Mỗi class/module nên có responsibility rõ ràng.
* Test code đặt trong `tests/`.
* Shell scripts đặt trong `scripts/`.
* Build output không commit lên Git.

Example:

```text id="q75n4r"
build/
*.o
*.out
```

phải được thêm vào `.gitignore`.

## 6. Coding Principles

Ưu tiên:

```text id="f3o4j5"
Simple
Readable
Maintainable
```

* Đặt tên variable/function/class rõ nghĩa.
* Function nên làm một nhiệm vụ chính.
* Tránh duplicate code.
* Chỉ comment khi cần giải thích "why", không comment lại "what" mà code đã thể hiện rõ.
* Không thêm abstraction hoặc dependency nếu chưa thực sự cần.

## 7. Using AI

Có thể sử dụng AI trong mọi bước:

* Research
* Design
* Coding
* Debugging
* Testing
* Code review
* Documentation

Nhưng trước khi merge code:

> Người tạo Pull Request phải hiểu, review và chịu trách nhiệm cho code mình đưa vào project.

Nếu chưa hiểu code AI tạo ra, hãy hỏi AI giải thích hoặc research thêm trước khi merge.
