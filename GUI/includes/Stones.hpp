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
    class Stones : public AObject
    {
    private:
    public:
        Stones(std::string name, std::string type, double density);
        ~Stones();
    };
    
    Stones::Stones(std::string name, std::string type, double density)
    {
    }
    
    Stones::~Stones()
    {
    }
    
}

#endif /* !STONES_HPP_ */
