/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Tile buttons
*/

#ifndef TILE_BUTTONS_H
    #define TILE_BUTTONS_H
    #include <memory>
    #include "Tile.hpp"
    #include "Buttons.hpp"
    #include "GUI.hpp"

namespace Zappy
{
    class Tile;
    class GUI;
    class TileButtons : public Buttons
    {
        private:
            std::shared_ptr<Tile> _targetTile = nullptr;
            GUI *_gui = nullptr;
        public:
            TileButtons(GUI *gui = nullptr, std::shared_ptr<Tile> tile = nullptr);
            inline ~TileButtons() = default;

            /**
             * @brief Special operator () that calls the function of the button
             * 
             * @return std::shared_ptr<Tile> 
             */
            inline std::shared_ptr<Tile> operator()() { return this->_targetTile; };

            /**
             * @brief Special function that is called by the button
             * 
             * @return std::shared_ptr<Tile> 
             */
            inline std::shared_ptr<Tile> function() { return this->_targetTile; };

            /**
             * @brief Custom update function for this button
             * 
             * @param mouse 
             */
            void update(MouseStatus mouse);
    };
} // namespace Zappy

#endif /* !TILE_BUTTONS_H */
