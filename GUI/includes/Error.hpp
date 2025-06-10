/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Error header
*/

#ifndef ERROR_H
    #define ERROR_H
    #include <exception>
    #include <string>

namespace Zappy
{
    class Error : public std::exception
    {
        private:
            std::string _what;
            std::string _where;
        public:
            inline Error(const std::string& what, const std::string& where) : _what(what), _where(where) {};
            inline ~Error() = default;
            inline const char *what() const noexcept { return this->_what.c_str(); };
            inline const char *where() const noexcept { return this->_where.c_str(); };
    };
} // namespace Zappy

#endif /* !ERROR_H */
