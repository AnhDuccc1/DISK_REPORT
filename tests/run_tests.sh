#!/bin/bash

# Màu sắc hiển thị terminal
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

PASSED=0
FAILED=0

# Thiết lập lại quyền cho test fixture
if [ -f "tests/setup_fixtures.sh" ]; then
    bash tests/setup_fixtures.sh > /dev/null 2>&1
fi

# Đường dẫn tới file thực thi drp
DRP_BIN="./build/drp"

if [ ! -f "$DRP_BIN" ]; then
    echo -e "${RED}Lỗi: Chưa tìm thấy file binary $DRP_BIN. Hãy biên dịch dự án trước (cmake -B build && cmake --build build).${NC}"
    exit 1
fi

run_test() {
    local tc_id="$1"
    local description="$2"
    local command="$3"
    local expected_exit_code="$4"
    
    echo -n "Running $tc_id ($description)... "
    
    eval "$command" > /tmp/drp_test_output.log 2>&1
    local exit_code=$?

    if [ $exit_code -eq $expected_exit_code ]; then
        echo -e "${GREEN}[PASS]${NC}"
        ((PASSED++))
    else
        echo -e "${RED}[FAIL] (Expected exit code $expected_exit_code, got $exit_code)${NC}"
        ((FAILED++))
    fi
}

echo "=========================================="
echo "   RUNNING DRP AUTOMATED TEST SUITE       "
echo "=========================================="

# TC01: Normal directory
run_test "TC01" "Normal directory" "$DRP_BIN tests/data/normal_dir" 0

# TC02: Empty directory
run_test "TC02" "Empty directory" "$DRP_BIN tests/data/empty_dir" 0

# TC03: Directory does not exist (kỳ vọng báo lỗi - exit code khác 0)
run_test "TC03" "Directory does not exist" "$DRP_BIN tests/data/non_existent_dir" 1

# TC04: Input is a file (kỳ vọng báo lỗi - exit code khác 0)
run_test "TC04" "Input is a file" "$DRP_BIN tests/data/normal_dir/file1.txt" 1

# TC05: Nested directories
run_test "TC05" "Nested directories" "$DRP_BIN tests/data/nested_dirs" 0

# TC06: Mixed sizes
run_test "TC06" "Files with mixed sizes" "$DRP_BIN tests/data/mixed_sizes" 0

# TC07: No extension
run_test "TC07" "File without extension" "$DRP_BIN tests/data/no_extension" 0

# TC08: With spaces
run_test "TC08" "Name containing spaces" "$DRP_BIN \"tests/data/with spaces\"" 0

# TC09: Permission denied
run_test "TC09" "Permission denied handling" "$DRP_BIN tests/data/restricted" 0

# TC10: Fewer than 5 files
run_test "TC10" "Fewer than 5 files" "$DRP_BIN tests/data/few_files" 0

echo "=========================================="
echo -e "Test Summary: ${GREEN}$PASSED Passed${NC}, ${RED}$FAILED Failed${NC}"
echo "=========================================="

if [ $FAILED -ne 0 ]; then
    exit 1
fi
