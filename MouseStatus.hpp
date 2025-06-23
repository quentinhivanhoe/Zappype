/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** mouse class
*/

#ifndef MOUSE_H
    #define MOUSE_H
    #include <SFML/Graphics.hpp>
    #include <iostream>

namespace Zappy
{
    class MouseStatus
    {
        private:
            bool _pressed;
            bool _hold;
            bool _released;
            sf::RectangleShape _hitbox;
        public:
            MouseStatus();
            inline ~MouseStatus() = default;

            inline bool pressed() const { return this->_pressed;};
            inline bool hold() const { return this->_hold;};
            inline bool released() const { return this->_released;};
            inline void setPressed(bool status) { this->_pressed = status; };
            inline void setHold(bool status) { this->_hold = status; };
            inline void setReleased(bool status) { this->_released = status; };

            inline void show(sf::RenderWindow &window) { window.draw(this->_hitbox); };
            bool hover(sf::RectangleShape other);
            void update(sf::RenderWindow &window);
    };
} // namespace Zappy

#endif /* !MOUSE_H */
