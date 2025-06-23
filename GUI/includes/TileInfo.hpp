/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Tile info header
*/

#ifndef TILE_INFO_H
    #define TILE_INFO_H
    #include "Tile.hpp"
    #include "MouseStatus.hpp"
    #include "TrantorButtons.hpp"
    #include <memory>
    #include <vector>
    #include "GUI.hpp"

namespace Zappy
{
    class GUI;
    class TrantorButtons;
    class TileInfo
    {
        private:
            GUI *_gui;
            std::shared_ptr<Tile> _tile = nullptr;
            std::shared_ptr<Tile> _nextTile = nullptr;
            std::vector<std::shared_ptr<TrantorButtons>> _buttons;
            sf::RectangleShape _titleBarBg;
            sf::RectangleShape _playerTitleBg;
            sf::RectangleShape _bg;
            sf::RectangleShape _playerBg;
            sf::Text _text;
            sf::Font _font;
            sf::Vector2f _unselectedPos;
            sf::Vector2f _selectedPos;
            sf::Vector2f _pos;
            bool _hiding = false;
            float _growingNb;
            float _animationSpeed = 30;
        public:
            TileInfo(GUI *gui);
            inline ~TileInfo() = default;

            void update(MouseStatus mouse);
            void render(sf::RenderWindow &window);
            void setTile(std::shared_ptr<Tile> tile);
            void updateTrantorButtonsTab();
            void drawText(const std::string& string, sf::Vector2f position, sf::Color color, int characterSize, sf::RenderWindow &window);
            void manageHiding();
            inline float getAnimationSpeed() const { return this->_animationSpeed; };
            inline sf::Vector2f getPos() const { return this->_pos; };
            inline std::shared_ptr<Tile> getTile() const { return this->_tile; };
    };
} // namespace Zappy

#endif /* !TILE_INFO_H */
