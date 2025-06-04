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
        std::string getName() const {return this->_name;};
        void setName(std::string name){this->_name = name;};
        void setFunction(std::function<const int&()> function){this->_function = function;};
        void function(const int& param);

    };
}
#endif /* !ACTIONS_HPP_ */
