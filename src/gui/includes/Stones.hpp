/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** Stones
*/

#ifndef STONES_HPP_
    #define STONES_HPP_
    #include "Abstracts/AObject.hpp"
namespace Zappy
{
    enum StoneType {
        LINEMATE = 0,
        DERAUMERE = 1,
        SIBUR = 2,
        MENDIANE = 3,
        PHIRAS = 4,
        THYSTAME = 5
    };
    class Stones : public AObject
    {
        private:
            StoneType _type;
        public:
            Stones(std::string name, std::string type, double density);
            ~Stones();
    };
}

#endif /* !STONES_HPP_ */
