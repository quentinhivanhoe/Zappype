/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** main
*/

#include "../includes/Core.hpp"

int main([[maybe_unused]]int argc, [[maybe_unused]]char **argv)
{
    try {
        Zappy::Core core(argc, argv);
    } catch(const Zappy::Error &e) {
        std::cerr << "Zappy Exception - [From : " << e.where() << "] - [" << e.what() << "]" << std::endl;
    }
    return 0;
}
