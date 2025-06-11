#include "../include/buffer_pool/buffer_pool.hpp"
#include <iostream>
#include <cassert>
using namespace std;
using namespace rdbms;

int main()
{
    BufferPool pool(3);

    Page p1, p2, p3, p4;
    p1.writeData("Page 1");
    p2.writeData("Page 2");
    p3.writeData("Page 3");
    p4.writeData("Page 4");

    pool.addPage("p1", p1);
    pool.addPage("p2", p2);
    pool.addPage("p3", p3);
    pool.printLRU();

    // Access p1 to update LRU
    pool.getPage("p1");

    // Add another to cause eviction
    pool.addPage("p4", p4);
    pool.printLRU();

    assert(pool.hasPage("p1"));
    assert(pool.hasPage("p4"));
    assert(!pool.hasPage("p2")); // Should be evicted

    cout << "BufferPool tests passed.\n";
    return 0;
}
