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
            float tile_scale = 0.5;
            Map _map;
            Drawable sky = Drawable("../GUI/assets/sky.jpg");
            sf::Event _event;
            sf::View _view;
            int _playerNb = 0;
            sf::Vector2i _mapSize;
            int _timeUnit = 1;
        public:
            GUI(const std::string& ip = "127.0.0.1", size_t port = 8000);
            ~GUI();
            void init();
            void initPaths();
            void run();
            void display_map();
            void display_sky();
            void display_objects();
            void display_trantor();
            void handleWindowEvents();
            inline std::vector<std::shared_ptr<Buttons>> getButtons() const {return this->_buttons;};
            inline Map getMap() const {return this->_map;};
            inline float getTileScale() const {return this->tile_scale;};
            inline std::shared_ptr<Network> getNetwork() const {return this->_networkInfo;};
            inline int getTimeUnit() const { return this->_timeUnit; };
            inline void setTimeUnit(int unit) { this->_timeUnit = unit; };

            inline void setPlayerNb(int number) { this->_playerNb = number; };
            inline void setMapSize(sf::Vector2i size) { this->_mapSize = size; };
            inline int getPlayerNb() const { return this->_playerNb; };
            inline sf::Vector2i getMapSize() const { return this->_mapSize; };

    };
}

#endif /* !GUI_HPP_ */
