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
            /**
             * @brief Manage the map size command
             * 
             * @param args 
             * @param network 
             */
            void manageMSZ(std::vector<std::string> args, Network *network);

            /**
             * @brief manage the tile content command
             * 
             * @param args 
             * @param network 
             */
            void manageBCT(std::vector<std::string> args, Network *network);

            /**
             * @brief manage the player position command
             * 
             * @param args 
             * @param network 
             */
            void managePPO(std::vector<std::string> args, Network *network);

            /**
             * @brief manage the payer level command
             * 
             * @param args 
             * @param network 
             */
            void managePLV(std::vector<std::string> args, Network *network);

            /**
             * @brief manage the player inventory command
             * 
             * @param args 
             * @param network 
             */
            void managePIN(std::vector<std::string> args, Network *network);

            /**
             * @brief manage the server time unit requet command
             * 
             * @param args 
             * @param network 
             */
            void manageSGT(std::vector<std::string> args, Network *network);

            /**
             * @brief manage the server time modification command
             * 
             * @param args 
             * @param network 
             */
            void manageSST(std::vector<std::string> args, Network *network);

            /**
             * @brief manage the new player command
             * 
             * @param args 
             * @param network 
             */
            void managePNW(std::vector<std::string> args, Network *network);

            /**
             * @brief manage the expulsion of the player
             * 
             * @param args 
             * @param network 
             */
            void managePEX(std::vector<std::string> args, Network *network);

            /**
             * @brief manage the broadcast from a player command
             * 
             * @param args 
             * @param network 
             */
            void managePBC(std::vector<std::string> args, Network *network);

            /**
             * @brief manage the start of incantation command
             * 
             * @param args 
             * @param network 
             */
            void managePIC(std::vector<std::string> args, Network *network);

            /**
             * @brief manage the end of incantation command
             * 
             * @param args 
             * @param network 
             */
            void managePIE(std::vector<std::string> args, Network *network);

            /**
             * @brief Manage the forking command
             * 
             * @param args 
             * @param network 
             */
            void managePFK(std::vector<std::string> args, Network *network);

            /**
             * @brief manage the player drop item command
             * 
             * @param args 
             * @param network 
             */
            void managePDR(std::vector<std::string> args, Network *network);

            /**
             * @brief manage the player get item command
             * 
             * @param args 
             * @param network 
             */
            void managePGT(std::vector<std::string> args, Network *network);

            /**
             * @brief manage death of player command
             * 
             * @param args 
             * @param network 
             */
            void managePDI(std::vector<std::string> args, Network *network);

            /**
             * @brief manage new egg command
             * 
             * @param args 
             * @param network 
             */
            void manageENW(std::vector<std::string> args, Network *network);

            /**
             * @brief manage birth of player from egg command
             * 
             * @param args 
             * @param network 
             */
            void manageEBO(std::vector<std::string> args, Network *network);

            /**
             * @brief manage egg list command
             * 
             * @param args 
             * @param network 
             */
            void manageELS(std::vector<std::string> args, Network *network);

            /**
             * @brief manage egg death command
             * 
             * @param args 
             * @param network 
             */
            void manageEDI(std::vector<std::string> args, Network *network);

            /**
             * @brief manage end of game commmand
             * 
             * @param args 
             * @param network 
             */
            void manageSEG(std::vector<std::string> args, Network *network);

            /**
             * @brief manage server message command
             * 
             * @param args 
             * @param network 
             */
            void manageSMG(std::vector<std::string> args, Network *network);

            /**
             * @brief manage server unknown command 
             * 
             * @param args 
             * @param network 
             */
            void manageSUC(std::vector<std::string> args, Network *network);

            /**
             * @brief manage server bad parameters command
             * 
             * @param args 
             * @param network 
             */
            void manageSBP(std::vector<std::string> args, Network *network);

            /**
             * @brief manage player list command
             * 
             * @param args 
             * @param network 
             */
            void manageSPI(std::vector<std::string> args, Network *network);

            /**
             * @brief manage player number command
             * 
             * @param args 
             * @param network 
             */
            void manageSPN(std::vector<std::string> args, Network *network);

            /**
             * @brief manage egg number command
             * 
             * @param args 
             * @param network 
             */
            void manageENU(std::vector<std::string> args, Network *network);
        public:
            inline Parser() = default;
            inline ~Parser() = default;

            /**
             * @brief Is num function
             * 
             * @param string 
             * @return true 
             * @return false 
             */
            static bool isNum(const std::string& string);

            /**
             * @brief is index function : exemple -> #1
             * 
             * @param string 
             * @return true 
             * @return false 
             */
            static bool isIndex(const std::string& string);

            /**
             * @brief get the occurences number of a key in the string
             * 
             * @param string 
             * @param key 
             * @return size_t 
             */
            static size_t nbOccur(const std::string& string, const std::string& key);

            /**
             * @brief spplit the line into a vector
             * 
             * @param string 
             * @param sep 
             * @return std::vector<std::string> 
             */
            static std::vector<std::string> splitLine(const std::string& string, const std::string& sep);

            /**
             * @brief Parse the line to transform it into a vector
             * 
             * @param line 
             * @param delimiter 
             * @return std::vector<std::string> 
             */
            static std::vector<std::string> parseLine(const std::string& line, char delimiter);

            /**
             * @brief transorm a vector of int into a vector of string
             * 
             * @param args 
             * @return std::vector<std::string> 
             */
            static std::vector<std::string> argsToString(std::vector<int> args);

            /**
             * @brief show the elements of the given vector
             * 
             * @param args 
             */
            static void showArgs(std::vector<std::string> args);

            /**
             * @brief Manage globally any response from the server
             * 
             * @param args 
             * @param network 
             */
            void manageResponse(std::vector<std::string> args, Network *network);
    };
} // namespace Zappy

#endif /* !PARSER_H */
