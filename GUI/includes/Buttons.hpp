/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Button class
*/

#ifndef BUTTON_H
    #define BUTTON_H
    #include <SFML/Graphics.hpp>
    #include "MouseStatus.hpp"
    #include "Math/Clamp.hpp"
    #include <iostream>
    #include <functional>

namespace Zappy
{
    class GUI;
    class Buttons
    {
        private:
            float _rotation = 0;
            sf::Vector2f _scale = {1, 1};
            sf::Vector2f _basePosition = {100, 100};
            sf::Vector2f _baseScale = {1, 1};
            sf::Vector2f _maxScale = {1.15, 1.15};
            sf::Vector2f _minScale = {0.85, 0.85};
            sf::Vector2f _position = {100, 100};
            sf::Vector2f _size = {100, 100};
            sf::Vector2f _titlePositionOffset = {0, 0};
            int _characterSize = 30;
            bool _active = true;

            sf::Text _title;
            sf::Font _font;
            sf::RectangleShape _bg;
            sf::Color _fillColor;
            sf::Color _outlineColor;

            std::function<void(void *)> _function = nullptr;
        public:
            Buttons();
            virtual inline ~Buttons() { std::cout << "Button destructor" << std::endl; };
            
            Buttons &operator()(void *parameters);
            Buttons &function(void *parameters);
            // Getters
            inline sf::Vector2f getPosition() const { return this->_position; };
            inline sf::Vector2f getTitlePositionOffset() const { return this->_titlePositionOffset; };
            inline sf::Vector2f getSize() const { return this->_size; };
            inline sf::Vector2f getScale() const { return this->_scale; };
            inline sf::Vector2f getBaseScale() const { return this->_baseScale; };
            inline sf::Vector2f getMaxScale() const { return this->_maxScale; };
            inline sf::Vector2f getMinScale() const { return this->_minScale; };
            inline int getCharacterSize() const { return this->_characterSize; };
            inline float getRotation() const { return this->_rotation; };
            inline std::string getTitle() const { return this->_title.getString(); };
            inline sf::Text &getTitleComponent() { return this->_title; };
            inline sf::Font &getFontComponent() { return this->_font; };
            inline sf::RectangleShape &getBgComponent() { return this->_bg; };
            inline sf::Color getFillColor() const { return this->_fillColor; };
            inline sf::Color getOutlineColor() const { return this->_outlineColor; };
            inline sf::Vector2f getBasePosition() const { return this->_basePosition; };
            
            // Setters
            Buttons &setPosition(sf::Vector2f position);
            Buttons &setTitlePositionOffset(sf::Vector2f position);
            Buttons &setSize(sf::Vector2f size);
            Buttons &setRotation(float rotation);
            Buttons &setScale(sf::Vector2f scale);
            Buttons &setBaseScale(sf::Vector2f scale);
            Buttons &setMinScale(sf::Vector2f scale);
            Buttons &setMaxScale(sf::Vector2f scale);
            Buttons &setCharacterSize(int size);
            Buttons &setTitle(const std::string& title);
            Buttons &setBgOutlineColor(sf::Color color);
            Buttons &setBgFillColor(sf::Color color);
            Buttons &setTextFillColor(sf::Color color);
            Buttons &setTextOutlineColor(sf::Color color);
            Buttons &setFunction(std::function<void(void *)> function);
            Buttons &setBasePosition(sf::Vector2f pos);
            
            Buttons &rotateClockWise(float step);
            Buttons &rotateCounterClockWise(float step);
            Buttons &scaleUp(float step);
            Buttons &scaleDown(float step);

            void render(sf::RenderWindow &window) const;
            virtual void update(MouseStatus mouse);
    };
} // namespace Zappy

#endif /* !BUTTON_H */
