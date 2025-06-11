#include "../include/query_processor/parser.hpp"
#include <cassert>
#include <iostream>

void testSingleCommand(const std::string &input, CommandType expectedType, const std::vector<std::string> &expectedArgs)
{
    ParsedCommand cmd = Parser::parseFullCommand(input);
    assert(cmd.type == expectedType);
    assert(cmd.args.size() == expectedArgs.size());
    for (size_t i = 0; i < expectedArgs.size(); ++i)
    {
        assert(cmd.args[i] == expectedArgs[i]);
    }
}

void testParser()
{
    testSingleCommand("PUT key1 value1", CommandType::PUT, {"key1", "value1"});
    testSingleCommand("GET key1", CommandType::GET, {"key1"});
    testSingleCommand("REMOVE key1", CommandType::REMOVE, {"key1"});
    testSingleCommand("SHOW", CommandType::SHOW, {});
    testSingleCommand("FLUSH", CommandType::FLUSH, {});
    testSingleCommand("EXIT", CommandType::EXIT, {});
    testSingleCommand("CREATE_DATABASE mydb", CommandType::CREATE_DATABASE, {"mydb"});
    testSingleCommand("ALTER_DATABASE prod", CommandType::ALTER_DATABASE, {"prod"});
    testSingleCommand("JOIN table1 table2", CommandType::JOIN, {"table1", "table2"});
    testSingleCommand("GROUP_BY age", CommandType::GROUP_BY, {"age"});
    testSingleCommand("ORDER name", CommandType::ORDER, {"name"});
    testSingleCommand("MATCH abc*", CommandType::MATCH, {"abc*"});
    testSingleCommand("LIMIT 5", CommandType::LIMIT, {"5"});
    testSingleCommand("DISTINCT", CommandType::DISTINCT, {});
    testSingleCommand("CREATE_INDEX name", CommandType::CREATE_INDEX, {"name"});
    testSingleCommand("UPDATE users name Bob name Alice =", CommandType::UPDATE, {"users", "name", "Bob", "name", "Alice", "="});

    // Invalid command
    testSingleCommand("FOOBAR something", CommandType::INVALID, {"something"});

    std::cout << "All parser tests passed.\n";
}

int main()
{
    testParser();
    return 0;
}
