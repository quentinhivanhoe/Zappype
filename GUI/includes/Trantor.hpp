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
        bool _isElevating = false;
        bool _isIdling = true;
        bool _isDead = false;
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
        std::string _state;
        sf::IntRect _textureRect;
        sf::Clock _innerClock;
        int _maxSizeDead = 2304 - 256;
        int _maxSizeElevating = 1024;

    public:
        sf::RectangleShape shape;
        sf::Clock _clock;

        /*GETTER*/

        /**
         * @brief Get the Inventory object
         * 
         * @return std::shared_ptr<Tile> 
         */
        inline std::shared_ptr<Tile> getInventory() {return this->_inventory;};

        /**
         * @brief Get the Team Name object
         * 
         * @return std::string 
         */
        inline std::string getTeamName() const {return this->_teamName;};

        /**
         * @brief 
         * 
         * @return size_t 
         */
        inline size_t getID() const {return this->_id;};

        /**
         * @brief Get the Level object
         * 
         * @return size_t 
         */
        inline size_t getLevel() const {return this->_level;};

        /**
         * @brief Get the Lifespan object
         * 
         * @return size_t 
         */
        inline size_t getLifespan() const {return this->_lifespan;};

        /**
         * @brief Get the Action object
         * 
         * @return std::vector<Actions> 
         */
        inline std::vector<Actions> getAction() const {return this->_actions;};

        /**
         * @brief Get the Pos object
         * 
         * @return Vector2D 
         */
        inline Vector2D getPos() const {return this->_pos;};

        /**
         * @brief Get the Direction object
         * 
         * @return size_t 
         */
        inline size_t getDirection() const { return this->_direction; };

        /**
         * @brief Get the Color object
         * 
         * @return sf::Color 
         */
        inline sf::Color getColor() const {return this->_color;};

        /**
         * @brief Get the Sprite object
         * 
         * @return std::shared_ptr<Drawable> 
         */
        inline std::shared_ptr<Drawable> getSprite() {return this->_sprite;};

        /**
         * @brief Get the Tile Pos object
         * 
         * @return sf::Vector2i 
         */
        inline sf::Vector2i getTilePos() const { return this->_tilePos; };

        /**
         * @brief Get the State object
         * 
         * @return std::string 
         */
        inline std::string getState() const { return this->_state; };

        /*SETTER*/

        /**
         * @brief Set the Team Name object
         * 
         * @param teamName 
         */
        inline void setTeamName(std::string teamName) {this->_teamName = teamName;};

        /**
         * @brief Set the Id object
         * 
         * @param id 
         */
        inline void setId(size_t id) {this->_id = id;};

        /**
         * @brief Set the Level object
         * 
         * @param level 
         */
        inline void setLevel(size_t level) {this->_level = level;};

        /**
         * @brief Set the Life Span object
         * 
         * @param lifeSpan 
         */
        inline void setLifeSpan(size_t lifeSpan) {this->_lifespan = lifeSpan;};

        /**
         * @brief Set the Color object
         * 
         * @param color 
         */
        inline void setColor(sf::Color color) {this->_color = color;};

        /**
         * @brief Set the Pos object
         * 
         * @param pos 
         */
        inline void setPos(Vector2D pos) {this->_pos = pos;};

        /**
         * @brief Set the Direction object
         * 
         * @param direction 
         */
        inline void setDirection(size_t direction) {this->_direction = direction; };

        /**
         * @brief Set the Tile Pos object
         * 
         * @param pos 
         */
        inline void setTilePos(sf::Vector2i pos) { this->_tilePos = pos; };

        /**
         * @brief Set the State object
         * 
         * @param state 
         */
        inline void setState(const std::string& state) { this->_state = state; };

        /**
         * @brief Update the Trantorian Sprite for Animations
         * 
         */
        void updateTrantorSprite();

        /**
         * @brief Manage the sprite when the trantorian is dead
         * 
         */
        void manageDeadSprite();

        /**
         * @brief Manage the sprite when the trantorian is elevating
         * 
         */
        void manageElevatingSprite();

        /**
         * @brief Manage the sprite when the trantorian is idling
         * 
         */
        void manageIdleSprite();

        /**
         * @brief Kill the trantorian respectfully
         * 
         */
        void kill();

        /**
         * @brief Set the state of the trantorian to Idle
         * 
         */
        void idle();

        /**
         * @brief Elevate the Trantorian
         * 
         */
        void elevate();
        Trantorian(/* args */);
        ~Trantorian();
    }; 
}

#endif /* !Trantorian_HPP_ */
