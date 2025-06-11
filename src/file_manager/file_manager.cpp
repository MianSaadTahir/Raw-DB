#include "file_manager/file_manager.hpp"
#include <iostream>
#include <cstdio>     // For mkdir
#include <sys/stat.h> // POSIX mkdir
#include <direct.h>   // For _mkdir on Windows

using namespace std;

namespace rdbms
{

    FileManager::FileManager() {}

    FileManager::~FileManager()
    {
        for (auto &entry : openFiles)
        {
            entry.second.close();
        }
    }

    string FileManager::resolvePath(const string &filename)
    {
        string dir = "data/tables/";
        _mkdir("data");
        _mkdir("data/tables");
        return dir + filename + ".dbf";
    }

    bool FileManager::createFile(const string &filename)
    {
        string path = resolvePath(filename);
        ofstream file(path.c_str(), ios::binary);
        if (!file.is_open())
        {
            cerr << "Failed to create file: " << path << "\n";
            return false;
        }
        file.close();
        return true;
    }

    bool FileManager::openFile(const string &filename)
    {
        string path = resolvePath(filename);
        fstream file(path.c_str(), ios::in | ios::out | ios::binary);
        if (!file.is_open())
        {
            cerr << "Failed to open file: " << path << "\n";
            return false;
        }
        openFiles[filename] = move(file);
        return true;
    }

    void FileManager::closeFile(const string &filename)
    {
        if (openFiles.count(filename))
        {
            openFiles[filename].close();
            openFiles.erase(filename);
        }
    }

    bool FileManager::writePage(const string &filename, int pageNumber, const char *data)
    {
        if (!openFiles.count(filename))
            return false;

        fstream &file = openFiles[filename];
        file.seekp(pageNumber * PAGE_SIZE, ios::beg);
        file.write(data, PAGE_SIZE);
        file.flush();
        return file.good();
    }

    bool FileManager::readPage(const string &filename, int pageNumber, char *buffer)
    {
        if (!openFiles.count(filename))
            return false;

        fstream &file = openFiles[filename];
        file.seekg(pageNumber * PAGE_SIZE, ios::beg);
        file.read(buffer, PAGE_SIZE);
        return file.good();
    }

} // namespace rdbms
