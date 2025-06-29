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
            Drawable(std::string texture_path = "assets/default.jpeg", float scale = 1.0);
            ~Drawable();

            /**
             * @brief Get the Texture object
             * 
             * @return sf::Texture& 
             */
            inline sf::Texture &getTexture(){return this->_texture;};

            /**
             * @brief Get the Sprite object
             * 
             * @return sf::Sprite& 
             */
            inline sf::Sprite &getSprite(){return this->_sprite;};

            /**
             * @brief Set the offsets object
             * 
             */
            void set_offsets();

            /**
             * @brief Get the offsets object
             * 
             * @return std::vector<Vector2D> 
             */
            std::vector<Vector2D> get_offsets(){return this->offsets;};

            /**
             * @brief Shuffle the given tab
             * 
             * @param tab 
             * @param seed 
             */
            void shuffler(std::vector<Vector2D> tab, unsigned seed);

            /**
             * @brief Set the Texture object
             * 
             * @param texture 
             */
            void setTexture(sf::Texture texture);

            /**
             * @brief Update the texture from the given path
             * 
             * @param filepath 
             */
            void updateTextureFromPath(std::string filepath);

            /**
             * @brief Set the Sprite object
             * 
             * @param sprite 
             */
            void setSprite(sf::Sprite sprite);
    };
}

#endif /* !DRAWABLE_HPP_ */
