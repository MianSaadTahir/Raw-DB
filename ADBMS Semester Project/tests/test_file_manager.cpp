#include "../include/file_manager/file_manager.hpp"
#include <iostream>
#include <cassert>
#include <cstring>

using namespace std;
using namespace rdbms;

void test_create_and_open() {
    FileManager fm;
    string filename = "test_file";

    assert(fm.createFile(filename) && "Failed to create file");
    assert(fm.openFile(filename) && "Failed to open file");
    fm.closeFile(filename);
}

void test_write_and_read() {
    FileManager fm;
    string filename = "test_rw_file";
    fm.createFile(filename);
    fm.openFile(filename);

    char writeBuffer[PAGE_SIZE];
    memset(writeBuffer, 0, PAGE_SIZE);
    strcpy(writeBuffer, "Test read-write data");

    assert(fm.writePage(filename, 1, writeBuffer) && "Failed to write page");

    char readBuffer[PAGE_SIZE];
    memset(readBuffer, 0, PAGE_SIZE);

    assert(fm.readPage(filename, 1, readBuffer) && "Failed to read page");
    assert(strcmp(writeBuffer, readBuffer) == 0 && "Data mismatch after read");

    fm.closeFile(filename);
}

int main() {
    cout << "Running FileManager tests...\n";

    test_create_and_open();
    cout << "File create/open test passed.\n";

    test_write_and_read();
    cout << "Write/Read page test passed.\n";

    cout << "All FileManager tests passed.\n";
    return 0;
}
