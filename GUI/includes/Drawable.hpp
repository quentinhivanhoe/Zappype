/*
** EPITECH PROJECT, 2025
** Zappype
** File description:
** Drawable
*/

#ifndef DRAWABLE_HPP_
#define DRAWABLE_HPP_
    #include "SFML/Graphics.hpp"
    #include "Math/Vector2D.hpp"
    #include <algorithm>
namespace Zappy
{
    class Drawable {
        private:
            sf::Texture _texture;
            sf::Sprite _sprite;
            std::vector<Vector2D> offsets;

        public:
            Drawable(std::string texture_path = "../GUI/assets/default.jpeg", float scale = 1.0);
            ~Drawable();
            sf::Texture &getTexture(){return this->_texture;};
            sf::Sprite &getSprite(){return this->_sprite;};
            void set_offsets();
            std::vector<Vector2D> get_offsets(){return this->offsets;};
            void setTexture(sf::Texture texture);
            void setSprite(sf::Sprite sprite);
    };
}

#endif /* !DRAWABLE_HPP_ */
