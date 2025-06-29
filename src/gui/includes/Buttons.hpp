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
    #include "Error.hpp"
    #include <iostream>
    #include <functional>

namespace Zappy
{
    class GUI;
    class Buttons
    {
        private:
            GUI *_gui = nullptr;
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

            void (GUI::* _function)() = nullptr;
        public:
            Buttons(GUI *gui = nullptr);
            virtual inline ~Buttons() { std::cout << "Button destructor" << std::endl; };
            
            /**
             * @brief Operator () that calls the function of the button
             * 
             * @return Buttons& 
             */
            Buttons &operator()();

            /**
             * @brief Call the function of the button
             * 
             * @return Buttons& 
             */
            Buttons &function();
            // Getters

            /**
             * @brief Get the Position object
             * 
             * @return sf::Vector2f 
             */
            inline sf::Vector2f getPosition() const { return this->_position; };

            /**
             * @brief Get the Title Position Offset object
             * 
             * @return sf::Vector2f 
             */
            inline sf::Vector2f getTitlePositionOffset() const { return this->_titlePositionOffset; };

            /**
             * @brief Get the Size object
             * 
             * @return sf::Vector2f 
             */
            inline sf::Vector2f getSize() const { return this->_size; };

            /**
             * @brief Get the Scale object
             * 
             * @return sf::Vector2f 
             */
            inline sf::Vector2f getScale() const { return this->_scale; };

            /**
             * @brief Get the Base Scale object
             * 
             * @return sf::Vector2f 
             */
            inline sf::Vector2f getBaseScale() const { return this->_baseScale; };

            /**
             * @brief Get the Max Scale object
             * 
             * @return sf::Vector2f 
             */
            inline sf::Vector2f getMaxScale() const { return this->_maxScale; };

            /**
             * @brief Get the Min Scale object
             * 
             * @return sf::Vector2f 
             */
            inline sf::Vector2f getMinScale() const { return this->_minScale; };

            /**
             * @brief Get the Character Size object
             * 
             * @return int 
             */
            inline int getCharacterSize() const { return this->_characterSize; };

            /**
             * @brief Get the Rotation object
             * 
             * @return float 
             */
            inline float getRotation() const { return this->_rotation; };

            /**
             * @brief Get the Title object
             * 
             * @return std::string 
             */
            inline std::string getTitle() const { return this->_title.getString(); };

            /**
             * @brief Get the Title Component object
             * 
             * @return sf::Text& 
             */
            inline sf::Text &getTitleComponent() { return this->_title; };

            /**
             * @brief Get the Font Component object
             * 
             * @return sf::Font& 
             */
            inline sf::Font &getFontComponent() { return this->_font; };

            /**
             * @brief Get the Bg Component object
             * 
             * @return sf::RectangleShape& 
             */
            inline sf::RectangleShape &getBgComponent() { return this->_bg; };

            /**
             * @brief Get the Fill Color object
             * 
             * @return sf::Color 
             */
            inline sf::Color getFillColor() const { return this->_fillColor; };

            /**
             * @brief Get the Outline Color object
             * 
             * @return sf::Color 
             */
            inline sf::Color getOutlineColor() const { return this->_outlineColor; };

            /**
             * @brief Get the Base Position object
             * 
             * @return sf::Vector2f 
             */
            inline sf::Vector2f getBasePosition() const { return this->_basePosition; };
            
            // Setters

            /**
             * @brief Set the Position object
             * 
             * @param position 
             * @return Buttons& 
             */
            Buttons &setPosition(sf::Vector2f position);


            /**
             * @brief Set the Title Position Offset object
             * 
             * @param position 
             * @return Buttons& 
             */
            Buttons &setTitlePositionOffset(sf::Vector2f position);

            /**
             * @brief Set the Size object
             * 
             * @param size 
             * @return Buttons& 
             */
            Buttons &setSize(sf::Vector2f size);

            /**
             * @brief Set the Rotation object
             * 
             * @param rotation 
             * @return Buttons& 
             */
            Buttons &setRotation(float rotation);

            /**
             * @brief Set the Scale object
             * 
             * @param scale 
             * @return Buttons& 
             */
            Buttons &setScale(sf::Vector2f scale);

            /**
             * @brief Set the Base Scale object
             * 
             * @param scale 
             * @return Buttons& 
             */
            Buttons &setBaseScale(sf::Vector2f scale);

            /**
             * @brief Set the Min Scale object
             * 
             * @param scale 
             * @return Buttons& 
             */
            Buttons &setMinScale(sf::Vector2f scale);

            /**
             * @brief Set the Max Scale object
             * 
             * @param scale 
             * @return Buttons& 
             */
            Buttons &setMaxScale(sf::Vector2f scale);

            /**
             * @brief Set the Character Size object
             * 
             * @param size 
             * @return Buttons& 
             */
            Buttons &setCharacterSize(int size);

            /**
             * @brief Set the Title object
             * 
             * @param title 
             * @return Buttons& 
             */
            Buttons &setTitle(const std::string& title);

            /**
             * @brief Set the Bg Outline Color object
             * 
             * @param color 
             * @return Buttons& 
             */
            Buttons &setBgOutlineColor(sf::Color color);

            /**
             * @brief Set the Bg Fill Color object
             * 
             * @param color 
             * @return Buttons& 
             */
            Buttons &setBgFillColor(sf::Color color);

            /**
             * @brief Set the Text Fill Color object
             * 
             * @param color 
             * @return Buttons& 
             */
            Buttons &setTextFillColor(sf::Color color);

            /**
             * @brief Set the Text Outline Color object
             * 
             * @param color 
             * @return Buttons& 
             */
            Buttons &setTextOutlineColor(sf::Color color);

            /**
             * @brief Set the Function object
             * 
             * @param function 
             * @return Buttons& 
             */
            Buttons &setFunction(void (GUI:: *function)());

            /**
             * @brief Set the Base Position object
             * 
             * @param pos 
             * @return Buttons& 
             */
            Buttons &setBasePosition(sf::Vector2f pos);
            
            /**
             * @brief Rotate the button (clockwise) by step angle
             * 
             * @param step 
             * @return Buttons& 
             */
            Buttons &rotateClockWise(float step);

            /**
             * @brief Rotate the button (counter clockwise) by step angle
             * 
             * @param step 
             * @return Buttons& 
             */
            Buttons &rotateCounterClockWise(float step);

            /**
             * @brief Scale the button up by size. (Growing)
             * 
             * @param step 
             * @return Buttons& 
             */
            Buttons &scaleUp(float step);

            /**
             * @brief Scale the button down by size. (Shrinking)
             * 
             * @param step 
             * @return Buttons& 
             */
            Buttons &scaleDown(float step);

            /**
             * @brief Draw the button on the window
             * 
             * @param window 
             */
            void render(sf::RenderWindow &window) const;

            /**
             * @brief Update the button
             * 
             * @param mouse 
             */
            virtual void update(MouseStatus mouse);
    };
} // namespace Zappy

#endif /* !BUTTON_H */
