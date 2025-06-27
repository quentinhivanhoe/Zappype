/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** BroadCastTab header
*/

#ifndef BROADCAST_TAB_H
    #define BROADCAST_TAB_H
    #include <SFML/Graphics.hpp>
    #include <vector>
    #include <string>
    #include <memory>

namespace Zappy
{
    class BroadCastTab
    {
        private:
            sf::RectangleShape _bg;
            sf::Clock _clock;
            sf::Text _text;
            sf::Font _font;

            std::vector<std::string> _messages;
            size_t _maxMessagesSize = 10;
        public:
            BroadCastTab();
            inline ~BroadCastTab() = default;
            void update();
            void drawText(const std::string& string, sf::Vector2f position, sf::Color color, int characterSize, sf::RenderWindow &window);
            void render(sf::RenderWindow &window);
            inline std::vector<std::string> getMessages() const { return this->_messages; };
            void pushToMessages(const std::string& messages);
            inline void resetTimer() { this->_clock.restart(); }; 
    };
} // namespace Zappy

#endif /* !BROADCAST_TAB_H */
