/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Egg header
*/

#ifndef EGG_H
    #define EGG_H
    #include "Drawable.hpp"
    #include <memory>
    #include <string>
namespace Zappy
{
    class Egg
    {
        private:
            std::shared_ptr<Drawable> _drawable;
            size_t _id;
            sf::Vector2f _pos;
            sf::Vector2i _indexPos;
            std::string _teamName;
        public:
            Egg(size_t id = 0, sf::Vector2i indexPos = {0, 0}, const std::string& teamName = "default");
            inline ~Egg() = default;
            inline std::shared_ptr<Drawable> getDrawable() const { return this->_drawable; };
            inline void setId(size_t id) { this->_id = id; };
            inline void setPos(sf::Vector2f pos) { this->_pos = pos; };
            inline void setIndexPos(sf::Vector2i pos) { this->_indexPos= pos; };
            inline void setTeamName(const std::string& name) { this->_teamName = name; };
            inline sf::Vector2f getPos() const { return this->_pos; };
            inline sf::Vector2i getIndexPos() const { return this->_indexPos; };
            inline std::string getTeamName() const { return this->_teamName; };
            inline size_t getId() const { return this->_id; };
    };
} // namespace Zappy


#endif /* !EGG_H */
