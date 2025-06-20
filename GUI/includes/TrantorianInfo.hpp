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

namespace Zappy
{
    class GUI;
    class Trantorian;
    class TrantorianInfo
    {
        private:
            GUI *_gui;
            std::shared_ptr<Trantorian> _trantorian = nullptr;
            sf::RectangleShape _bg;
            sf::RectangleShape _titleBarBg;
            sf::Text _text;
            sf::Font _font;
        public:
            TrantorianInfo(GUI *gui);
            inline ~TrantorianInfo() = default;

            void update(MouseStatus mouse);
            void render(sf::RenderWindow &window);
            inline void setTrantorian(std::shared_ptr<Trantorian> trantorian) { this->_trantorian = trantorian; };
    };
} // namespace Zappy


#endif /* !TRANTORIAN_INFO_H */
