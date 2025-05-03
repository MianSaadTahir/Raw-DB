#include <iostream>
#include <cassert>
#include "../include/query_processor/parser.hpp"

void testParser() {
    // Test: PUT Command
    std::string input1 = "put key1 value1";
    ParsedCommand result1 = Parser::parseFullCommand(input1);
    assert(result1.type == CommandType::PUT);
    assert(result1.args.size() == 2);
    assert(result1.args[0] == "key1");
    assert(result1.args[1] == "value1");
    std::cout << "[PASS] PUT Command\n";

    // Test: GET Command
    std::string input2 = "get key1";
    ParsedCommand result2 = Parser::parseFullCommand(input2);
    assert(result2.type == CommandType::GET);
    assert(result2.args.size() == 1);
    assert(result2.args[0] == "key1");
    std::cout << "[PASS] GET Command\n";

    // Test: REMOVE Command
    std::string input3 = "remove key1";
    ParsedCommand result3 = Parser::parseFullCommand(input3);
    assert(result3.type == CommandType::REMOVE);
    assert(result3.args.size() == 1);
    assert(result3.args[0] == "key1");
    std::cout << "[PASS] REMOVE Command\n";

    // Test: SHOW Command
    std::string input4 = "show";
    ParsedCommand result4 = Parser::parseFullCommand(input4);
    assert(result4.type == CommandType::SHOW);
    assert(result4.args.empty());
    std::cout << "[PASS] SHOW Command\n";

    // Test: FLUSH Command
    std::string input5 = "flush";
    ParsedCommand result5 = Parser::parseFullCommand(input5);
    assert(result5.type == CommandType::FLUSH);
    assert(result5.args.empty());
    std::cout << "[PASS] FLUSH Command\n";

    // Test: EXIT Command
    std::string input6 = "exit";
    ParsedCommand result6 = Parser::parseFullCommand(input6);
    assert(result6.type == CommandType::EXIT);
    assert(result6.args.empty());
    std::cout << "[PASS] EXIT Command\n";

    // Test: CREATE_DATABASE Command
    std::string input7 = "create_database TestDB";
    ParsedCommand result7 = Parser::parseFullCommand(input7);
    assert(result7.type == CommandType::CREATE_DATABASE);
    assert(result7.args.size() == 1);
    assert(result7.args[0] == "TestDB");
    std::cout << "[PASS] CREATE_DATABASE Command\n";

    // Test: ALTER_DATABASE Command
    std::string input8 = "alter_database TestDB_v2";
    ParsedCommand result8 = Parser::parseFullCommand(input8);
    assert(result8.type == CommandType::ALTER_DATABASE);
    assert(result8.args.size() == 1);
    assert(result8.args[0] == "TestDB_v2");
    std::cout << "[PASS] ALTER_DATABASE Command\n";

    // Test: JOIN Command
    std::string input9 = "join key1 key2";
    ParsedCommand result9 = Parser::parseFullCommand(input9);
    assert(result9.type == CommandType::JOIN);
    assert(result9.args.size() == 2);
    assert(result9.args[0] == "key1");
    assert(result9.args[1] == "key2");
    std::cout << "[PASS] JOIN Command\n";

    // Test: GROUP_BY Command
    std::string input10 = "group_by key1";
    ParsedCommand result10 = Parser::parseFullCommand(input10);
    assert(result10.type == CommandType::GROUP_BY);
    assert(result10.args.size() == 1);
    assert(result10.args[0] == "key1");
    std::cout << "[PASS] GROUP_BY Command\n";

    // Test: ORDER Command
    std::string input11 = "order key1";
    ParsedCommand result11 = Parser::parseFullCommand(input11);
    assert(result11.type == CommandType::ORDER);
    assert(result11.args.size() == 1);
    assert(result11.args[0] == "key1");
    std::cout << "[PASS] ORDER Command\n";

    // Test: MATCH Command
    std::string input12 = "match pattern1";
    ParsedCommand result12 = Parser::parseFullCommand(input12);
    assert(result12.type == CommandType::MATCH);
    assert(result12.args.size() == 1);
    assert(result12.args[0] == "pattern1");
    std::cout << "[PASS] MATCH Command\n";

    // Test: LIMIT Command
    std::string input13 = "limit 10";
    ParsedCommand result13 = Parser::parseFullCommand(input13);
    assert(result13.type == CommandType::LIMIT);
    assert(result13.args.size() == 1);
    assert(result13.args[0] == "10");
    std::cout << "[PASS] LIMIT Command\n";

    // Test: DISTINCT Command
    std::string input14 = "distinct";
    ParsedCommand result14 = Parser::parseFullCommand(input14);
    assert(result14.type == CommandType::DISTINCT);
    assert(result14.args.empty());
    std::cout << "[PASS] DISTINCT Command\n";

    // Test: CREATE_INDEX Command
    std::string input15 = "create_index key1";
    ParsedCommand result15 = Parser::parseFullCommand(input15);
    assert(result15.type == CommandType::CREATE_INDEX);
    assert(result15.args.size() == 1);
    assert(result15.args[0] == "key1");
    std::cout << "[PASS] CREATE_INDEX Command\n";

    // Test: Invalid Command
    std::string input16 = "unknown_command";
    ParsedCommand result16 = Parser::parseFullCommand(input16);
    assert(result16.type == CommandType::INVALID);
    assert(result16.args.empty());
    std::cout << "[PASS] INVALID Command\n";
}

int main() {
    std::cout << "Running Parser Tests...\n";
    testParser();
    std::cout << "All tests passed successfully!\n";
    return 0;
}
