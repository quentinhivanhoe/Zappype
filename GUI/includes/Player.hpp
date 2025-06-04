/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** Player
*/

#ifndef PLAYER_HPP_
    #define PLAYER_HPP_
    #include "iostream"
    #include "SFML/Graphics.hpp"
namespace Zappy 
{
    class Player
    {
    private:
        std::string _teamName;
        size_t _id;
        size_t _level;
        std::string _actions;
        size_t _lifespan;
        sf::Clock _clock;
    public:
        Player(/* args */);
        ~Player();
    }; 
}

#endif /* !PLAYER_HPP_ */
