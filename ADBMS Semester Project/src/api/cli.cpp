#include "api/cli.hpp"
#include "../include/query_processor/parser.hpp"
#include "../include/query_processor/executor.hpp"
#include <iostream>
#include <sstream>

namespace rdbms
{

    CLI::CLI() : running(true) {}

    void CLI::printWelcomeMessage() const
    {
        std::cout << "Welcome to RDBMS CLI!" << std::endl;
        std::cout << "Type your SQL command or 'exit' to quit." << std::endl;
    }

    void CLI::printPrompt() const
    {
        std::cout << "RDBMS> ";
    }

    std::string CLI::getInput() const
    {
        std::string input;
        std::getline(std::cin, input);
        return input;
    }

    std::vector<std::string> CLI::tokenize(const std::string &input) const
    {
        std::istringstream iss(input);
        std::vector<std::string> tokens;
        std::string token;
        while (iss >> token)
        {
            tokens.push_back(token);
        }
        return tokens;
    }

    void CLI::handleCommand(const std::string &command)
    {
        if (command == "exit")
        {
            running = false;
            std::cout << "Exiting CLI." << std::endl;
            return;
        }

        // Parse the command
        auto parsedQuery = Parser::parse(command);
        if (!parsedQuery.valid)
        {
            std::cout << "Syntax Error: " << parsedQuery.errorMessage << std::endl;
            return;
        }

        // Execute the command
        auto result = Executor::execute(parsedQuery);
        if (!result.success)
        {
            std::cout << "Execution Error: " << result.errorMessage << std::endl;
        }
        else
        {
            std::cout << "Success: " << result.message << std::endl;
        }
    }

    void CLI::run()
    {
        printWelcomeMessage();
        while (running)
        {
            printPrompt();
            std::string input = getInput();
            handleCommand(input);
        }
    }

} // namespace rdbms
