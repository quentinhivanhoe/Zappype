/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Core
*/

#include "../includes/Core.hpp"


Zappy::Core::Core(int argc, char **argv)
{
    bool isDebugging = false;
    if (argc > 1) {
        if (std::string(argv[1]) == "-d")
            isDebugging = true;
    }
    this->_gui = std::make_shared<GUI>(isDebugging);
}

Zappy::Core::~Core()
{
}
