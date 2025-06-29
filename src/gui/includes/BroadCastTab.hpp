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

            /**
             * @brief Update the broadcast tab
             * 
             */
            void update();

            /**
             * @brief Draw a text on the window with the given parameters
             * 
             * @param string 
             * @param position 
             * @param color 
             * @param characterSize 
             * @param window 
             */
            void drawText(const std::string& string, sf::Vector2f position, sf::Color color, int characterSize, sf::RenderWindow &window);

            /**
             * @brief Render the broadcast tab
             * 
             * @param window 
             */
            void render(sf::RenderWindow &window);

            /**
             * @brief Get the Messages object
             * 
             * @return std::vector<std::string> 
             */
            inline std::vector<std::string> getMessages() const { return this->_messages; };

            /**
             * @brief Add a message (line) into the broadcast tab
             * 
             * @param messages 
             */
            void pushToMessages(const std::string& messages);

            /**
             * @brief Reset the timer for oldest messsage deletion
             * 
             */
            inline void resetTimer() { this->_clock.restart(); }; 
    };
} // namespace Zappy

#endif /* !BROADCAST_TAB_H */
