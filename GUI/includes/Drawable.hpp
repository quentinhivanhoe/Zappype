/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** Drawable
*/

#ifndef DRAWABLE_HPP_
#define DRAWABLE_HPP_
    #include "SFML/Graphics.hpp"
namespace Zappy
{
    class Drawable {
        private:
            sf::Texture _texture;
            sf::Sprite _sprite;
        public:
            Drawable(const char *texture_path = "../GUI/assets/default.jpeg");
            ~Drawable();
            sf::Texture &getTexture(){return this->_texture;};
            sf::Sprite &getSprite(){return this->_sprite;};
            void setTexture(sf::Texture texture);
            void setSprite(sf::Sprite sprite);
    };
}

#endif /* !DRAWABLE_HPP_ */
