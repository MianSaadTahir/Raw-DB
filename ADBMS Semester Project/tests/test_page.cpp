#include "../include/page/page.hpp"
#include <iostream>
#include <cassert>
#include <cstring>

using namespace std;
using namespace rdbms;

void test_page_write_and_read()
{
    Page page;
    string testData = "Hello, this is test data!";
    page.writeData(testData);

    string readData = page.readData();
    assert(readData == testData && "Page read data does not match written data");
}

void test_page_raw_load_and_read()
{
    Page page;
    const char *rawData = "Raw page binary content.";
    page.loadFromRawData(rawData);

    string result = page.readData();
    assert(result == string(rawData) && "Loaded raw data does not match");
}

int main()
{
    cout << "Running Page tests...\n";

    test_page_write_and_read();
    cout << "Page write/read test passed.\n";

    test_page_raw_load_and_read();
    cout << "Page raw data load test passed.\n";

    cout << "All Page tests passed successfully.\n";
    return 0;
}
