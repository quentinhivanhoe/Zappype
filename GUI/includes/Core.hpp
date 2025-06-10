/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Core header
*/

#ifndef CORE_H
    #define CORE_H
    #include "GUI.hpp"
    #include <iostream>
    #include "Error.hpp"

namespace Zappy
{
    class Core
    {
        private:
            int _argc;
            char **_argv;
            std::shared_ptr<GUI> _gui;
        public:
            Core(int argc = 0, char **argv = nullptr);
            ~Core();
    };
} // namespace Zappy


#endif /* !CORE_H */
