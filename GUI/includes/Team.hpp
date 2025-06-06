/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** Team
*/

#ifndef TEAM_HPP_
    #define TEAM_HPP_
    #include "Player.hpp"
namespace Zappy
{
    class Team
    {
    private:
        std::vector<Player> _players;
        std::string _teamName;
    public:
        Team(std::string teamName);
        ~Team();
        std::vector<Player> getPlayer() const {return this->_players;};
        std::string getTeamName() const {return this->_teamName;};
    };
}

#endif /* !TEAM_HPP_ */
