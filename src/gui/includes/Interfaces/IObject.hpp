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

            /**
             * @brief Get the Type object
             * 
             * @return std::string 
             */
            virtual std::string getType() const = 0;

            /**
             * @brief Get the Name object
             * 
             * @return std::string 
             */
            virtual std::string getName() const = 0;

            /**
             * @brief Get the Density object
             * 
             * @return double 
             */
            virtual double getDensity() const = 0;

            /**
             * @brief Set the Type object
             * 
             * @param type 
             */
            virtual void setType(std::string type) = 0;

            /**
             * @brief Set the Name object
             * 
             * @param name 
             */
            virtual void setName(std::string name) = 0;

            /**
             * @brief Set the Density object
             * 
             * @param density 
             */
            virtual void setDensity(double density) = 0;
    };
}

#endif /* !IOBJECT_HPP_ */
