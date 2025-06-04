/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** AObject
*/

#ifndef AOBJECT_HPP_
    #define AOBJECT_HPP_
    #include "../Interfaces/IObject.hpp"

namespace Zappy
{
    class AObject : public IObject
    {
    private:
        std::string _type;
        std::string _name;
        double _density;
    public:
        AObject(/* args */);
        ~AObject();
        std::string getType() const {return this->_type;};
        std::string getName() const {return this->_name;};
        double getDensity() const {return this->_density;};
        void setType(std::string type) {this->_type = type;};
        void setName(std::string name) {this->_name = name;};
        void setDensity(double density) {this->_density = density;};
        
    };
}

#endif /* !AOBJECT_HPP_ */
