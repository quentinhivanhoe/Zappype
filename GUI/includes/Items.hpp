/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** Items
*/

#ifndef ITEMS_HPP_
    #define ITEMS_HPP_
    #include "Drawable.hpp"
    #include "Tile.hpp"
namespace Zappy
{
    class Items
    {
    private:
        size_t _id;
        Drawable _sprite;
        sf::Text quantity;
    public:
        Drawable &getSprite(){return _sprite;};
        Items(std::string fileName, size_t id);
        ~Items();
    };
    
  
    
}

#endif /* !ITEMS_HPP_ */
