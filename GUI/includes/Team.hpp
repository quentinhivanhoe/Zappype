/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** Team
*/

#ifndef TEAM_HPP_
    #define TEAM_HPP_
    #include "Trantor.hpp"
namespace Zappy
{
    class Team
    {
        private:
            std::vector<Trantorian> _Trantorians;
            std::string _teamName;
        public:
            Team(std::string teamName);
            ~Team();
            std::vector<Trantorian> getTrantorian() const {return this->_Trantorians;};
            std::string getTeamName() const {return this->_teamName;};
    };
}

#endif /* !TEAM_HPP_ */
