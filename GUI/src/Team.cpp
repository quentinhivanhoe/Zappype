/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** Teams
*/

#include "../includes/Team.hpp"


Zappy::Team::Team(std::string teamName)
{
    this->_teamName = teamName;
    this->_Trantorians.push_back(std::make_shared<Trantorian>());
}
    
Zappy::Team::~Team()
{
}
    