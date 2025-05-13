#include "../include/page/page.hpp"
#include <iostream>
#include <cassert>
#include <cstring>

using namespace std;
using namespace rdbms;

void printSection(const string &title)
{
    cout << "\n==== " << title << " ====\n";
}

int main()
{
    Page page;

    printSection("Testing writeData() and readData()");
    string testData = "id=1,name=Alice,age=30";
    page.writeData(testData);
    string readBack = page.readData();
    cout << "Written: " << testData << endl;
    cout << "Read:    " << readBack << endl;
    assert(readBack == testData);

    printSection("Testing getRawData()");
    const char *raw = page.getRawData();
    assert(strncmp(raw, testData.c_str(), testData.size()) == 0);
    cout << "Raw data matches expected." << endl;

    printSection("Testing loadFromRawData()");
    const char *newRaw = "id=2,name=Bob,age=40";
    page.loadFromRawData(newRaw);
    string afterLoad = page.readData();
    cout << "Loaded Raw: " << newRaw << "\nRead:       " << afterLoad << endl;
    assert(afterLoad == string(newRaw));

    printSection("Testing hasColumn()");
    assert(page.hasColumn("name") == true);
    assert(page.hasColumn("salary") == false);
    cout << "Column check passed." << endl;

    printSection("Testing updateColumn()");
    page.updateColumn("name", "Bobby");
    string updatedData = page.readData();
    cout << "Updated: " << updatedData << endl;
    assert(updatedData.find("name=Bobby") != string::npos);
    assert(page.hasColumn("name"));
    cout << "Update passed." << endl;

    cout << "\nAll Page tests passed successfully.\n";
    return 0;
}
