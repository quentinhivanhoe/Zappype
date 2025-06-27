/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** Team
*/

#ifndef TEAM_HPP_
    #define TEAM_HPP_
    #include "Trantor.hpp"
    #include "Egg.hpp"
namespace Zappy
{
    class Trantorian;
    class TrantorButtons;
    class Team
    {
        private:
            std::vector<std::shared_ptr<Trantorian>> _trantorians;
            std::vector<std::shared_ptr<Egg>> _eggs;
            std::string _teamName;
        public:
            Team(std::string teamName);
            ~Team();
            inline std::vector<std::shared_ptr<Trantorian>> getTrantorians() const {return this->_trantorians;};
            inline std::vector<std::shared_ptr<Egg>> getEggs() const {return this->_eggs;};
            inline std::string getTeamName() const {return this->_teamName;};
            inline void addTrantorian(std::shared_ptr<Trantorian> trantorian) { this->_trantorians.push_back(trantorian); };
            inline void addEgg(std::shared_ptr<Egg> egg) { this->_eggs.push_back(egg); };
    };
}

#endif /* !TEAM_HPP_ */
