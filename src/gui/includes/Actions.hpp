/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** Actions
*/

#ifndef ACTIONS_HPP_
    #define ACTIONS_HPP_
    #include "iostream"
    #include "functional"
namespace Zappy {
    class Actions
    {
    private:
        std::string _name;
        std::function<const int&()> _function;
    public:
        Actions(/* args */);
        ~Actions();

        /**
         * @brief Get the Name object
         * 
         * @return std::string 
         */
        inline std::string getName() const {return this->_name;};

        /**
         * @brief Set the Name object
         * 
         * @param name 
         */
        inline void setName(std::string name){this->_name = name;};

        /**
         * @brief Set the Function object
         * 
         * @param function 
         */
        inline void setFunction(std::function<const int&()> function){this->_function = function;};

        /**
         * @brief Call the function of the Action (deprecated)
         * 
         * @param param 
         */
        void function(const int& param);

    };
}
#endif /* !ACTIONS_HPP_ */
