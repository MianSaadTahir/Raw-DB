#include "../include/page/page.hpp"
#include <cstring>
#include <sstream>

namespace rdbms
{

    Page::Page()
    {
        memset(data, 0, PAGE_SIZE);
    }

    void Page::writeData(const std::string &input)
    {
        strncpy(data, input.c_str(), PAGE_SIZE - 1);
        data[PAGE_SIZE - 1] = '\0'; // Ensure null-termination
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

    bool Page::hasColumn(const std::string &column)
    {
        std::string rawData = readData();
        std::stringstream ss(rawData);
        std::string token;

        while (std::getline(ss, token, ','))
        {
            size_t pos = token.find('=');
            if (pos != std::string::npos)
            {
                std::string key = token.substr(0, pos);
                if (key == column)
                    return true;
            }
        }
        return false;
    }

    void Page::updateColumn(const std::string &column, const std::string &newValue)
    {
        std::string rawData = readData();
        std::stringstream ss(rawData);
        std::string token;
        std::string updatedData;
        bool updated = false;

        while (std::getline(ss, token, ','))
        {
            size_t pos = token.find('=');
            if (pos != std::string::npos)
            {
                std::string key = token.substr(0, pos);
                std::string value = token.substr(pos + 1);

                if (key == column)
                {
                    updatedData += key + "=" + newValue + ",";
                    updated = true;
                }
                else
                {
                    updatedData += token + ",";
                }
            }
        }

        if (updated && !updatedData.empty())
        {
            updatedData.pop_back(); // remove trailing comma
            writeData(updatedData);
        }
    }

} // namespace rdbms
