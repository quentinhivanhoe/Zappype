/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** Player
*/

#ifndef PLAYER_HPP_
    #define PLAYER_HPP_
    #include <memory>
    #include <iostream>
    #include <SFML/Graphics.hpp>
    #include "Math/Vector2D.hpp"
    #include "Actions.hpp"
    #include "Interfaces/IObject.hpp"
namespace Zappy 
{
    class Player
    {
    private:
        std::string _teamName;
        size_t _id;
        size_t _level;
        std::vector<Actions> _actions;
        size_t _lifespan;
        sf::Color _color;
        Vector2D _pos;
        std::vector<std::shared_ptr<IObject>> _stones;
        std::vector<std::shared_ptr<IObject>> _foods;
    public:
        sf::RectangleShape shape;
        sf::Clock _clock;
        /*GETTER*/
        std::vector<std::shared_ptr<IObject>> getStones() const {return this->_stones;};
        std::vector<std::shared_ptr<IObject>> getFoods() const {return this->_foods;};
        std::string getTeamName() const {return this->_teamName;};
        size_t getID() const {return this->_id;};
        size_t getLevel() const {return this->_level;};
        size_t getLifespan() const {return this->_lifespan;};
        std::vector<Actions> getAction() const {return this->_actions;};
        Vector2D getPos() const {return this->_pos;};
        sf::Color getColor() const {return this->_color;};
        /*SETTER*/
        void setTeamName(std::string teamName) {this->_teamName = teamName;};
        void setId(size_t id) {this->_id = id;};
        void setLevel(size_t level) {this->_level = level;};
        void setLifeSpan(size_t lifeSpan) {this->_lifespan = lifeSpan;};
        void setColor(sf::Color color) {this->_color = color;};
        void setPos(Vector2D pos) {this->_pos = pos;};
        Player(/* args */);
        ~Player();
    }; 
}

#endif /* !PLAYER_HPP_ */
