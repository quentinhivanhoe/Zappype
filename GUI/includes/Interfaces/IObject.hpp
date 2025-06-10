/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** IObject
*/

#ifndef IOBJECT_HPP_
    #define IOBJECT_HPP_
    #include "iostream"
namespace Zappy
{
    class IObject
    {
        public:
            virtual ~IObject(){};
            virtual std::string getType() const = 0;
            virtual std::string getName() const = 0;
            virtual double getDensity() const = 0;
            virtual void setType(std::string type) = 0;
            virtual void setName(std::string name) = 0;
            virtual void setDensity(double density) = 0;
    };
}

#endif /* !IOBJECT_HPP_ */
