/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** One Shot Animation Player Header
*/

#ifndef ONE_SHOT_ANIMATION_PLAYER_H
    #define ONE_SHOT_ANIMATION_PLAYER_H
    #include <memory>
    #include "Drawable.hpp"
namespace Zappy
{
    class OneShotAnimationPlayer
    {
        private:
            bool _alive = true;
            bool _isFading = false;
            std::string _path;
            std::shared_ptr<Drawable> _spriteSheet;
            sf::Clock _innerClock;
            sf::Vector2f _fullSize;
            sf::Vector2f _singleTileSize;
            sf::Vector2f _scale;
            int _frameRate;
            sf::IntRect _innerRect;
            sf::Vector2f _pos;
            int alphaValue = 255;
        public:
            OneShotAnimationPlayer(int framerate = {30}, sf::Vector2f scale = {1, 1}, sf::Vector2f singleTileSize = {100, 100}, sf::Vector2f fullSize = {100, 100}, sf::Vector2f pos = {100, 100}, const std::string& spritePath = "assets/default.jpeg");
            inline ~OneShotAnimationPlayer() = default;
            void update();
            inline bool isAlive() const { return this->_alive; };
            inline std::shared_ptr<Drawable> getDrawable() const { return this->_spriteSheet; };

    };
} // namespace Zappy

#endif /* !ONE_SHOT_ANIMATION_PLAYER_H */
