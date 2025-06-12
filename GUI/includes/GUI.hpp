/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** GUI
*/

#ifndef GUI_HPP_
    #define GUI_HPP_
    #include <memory>
    #include "SFML/Graphics.hpp"
    #include "Network.hpp"
    #include "Buttons.hpp"
    #include "Map.hpp"

namespace Zappy
{
    class GUI
    {
        private:
            std::vector<std::shared_ptr<Buttons>> _buttons;
            std::shared_ptr<Network> _networkInfo;
            sf::RenderWindow _window;

            //faire une classe pour ça ptet//        
            sf::Texture tile_texture;
            sf::Sprite tile;
            float tile_scale = 0.25;
            Map _map;

            sf::Texture sky_texture;
            sf::Sprite sky;

            //----------------------------//
            sf::Event _event;

        public:
            GUI();
            ~GUI();
            void init();
            void run();
            void display_map();
            void display_sky();
            void handleWindowEvents();
            std::vector<std::shared_ptr<Buttons>> getButtons() const {return this->_buttons;};
            Map getMap() const {return this->_map;};
            float getTileScale() const {return this->tile_scale;};
            std::shared_ptr<Network> getNetwork() const {return this->_networkInfo;};
    };
}

#endif /* !GUI_HPP_ */
