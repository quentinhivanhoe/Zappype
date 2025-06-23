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
    #include <SFML/Graphics.hpp>
    #include "Math/Vector2D.hpp"
    #include "GUI.hpp"
    #include "TileButtons.hpp"
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
        std::shared_ptr<TileButtons> _innerButton = nullptr;
        bool _activity = false;
    public:
        Tile(size_t id = -1);
        ~Tile();
        size_t getNItem(Item name);
        size_t getId() const {return this->_id;};
        void setNItem(Item name, size_t value);
        void setOffsetsList(std::vector<Vector2D> offsets);
        inline std::vector<Vector2D> getOffsetsList() {return this->offsets_list;};
        inline std::vector<size_t> getItems(){return this->_items;};
        inline Vector2D getPos() const {return this->_pos;};
        inline void setPos(Vector2D pos) {this->_pos = pos;};
        inline Vector2D getCenter() const {return this->_center;};
        inline void setCenter(Vector2D Center) {this->_center = Center;};
        inline bool getActivity() const {return this->_activity;};
        inline void setActivity(bool activity) {this->_activity = activity;};
        inline void setIndex(sf::Vector2i index) { this->_index = index; };
        inline sf::Vector2i getIndex() const { return this->_index; };
    }; 
}

#endif /* !TILE_HPP_ */
