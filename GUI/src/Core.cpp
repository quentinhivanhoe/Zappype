/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Core
*/

#include "../includes/Core.hpp"


Zappy::Core::Core(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    this->_gui = std::make_shared<GUI>();
}

Zappy::Core::~Core()
{
}
