#ifndef EXECUTOR_HPP
#define EXECUTOR_HPP

#include <string>
#include <vector>
#include "../database/database.hpp"

enum class CommandType
{
    PUT,
    GET,
    REMOVE,
    SHOWDATABASE,
    SHOWTABLES,
    FLUSH,
    EXIT,
    CREATE_DATABASE,
    ALTER_DATABASE,
    CREATE_TABLE,
    INSERT,
    JOIN,
    GROUP_BY,
    ORDER,
    MATCH,
    LIMIT,
    DISTINCT,
    CREATE_INDEX,
    UPDATE,
    DELETE,
    SELECT
};

class Executor
{
public:
    Executor(Database &db);
    void executeCommand(const std::string &commandLine);

private:
    Database &db;

    void executePut(const std::vector<std::string> &args);
    void executeGet(const std::vector<std::string> &args);
    void executeRemove(const std::vector<std::string> &args);
    void executeShow();
    void executeFlush();
    void executeExit();
    void executeCreateDatabase(const std::vector<std::string> &args);
    void executeAlterDatabase(const std::vector<std::string> &args);
    void executeCreateTable(const std::vector<std::string> &args);
    void executeInsert(const std::vector<std::string> &args);
    void executeJoin(const std::vector<std::string> &args);
    void executeGroupBy(const std::vector<std::string> &args);
    void executeOrder(const std::vector<std::string> &args);
    void executeMatch(const std::vector<std::string> &args);
    void executeLimit(const std::vector<std::string> &args);
    void executeDistinct();
    void executeCreateIndex(const std::vector<std::string> &args);
    void executeUpdate(const std::vector<std::string> &args);
    void executeDelete(const std::vector<std::string> &args);
    void executeSelect(const std::vector<std::string> &args);
};

#endif // EXECUTOR_HPP
