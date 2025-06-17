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
    #include "Drawable.hpp"
    #include "Network.hpp"
    #include "Buttons.hpp"
    #include "Map.hpp"
    #include "Math/Vector2D.hpp"
    #include "Items.hpp"

namespace Zappy
{
    class Network;
    class GUI
    {
        private:
            std::vector<std::shared_ptr<Buttons>> _buttons;
            std::vector<std::shared_ptr<Items>> _items;
            std::vector<std::string> spritePaths;
            std::shared_ptr<Network> _networkInfo;
            sf::RenderWindow _window;

            Drawable tile = Drawable("../GUI/assets/map.png");
            float tile_scale = 0.25;
            Map _map;
            Drawable sky = Drawable("../GUI/assets/sky.jpg");
            sf::Event _event;

        public:
            GUI(const std::string& ip = "127.0.0.1", size_t port = 8000);
            ~GUI();
            void init();
            void initPaths();
            void run();
            void display_map();
            void display_sky();
            void display_objects();
            void handleWindowEvents();
            std::vector<std::shared_ptr<Buttons>> getButtons() const {return this->_buttons;};
            Map getMap() const {return this->_map;};
            float getTileScale() const {return this->tile_scale;};
            std::shared_ptr<Network> getNetwork() const {return this->_networkInfo;};
    };
}

#endif /* !GUI_HPP_ */
//