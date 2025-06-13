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
    #include <iostream>
    #include <memory>
namespace Zappy
{
    class Items
    {
    private:
        size_t _id;
        std::shared_ptr<Drawable> _sprite;
        sf::Text quantity;
    public:
        std::shared_ptr<Drawable> getSprite(){return _sprite;};
        Items(std::string fileName, size_t id);
        ~Items();
    };
    
  
    
}

#endif /* !ITEMS_HPP_ */
