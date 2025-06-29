/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** trantorian info header
*/

#ifndef TRANTORIAN_INFO_H
    #define TRANTORIAN_INFO_H
    #include "MouseStatus.hpp"
    #include <memory>
    #include <vector>
    #include "Trantor.hpp"
    #include "GUI.hpp"
    #include <cmath>
    
namespace Zappy
{
    class GUI;
    class Trantorian;
    class TrantorianInfo
    {
        private:
            GUI *_gui;
            std::shared_ptr<Trantorian> _trantorian = nullptr;
            std::shared_ptr<Trantorian> _nextTrantorian = nullptr;
            sf::RectangleShape _bg;
            sf::RectangleShape _titleBarBg;
            sf::Text _text;
            sf::Font _font;
            sf::Vector2f _unselectedPos;
            sf::Vector2f _selectedPos;
            sf::Vector2f _pos;
            sf::Vector2f _anchorPos;
            bool _hiding = false;
            float _growingNb;
        public:
            TrantorianInfo(GUI *gui);
            inline ~TrantorianInfo() = default;

            /**
             * @brief Update the Trantorian info
             * 
             * @param mouse 
             */
            void update(MouseStatus mouse);

            /**
             * @brief Draw the Trantorian Info
             * 
             * @param window 
             */
            void render(sf::RenderWindow &window);

            /**
             * @brief Set the Trantorian object
             * 
             * @param trantorian 
             */
            void setTrantorian(std::shared_ptr<Trantorian> trantorian);

            /**
             * @brief Draw a text in the window with the given parameters
             * 
             * @param string 
             * @param position 
             * @param color 
             * @param characterSize 
             * @param window 
             */
            void drawText(const std::string& string, sf::Vector2f position, sf::Color color, int characterSize, sf::RenderWindow &window);

            /**
             * @brief hide the trantorian info
             * 
             */
            inline void hide() { this->_hiding = true; };

            /**
             * @brief Get the hiding state of the trantorian info
             * 
             * @return true 
             * @return false 
             */
            inline bool isHiding() const { return this->_hiding; };

            /**
             * @brief Manage the hiding state of the trantorian info
             * 
             */
            void manageHiding();

            /**
             * @brief Get the Trantorian object
             * 
             * @return std::shared_ptr<Trantorian> 
             */
            inline std::shared_ptr<Trantorian> getTrantorian() const { return this->_trantorian; };
    };
} // namespace Zappy

#endif /* !TRANTORIAN_INFO_H */
