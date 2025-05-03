#include "../include/query_processor/executor.hpp"
#include <sstream>
#include <iostream>

Executor::Executor(Database& db) : db(db) {}

void Executor::executeCommand(const std::string& commandLine) {
    std::istringstream stream(commandLine);
    std::string command;
    stream >> command;

    std::vector<std::string> args;
    std::string word;
    while (stream >> word) {
        args.push_back(word);
    }

    if (command == "PUT") executePut(args);
    else if (command == "GET") executeGet(args);
    else if (command == "REMOVE") executeRemove(args);
    else if (command == "SHOW") executeShow();
    else if (command == "FLUSH") executeFlush();
    else if (command == "EXIT") executeExit();
    else if (command == "CREATE_DATABASE") executeCreateDatabase(args);
    else if (command == "ALTER_DATABASE") executeAlterDatabase(args);
    else if (command == "JOIN") executeJoin(args);
    else if (command == "GROUP_BY") executeGroupBy(args);
    else if (command == "ORDER") executeOrder(args);
    else if (command == "MATCH") executeMatch(args);
    else if (command == "LIMIT") executeLimit(args);
    else if (command == "DISTINCT") executeDistinct();
    else if (command == "CREATE_INDEX") executeCreateIndex(args);
    else std::cout << "Unknown command: " << command << std::endl;
}

void Executor::executePut(const std::vector<std::string>& args) {
    if (args.size() < 2) return;
    db.insert(args[0], args[1]);
}

void Executor::executeGet(const std::vector<std::string>& args) {
    if (args.empty()) return;
    std::cout << db.get(args[0]) << std::endl;
}

void Executor::executeRemove(const std::vector<std::string>& args) {
    if (args.empty()) return;
    db.remove(args[0]);
}

void Executor::executeShow() {
    db.showAllData();
}

void Executor::executeFlush() {
    db.flushDatabase();
}

void Executor::executeExit() {
    std::cout << "Exiting...\n";
    exit(0);
}

void Executor::executeCreateDatabase(const std::vector<std::string>& args) {
    if (args.empty()) return;
    db.createDatabase(args[0]);
}

void Executor::executeAlterDatabase(const std::vector<std::string>& args) {
    if (args.empty()) return;
    db.alterDatabase(args[0]);
}

void Executor::executeJoin(const std::vector<std::string>& args) {
    if (args.size() < 2) return;
    db.join(args[0], args[1]);
}

void Executor::executeGroupBy(const std::vector<std::string>& args) {
    if (args.empty()) return;
    db.groupBy(args[0]);
}

void Executor::executeOrder(const std::vector<std::string>& args) {
    if (args.empty()) return;
    db.order(args[0]);
}

void Executor::executeMatch(const std::vector<std::string>& args) {
    if (args.empty()) return;
    db.match(args[0]);
}

void Executor::executeLimit(const std::vector<std::string>& args) {
    if (args.empty()) return;
    db.limit(std::stoi(args[0]));
}

void Executor::executeDistinct() {
    db.distinct();
}

void Executor::executeCreateIndex(const std::vector<std::string>& args) {
    if (args.empty()) return;
    db.createIndex(args[0]);
}
