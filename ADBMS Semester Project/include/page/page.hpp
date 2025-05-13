#ifndef PAGE_HPP
#define PAGE_HPP

#include <string>
#include "../config/constants.hpp"

namespace rdbms
{

    class Page
    {
    public:
        Page();
        void writeData(const std::string &input);
        std::string readData() const;
        const char *getRawData() const;
        void loadFromRawData(const char *raw);
        bool hasColumn(const std::string &column);
        void updateColumn(const std::string &column, const std::string &newValue);

    private:
        char data[PAGE_SIZE];
    };

} // namespace rdbms

#endif
