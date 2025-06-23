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
    #include "TrantorButtons.hpp"

namespace Zappy 
{
    class TrantorButtons;
    class Tile;
    class Trantorian
    {
    private:
        std::string _teamName = "default";
        size_t _id = 0;
        size_t _level = 0;
        size_t _direction = 0;
        std::vector<Actions> _actions;
        std::shared_ptr<Drawable> _sprite;
        size_t _lifespan = 0;
        sf::Color _color;
        Vector2D _pos;
        sf::Vector2i _tilePos;
        std::shared_ptr<Tile> _inventory;
        std::shared_ptr<TrantorButtons> _innerButton; 

    public:
        sf::RectangleShape shape;
        sf::Clock _clock;

        /*GETTER*/
        inline std::shared_ptr<Tile> getInventory() {return this->_inventory;};
        inline std::string getTeamName() const {return this->_teamName;};
        inline size_t getID() const {return this->_id;};
        inline size_t getLevel() const {return this->_level;};
        inline size_t getLifespan() const {return this->_lifespan;};
        inline std::vector<Actions> getAction() const {return this->_actions;};
        inline Vector2D getPos() const {return this->_pos;};
        inline size_t getDirection() const { return this->_direction; };
        inline sf::Color getColor() const {return this->_color;};
        inline std::shared_ptr<Drawable> getSprite() {return this->_sprite;};
        inline sf::Vector2i getTilePos() const { return this->_tilePos; };

        /*SETTER*/
        inline void setTeamName(std::string teamName) {this->_teamName = teamName;};
        inline void setId(size_t id) {this->_id = id;};
        inline void setLevel(size_t level) {this->_level = level;};
        inline void setLifeSpan(size_t lifeSpan) {this->_lifespan = lifeSpan;};
        inline void setColor(sf::Color color) {this->_color = color;};
        inline void setPos(Vector2D pos) {this->_pos = pos;};
        inline void setDirection(size_t direction) {this->_direction = direction; };
        inline void setTilePos(sf::Vector2i pos) { this->_tilePos = pos; };
        Trantorian(/* args */);
        ~Trantorian();
    }; 
}

#endif /* !Trantorian_HPP_ */
