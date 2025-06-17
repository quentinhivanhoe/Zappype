/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** Trantorian
*/

#ifndef Trantorian_HPP_
    #define Trantorian_HPP_
    #include <memory>
    #include <iostream>
    #include <SFML/Graphics.hpp>
    #include "Math/Vector2D.hpp"
    #include "Actions.hpp"
    #include "Interfaces/IObject.hpp"
    #include "Drawable.hpp"
    #include "Tile.hpp"
namespace Zappy 
{
    class Trantorian
    {
    private:
        std::string _teamName;
        size_t _id;
        size_t _level;
        std::vector<Actions> _actions;
        std::shared_ptr<Drawable> _sprite;
        size_t _lifespan;
        sf::Color _color;
        Vector2D _pos;
        Tile _inventory;
    public:
        sf::RectangleShape shape;
        sf::Clock _clock;
        /*GETTER*/
        Tile getInventory() {return this->_inventory;};
        std::string getTeamName() const {return this->_teamName;};
        size_t getID() const {return this->_id;};
        size_t getLevel() const {return this->_level;};
        size_t getLifespan() const {return this->_lifespan;};
        std::vector<Actions> getAction() const {return this->_actions;};
        Vector2D getPos() const {return this->_pos;};
        sf::Color getColor() const {return this->_color;};
        std::shared_ptr<Drawable> getSprite() {return this->_sprite;};
        /*SETTER*/
        void setTeamName(std::string teamName) {this->_teamName = teamName;};
        void setId(size_t id) {this->_id = id;};
        void setLevel(size_t level) {this->_level = level;};
        void setLifeSpan(size_t lifeSpan) {this->_lifespan = lifeSpan;};
        void setColor(sf::Color color) {this->_color = color;};
        void setPos(Vector2D pos) {this->_pos = pos;};
        Trantorian(/* args */);
        ~Trantorian();
    }; 
}

#endif /* !Trantorian_HPP_ */
