/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** Tile
*/

#ifndef TILE_HPP_
    #define TILE_HPP_
    #include <iostream>
    #include <vector>
    #include <memory>
    #include <SFML/Graphics.hpp>
    #include "Math/Vector2D.hpp"
    #include "GUI.hpp"
    #include "TileButtons.hpp"
    #include "Drawable.hpp"

namespace Zappy
{
    enum Item {
        EGG = 0,
        FOOD = 1,
        LINEMATE = 2,
        DERAUMERE = 3,
        SIBUR = 4,
        MENDIANE = 5,
        PHIRAS = 6,
        THYSTAME = 7,
    };
    class Tile
    {
    private:
        size_t _id;
        std::vector<size_t> _items;
        std::vector<Vector2D> offsets_list;
        Vector2D _pos;
        Vector2D _center;
        sf::Vector2i _index;
        std::shared_ptr<Drawable>_tile = std::make_shared<Drawable>("assets/map.png", 0.5 * 3.07);
        std::shared_ptr<TileButtons> _innerButton = nullptr;
        bool _activity = false;
    public:
        Tile(size_t id = -1);
        ~Tile();

        /**
         * @brief Get the number of the given item
         * 
         * @param name 
         * @return size_t 
         */
        size_t getNItem(Item name);

        /**
         * @brief Get the Id object
         * 
         * @return size_t 
         */
        size_t getId() const {return this->_id;};

        /**
         * @brief Set the number of the given item
         * 
         * @param name 
         * @param value 
         */
        void setNItem(Item name, size_t value);

        /**
         * @brief init the button of the tile
         * 
         * @param gui 
         * @param tile 
         */
        void initButton(GUI *gui, std::shared_ptr<Tile> tile);
        
        /**
         * @brief Set the Offsets List object
         * 
         * @param offsets 
         */
        void setOffsetsList(std::vector<Vector2D> offsets);

        /**
         * @brief Get the Offsets List object
         * 
         * @return std::vector<Vector2D> 
         */
        inline std::vector<Vector2D> getOffsetsList() {return this->offsets_list;};

        /**
         * @brief Get the Items object
         * 
         * @return std::vector<size_t> 
         */
        inline std::vector<size_t> getItems(){return this->_items;};

        /**
         * @brief Get the Pos object
         * 
         * @return Vector2D 
         */
        inline Vector2D getPos() const {return this->_pos;};

        /**
         * @brief Get the Tile object
         * 
         * @return std::shared_ptr<Drawable> 
         */
        inline std::shared_ptr<Drawable> getTile() {return this->_tile;};

        /**
         * @brief Set the Pos object
         * 
         * @param pos 
         * @return * void 
         */
        inline void setPos(Vector2D pos) {this->_pos = pos;};

        /**
         * @brief Get the Center object
         * 
         * @return Vector2D 
         */
        inline Vector2D getCenter() const {return this->_center;};

        /**
         * @brief Set the Center object
         * 
         * @param Center 
         */
        inline void setCenter(Vector2D Center) {this->_center = Center;};
        /**
         * @brief Get the Activity object
         * 
         * @return true 
         * @return false 
         */
        inline bool getActivity() const {return this->_activity;};

        /**
         * @brief Set the Activity object
         * 
         * @param activity 
         */
        inline void setActivity(bool activity) {this->_activity = activity;};

        /**
         * @brief Set the Index object
         * 
         * @param index 
         */
        inline void setIndex(sf::Vector2i index) { this->_index = index; };

        /**
         * @brief Get the Index object
         * 
         * @return sf::Vector2i 
         */
        inline sf::Vector2i getIndex() const { return this->_index; };

        /**
         * @brief Get the Button object
         * 
         * @return std::shared_ptr<TileButtons> 
         */
        inline std::shared_ptr<TileButtons> getButton() const { return this->_innerButton; };
    }; 
}

#endif /* !TILE_HPP_ */
