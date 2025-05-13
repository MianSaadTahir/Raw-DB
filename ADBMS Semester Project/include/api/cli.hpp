#ifndef RDBMS_CLI_HPP
#define RDBMS_CLI_HPP

#include <string>
#include <vector>

namespace rdbms
{

    class CLI
    {
    public:
        CLI();
        void run(); // Launch the CLI loop

    private:
        void printWelcomeMessage() const;
        void printPrompt() const;
        std::string getInput() const;
        std::vector<std::string> tokenize(const std::string &input) const;
        void handleCommand(const std::string &command);

        bool running;
    };

} // namespace rdbms

#endif // RDBMS_CLI_HPP
