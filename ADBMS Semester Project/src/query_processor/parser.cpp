#include "../include/query_processor/parser.hpp"
#include <sstream>
#include <algorithm>

std::vector<std::string> Parser::tokenize(const std::string &input)
{
    std::vector<std::string> tokens;
    std::stringstream ss(input);
    std::string word;
    while (ss >> word)
        tokens.push_back(word);
    return tokens;
}

std::string Parser::toLower(const std::string &str)
{
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

ParsedCommand Parser::parseFullCommand(const std::string &input)
{
    auto tokens = tokenize(input);
    ParsedCommand result;

    if (tokens.empty())
    {
        result.type = CommandType::INVALID;
        return result;
    }

    std::string command = toLower(tokens[0]);

    if (command == "put")
        result.type = CommandType::PUT;
    else if (command == "get")
        result.type = CommandType::GET;
    else if (command == "remove")
        result.type = CommandType::REMOVE;
    else if (command == "show")
        result.type = CommandType::SHOW;
    else if (command == "flush")
        result.type = CommandType::FLUSH;
    else if (command == "exit")
        result.type = CommandType::EXIT;
    else if (command == "create_database")
        result.type = CommandType::CREATE_DATABASE;
    else if (command == "alter_database")
        result.type = CommandType::ALTER_DATABASE;
    else if (command == "join")
        result.type = CommandType::JOIN;
    else if (command == "group_by")
        result.type = CommandType::GROUP_BY;
    else if (command == "order")
        result.type = CommandType::ORDER;
    else if (command == "match")
        result.type = CommandType::MATCH;
    else if (command == "limit")
        result.type = CommandType::LIMIT;
    else if (command == "distinct")
        result.type = CommandType::DISTINCT;
    else if (command == "create_index")
        result.type = CommandType::CREATE_INDEX;
    else if (command == "update")
        result.type = CommandType::UPDATE; // Added for UPDATE command
    else
        result.type = CommandType::INVALID;

    result.args = std::vector<std::string>(tokens.begin() + 1, tokens.end());

    return result;
}
