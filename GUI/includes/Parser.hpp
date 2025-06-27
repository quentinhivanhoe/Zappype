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
            void managePPO(std::vector<std::string> args, Network *network);
            void managePLV(std::vector<std::string> args, Network *network);
            void managePIN(std::vector<std::string> args, Network *network);
            void manageSGT(std::vector<std::string> args, Network *network);
            void manageSST(std::vector<std::string> args, Network *network);
            void managePNW(std::vector<std::string> args, Network *network);
            void managePEX(std::vector<std::string> args, Network *network);
            void managePBC(std::vector<std::string> args, Network *network);
            void managePIC(std::vector<std::string> args, Network *network);
            void managePIE(std::vector<std::string> args, Network *network);
            void managePFK(std::vector<std::string> args, Network *network);
            void managePDR(std::vector<std::string> args, Network *network);
            void managePGT(std::vector<std::string> args, Network *network);
            void managePDI(std::vector<std::string> args, Network *network);
            void manageENW(std::vector<std::string> args, Network *network);
            void manageEBO(std::vector<std::string> args, Network *network);
            void manageELS(std::vector<std::string> args, Network *network);
            void manageEDI(std::vector<std::string> args, Network *network);
            void manageSEG(std::vector<std::string> args, Network *network);
            void manageSMG(std::vector<std::string> args, Network *network);
            void manageSUC(std::vector<std::string> args, Network *network);
            void manageSBP(std::vector<std::string> args, Network *network);
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
            static std::vector<std::string> argsToString(std::vector<int> args);
            static void showArgs(std::vector<std::string> args);
            void manageResponse(std::vector<std::string> args, Network *network);
    };
} // namespace Zappy

#endif /* !PARSER_H */
