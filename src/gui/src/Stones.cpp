/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** Stones
*/

#include "../includes/Stones.hpp"

Zappy::Stones::Stones(std::string name, std::string type, double density)
{
    this->setDensity(density);
    this->setName(name);
    this->setType(type);
}
    
Zappy::Stones::~Stones()
{
}