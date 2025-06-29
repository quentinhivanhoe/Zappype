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
            bool _isForUi = true;
            sf::RectangleShape _hitbox;
        public:
            MouseStatus(bool isForUi = true);
            inline ~MouseStatus() = default;


            /**
             * @brief Get the pressed state of the mouse
             * 
             * @return true 
             * @return false 
             */
            inline bool pressed() const { return this->_pressed;};

            /**
             * @brief Get the hold state of the mouse
             * 
             * @return true 
             * @return false 
             */
            inline bool hold() const { return this->_hold;};

            /**
             * @brief Get the released state of the mouse
             * 
             * @return true 
             * @return false 
             */
            inline bool released() const { return this->_released;};

            /**
             * @brief Set the Pressed object
             * 
             * @param status 
             */
            inline void setPressed(bool status) { this->_pressed = status; };

            /**
             * @brief Set the Hold object
             * 
             * @param status 
             */
            inline void setHold(bool status) { this->_hold = status; };

            /**
             * @brief Set the Released object
             * 
             * @param status 
             */
            inline void setReleased(bool status) { this->_released = status; };

            /**
             * @brief render the hitbox of the mouse
             * 
             * @param window 
             */
            inline void show(sf::RenderWindow &window) { window.draw(this->_hitbox); };

            /**
             * @brief get the hover state of the mouse from a rectangle
             * 
             * @param other 
             * @return true 
             * @return false 
             */
            bool hover(sf::RectangleShape other);

            /**
             * @brief Update the mouse
             * 
             * @param window 
             */
            void update(sf::RenderWindow &window);
    };
} // namespace Zappy

#endif /* !MOUSE_H */
