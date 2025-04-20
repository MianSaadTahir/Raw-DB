#include "../include/page/page.hpp"
#include <cstring>

namespace rdbms
{

    Page::Page()
    {
        memset(data, 0, PAGE_SIZE);
    }

    void Page::writeData(const std::string &input)
    {
        strncpy(data, input.c_str(), PAGE_SIZE - 1);
    }

    std::string Page::readData() const
    {
        return std::string(data);
    }

    const char *Page::getRawData() const
    {
        return data;
    }

    void Page::loadFromRawData(const char *raw)
    {
        memcpy(data, raw, PAGE_SIZE);
    }

} // namespace rdbms
