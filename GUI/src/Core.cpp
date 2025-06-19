/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Core
*/

#include "../includes/Core.hpp"


Zappy::Core::Core(int argc, char **argv)
{
    // if (argc < 2)
    //     throw Error("Not enough arguments. run ./zappy_gui \"ip\" \"port\"", "Core init");
    // if (!Parser::isNum(argv[2]))
    //     throw Error("Port must be a positive number.", "Core init");
    (void)argc;
    (void)argv;
    this->_gui = std::make_shared<GUI>();
}

Zappy::Core::~Core()
{
}
