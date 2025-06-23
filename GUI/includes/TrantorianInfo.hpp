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

            void update(MouseStatus mouse);
            void render(sf::RenderWindow &window);
            void setTrantorian(std::shared_ptr<Trantorian> trantorian);
            void drawText(const std::string& string, sf::Vector2f position, sf::Color color, int characterSize, sf::RenderWindow &window);
            inline void hide() { this->_hiding = true; };
            inline bool isHiding() const { return this->_hiding; };
            void manageHiding();
            inline std::shared_ptr<Trantorian> getTrantorian() const { return this->_trantorian; };
    };
} // namespace Zappy

#endif /* !TRANTORIAN_INFO_H */
