#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#include <string>
#include <fstream>
#include <unordered_map>
#include "../config/constants.hpp"

using namespace std;

namespace rdbms {

    class FileManager {
    public:
        FileManager();
        ~FileManager();

        bool createFile(const string& filename);
        bool openFile(const string& filename);
        void closeFile(const string& filename);

        bool writePage(const string& filename, int pageNumber, const char* data);
        bool readPage(const string& filename, int pageNumber, char* buffer);

    private:
        unordered_map<string, fstream> openFiles;

        string resolvePath(const string& filename);
    };

} // namespace rdbms

#endif // FILE_MANAGER_HPP
