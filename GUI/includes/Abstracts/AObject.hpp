/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** AObject
*/

#ifndef AOBJECT_HPP_
    #define AOBJECT_HPP_
    #include "../Interfaces/IObject.hpp"
    #include "SFML/Graphics.hpp"

namespace Zappy
{
    class AObject : public IObject
    {
    private:
        std::string _type;
        std::string _name;
        double _density;
        sf::RectangleShape shape;
        sf::Color color;
    public:
        AObject(/* args */);
        ~AObject();
        inline std::string getType() const {return this->_type;};
        inline std::string getName() const {return this->_name;};
        inline double getDensity() const {return this->_density;};
        inline void setType(std::string type) {this->_type = type;};
        inline void setName(std::string name) {this->_name = name;};
        inline void setDensity(double density) {this->_density = density;};
        
    };
}

#endif /* !AOBJECT_HPP_ */
