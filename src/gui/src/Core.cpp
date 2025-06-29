/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Core
*/

#include "../includes/Core.hpp"


Zappy::Core::Core()
{
    this->_gui = std::make_shared<GUI>();
}

Zappy::Core::~Core()
{
}
