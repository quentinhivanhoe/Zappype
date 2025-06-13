/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** parser header
*/

#ifndef PARSER_H
    #define PARSER_H
    #include <iostream>
    #include <vector>
    #include <string>
    #include <iomanip>
    #include <memory>
    #include <regex>
    #include "GUI.hpp"
namespace Zappy
{
    class GUI;
    class Network;
    class Parser
    {
        private:
            void manageMSZ(std::vector<std::string> args, Network *network);
            void manageBCT(std::vector<std::string> args, Network *network);
            void manageSPI(std::vector<std::string> args, Network *network);
            void manageSPN(std::vector<std::string> args, Network *network);
        public:
            inline Parser() = default;
            inline ~Parser() = default;

            static bool isNum(const std::string& string);
            static bool isIndex(const std::string& string);
            static size_t nbOccur(const std::string& string, const std::string& key);
            static std::vector<std::string> splitLine(const std::string& string, const std::string& sep);
            static std::vector<std::string> parseLine(const std::string& line, char delimiter);
            static void showArgs(std::vector<std::string> args);
            void manageResponse(std::vector<std::string> args, Network *network);
    };
} // namespace Zappy

#endif /* !PARSER_H */
