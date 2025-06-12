/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Parser functions
*/

#include "../includes/Parser.hpp"

std::vector<std::string> Zappy::Parser::parseLine(const std::string& line, char delimiter)
{
    std::vector<std::string> tab;
    std::string temp = line;
    while (temp.find('\n') != temp.npos)
        temp.replace(temp.find('\n'), 1, " ");
    std::stringstream tempLine(temp);
    std::string element;
    while (std::getline(tempLine, element, delimiter))
        if (!element.empty())
            tab.push_back(element);
    return tab;
}

void Zappy::Parser::showArgs(std::vector<std::string> args)
{
    std::cout << "{";
    for (size_t i = 0; i < args.size(); i++) {
        std::cout << args[i];
        if (i + 1 < args.size())
            std::cout << ", ";
    }
    std::cout << "}" << std::endl;
}

void Zappy::Parser::manageResponse(std::vector<std::string> args, Zappy::Network *network)
{
    std::map<std::string, void (Zappy::Parser:: *)(std::vector<std::string>, Network *)> funcTab = {
        {"msz", &Zappy::Parser::manageMSZ},
        {"spi", &Zappy::Parser::manageMSZ},
        {"spn", &Zappy::Parser::manageMSZ},
        {"bct", &Zappy::Parser::manageMSZ},
    };
    if (funcTab[args.front()])
        (this->*funcTab[args.front()])(args, network);
    else
        std::cout << "response not found" << std::endl;
}

bool Zappy::Parser::isNum(const std::string& string)
{
    std::regex regExp("[0-9]+");
    return std::regex_match(string, regExp);
}

bool Zappy::Parser::isIndex(const std::string& string)
{
    std::regex regExp("#[0-9]+");
    return std::regex_match(string, regExp);
}

//----------------------------------------------------------------------//

void Zappy::Parser::manageMSZ([[maybe_unused]] std::vector<std::string> args, [[maybe_unused]] Zappy::Network *network)
{
    if (args.size() != 3) {
        std::cout << "Wrong number of args, response failed." << std::endl;
        return;
    }
    if (!Parser::isNum(args[1]) || !Parser::isNum(args[2])) {
        std::cout << "Args must be positive numbers." << std::endl;
        return;
    }
    network->setMapSize({std::stoi(args[1]), std::stoi(args[2])});
}

void Zappy::Parser::manageBCT([[maybe_unused]] std::vector<std::string> args, [[maybe_unused]] Zappy::Network *network)
{
    Parser::showArgs(args);
    if (args.size() != 10) {
        std::cout << "Wrong number of args, response failed." << std::endl;
        return;
    }
    for (size_t i = 1; i < args.size(); i++) {
        if (!Parser::isNum(args[i])) {
            std::cout << "Args must be positive numbers." << std::endl;
            return;
        }
    }
    Parser::showArgs(args);
}

void Zappy::Parser::manageSPN([[maybe_unused]] std::vector<std::string> args, [[maybe_unused]] Zappy::Network *network)
{
    if (args.size() != 2) {
        std::cout << "Wrong number of args, response failed." << std::endl;
        return;
    }
    if (!Parser::isNum(args[1])) {
        std::cout << "Args must be positive numbers." << std::endl;
        return;
    }
    network->setPlayerNb(std::stoi(args[1]));
}

void Zappy::Parser::manageSPI([[maybe_unused]] std::vector<std::string> args, [[maybe_unused]] Zappy::Network *network)
{
    if (args.size() != 8) {
        std::cout << "Wrong number of args, response failed." << std::endl;
        return;
    }
    if (!Parser::isIndex(args[1])) {
        std::cout << "Index must be a # followed by a positive number." << std::endl;
        return;
    }
    for (size_t i = 2; i < args.size(); i++) {
        if (!Parser::isNum(args[i])) {
            std::cout << "Args must be positive numbers." << std::endl;
            return;
        }
    }
    Parser::showArgs(args);
}
