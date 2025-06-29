/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** GUI
*/

#ifndef GUI_HPP_
    #define GUI_HPP_
    #include <memory>
    #include <thread>
    #include "SFML/Graphics.hpp"
    #include "MouseStatus.hpp"
    #include "Drawable.hpp"
    #include "Network.hpp"
    #include "Items.hpp"
    #include "MouseStatus.hpp"
    #include "Map.hpp"
    #include "TrantorianInfo.hpp"
    #include "TileInfo.hpp"
    #include "DrawRandom.hpp"
    #include "BroadCastTab.hpp"
    #include "OneShotAnimationPlayer.hpp"
    #include "TrantorButtons.hpp"
    #include <cmath>
    #include <algorithm>

namespace Zappy
{
    class Network;
    class TrantorButtons;
    class TileButtons;
    class Buttons;
    class Map;
    class TileInfo;
    class TrantorianInfo;
    class Items;
    class GUI
    {
        private:
            std::vector<std::shared_ptr<Items>> _items;
            std::vector<std::string> spritePaths;
            std::shared_ptr<Network> _networkInfo;
            sf::RenderWindow _window;
            sf::View _view;
            sf::Text _TimeText;
            sf::Font _TimeFont;
            MouseStatus _mouse = MouseStatus(false);
            MouseStatus _uiMouse = MouseStatus(true);
            sf::VertexArray background;
            sf::Clock _clock = sf::Clock();
            float time = 6.0f;
            bool night = true;
            std::string _ip = "127.0.0.1";
            size_t _port = 0;
            Drawable tile = Drawable("assets/map.png");
            Drawable sky = Drawable("assets/sky.jpg");
            DrawRandom _effect = DrawRandom(40, 6, 0.2, 0.1);
            sf::Clock _framerateClock;
            std::thread _recieveThread;
            std::shared_ptr<Map> _map;
            float tile_scale = 0.5;
            sf::Event _event;
            int _playerNb = 0;
            sf::Vector2i _mapSize;
            int _timeUnit = 1;
            bool _dragging;
            std::shared_ptr<TileInfo> _tileInfo;
            std::shared_ptr<TrantorianInfo> _trantorianInfo;
            std::shared_ptr<BroadCastTab> _broadcastTab;
            std::vector<std::shared_ptr<OneShotAnimationPlayer>> _oneShotAnimationTab;
            bool _isEnding = false;
            std::vector<std::shared_ptr<Buttons>> _endScreenButtons;
            //Menu
            Drawable _menuBg = Drawable("assets/menu_bg.jpg");
            Drawable _menuBgDark = Drawable("assets/menu_bg_dark.jpg");
            std::vector<std::shared_ptr<Buttons>> _menuButtons;
            std::vector<std::shared_ptr<Buttons>> _connectionButtons;
            bool _isOnConnectionPage = false;
            bool _hasConnectionFailed = false;
            bool _portSelected = false;
            bool _ipSelected = false;
            bool _gameIsRunning = false;
            sf::RectangleShape _ipRect;
            sf::RectangleShape _portRect;
            sf::Text _menuText;
            sf::Font _font;
            std::string _tmpIp = "";
            std::string _tmpPort = "";
            std::string _lastTeamAlive;
        public:
            GUI();
            ~GUI();

            /**
             * @brief Init needed components for the main game
             * 
             */
            void init();

            /**
             * @brief Run the main game
             * 
             */
            void runGame();

            /**
             * @brief Run function for the Menu
             * 
             */
            void runMenu();

            /**
             * @brief Handle the Events of the window from the menu
             * 
             */
            void handleMenuEvents();

            /**
             * @brief Manage the Menu page (START OR QUIT)
             * 
             */
            void manageMenuPage();

            /**
             * @brief Manage the Connection page
             * 
             */
            void manageConnectionPage();

            /**
             * @brief Create the Buttons needed for the menu
             * 
             */
            void initMenuButtons();

            /**
             * @brief Create the Buttons needed for the connection page
             * 
             */
            void initMenuConnectionButtons();

            /**
             * @brief Quit the game
             * 
             */
            void quit();

            /**
             * @brief Go to the connection page from the menu
             * 
             */
            void goToConnectionPage();

            /**
             * @brief Go back to the main menu
             * 
             */
            void goBackToMenu();

            /**
             * @brief Create the components for the connection page
             * 
             */
            void initConnectionFields();

            /**
             * @brief Connect function for a button
             * 
             */
            void connect();

            /**
             * @brief Select IP function for a button
             * 
             */
            void selectIp();

            /**
             * @brief Confirm IP function for a button
             * 
             */
            void confirmIp();

            /**
             * @brief Select Port function for a button
             * 
             */
            void selectPort();

            /**
             * @brief Confirm Port function for a button
             * 
             */
            void confirmPort();

            /**
             * @brief Draw the text on the screen
             * 
             * @param string 
             * @param position 
             * @param color 
             * @param characterSize 
             * @param window 
             */
            void drawText(const std::string& string, sf::Vector2f position, sf::Color color, int characterSize, sf::RenderWindow &window);

            /**
             * @brief Draw the IP and the PORT on the window (connection page)
             * 
             */
            void renderIpAndPort();

            /**
             * @brief Init the path for items
             * 
             */
            void initPaths();

            /**
             * @brief Run functions for the main game
             * 
             */
            void run();

            /**
             * @brief Render the tiles on the screen
             * 
             */
            void display_map();

            /**
             * @brief Render the sky on the screen
             * 
             */
            void display_sky();

            /**
             * @brief Render all the trantorians
             * 
             */
            void display_trantor();

            /**
             * @brief Render all the Eggs
             * 
             */
            void display_eggs();

            /**
             * @brief Display all the active animations
             * 
             */
            void displayOneShotAnimation();

            /**
             * @brief Handle main game window events
             * 
             */
            void handleWindowEvents();

            /**
             * @brief Handle zoom with scroll wheel
             * 
             */
            void zoomScroll();

            /**
             * @brief Handle view position
             * 
             */
            void touchView();

            /**
             * @brief Update the clock
             * 
             */
            void updateClock();

            /**
             * @brief Update the trantorians
             * 
             */
            void updateTrantor();

            /**
             * @brief Update function for thread
             * 
             */
            void update();

            /**
             * @brief Handle tile buttons for tile selection
             * 
             */
            void handleTileButtons();

            /**
             * @brief Manage end of game
             * 
             */
            void manageEndOfGame();

            /**
             * @brief Notify the GUI that the game has ended
             * 
             */
            inline void endGame() { this->_isEnding = true; };

            /**
             * @brief Create the buttons for the end screen
             * 
             */
            void initEndScreenButtons();

            /**
             * @brief Returns to the main menu
             * 
             */
            void quitGameToMenu();

            /**
             * @brief Set the Last Team Alive object
             * 
             * @param teamName 
             */
            inline void setLastTeamAlive(const std::string& teamName) { this->_lastTeamAlive = teamName; };

            /**
             * @brief View clamp function
             * 
             * @param val 
             * @param min 
             * @param max 
             * @return sf::Vector2f 
             */
            sf::Vector2f vclamp(sf::Vector2f val, sf::Vector2f min, sf::Vector2f max);

            /**
             * @brief Lerp function for colors
             * 
             * @param a 
             * @param b 
             * @param t 
             * @return sf::Color 
             */
            sf::Color lerpColor(const sf::Color &a, sf::Color &b, float t);

            /**
             * @brief Update function for the sky
             * 
             */
            void updateSky();

            /**
             * @brief Get the dist to cam object
             * 
             * @param view 
             * @param pos 
             * @return float 
             */
            float get_dist_to_cam(sf::View view, Vector2D pos);

            /**
             * @brief Init map with the given size
             * 
             * @param sizeX 
             * @param sizeY 
             */
            inline void initMap(double sizeX, double sizeY) { this->_map = std::make_shared<Map>(this, Vector2D(sizeX, sizeY)); };

            /**
             * @brief Get the Map object
             * 
             * @return std::shared_ptr<Map> 
             */
            inline std::shared_ptr<Map> getMap() const {return this->_map;};

            /**
             * @brief Get the Tile Scale object
             * 
             * @return float 
             */
            inline float getTileScale() const {return this->tile_scale;};

            /**
             * @brief Get the Network object
             * 
             * @return std::shared_ptr<Network> 
             */
            inline std::shared_ptr<Network> getNetwork() const {return this->_networkInfo;};

            /**
             * @brief Get the Time Unit object
             * 
             * @return int 
             */
            inline int getTimeUnit() const { return this->_timeUnit; };

            /**
             * @brief Get the View object
             * 
             * @return sf::View& 
             */
            inline sf::View &getView() {return this->_view; };

            /**
             * @brief Set the Time Unit object
             * 
             * @param unit 
             */
            inline void setTimeUnit(int unit) { this->_timeUnit = unit; };

            /**
             * @brief Set the Player Nb object
             * 
             * @param number 
             */
            inline void setPlayerNb(int number) { this->_playerNb = number; };

            /**
             * @brief Set the Map Size object
             * 
             * @param size 
             */
            inline void setMapSize(sf::Vector2i size) { this->_mapSize = size; };

            /**
             * @brief Get the Player Nb object
             * 
             * @return int 
             */
            inline int getPlayerNb() const { return this->_playerNb; };

            /**
             * @brief Get the Map Size object
             * 
             * @return sf::Vector2i 
             */
            inline sf::Vector2i getMapSize() const { return this->_mapSize; };

            /**
             * @brief Get the Tile Info object
             * 
             * @return std::shared_ptr<TileInfo> 
             */
            inline std::shared_ptr<TileInfo> getTileInfo() const { return this->_tileInfo; };

            /**
             * @brief Get the Trantorian Info object
             * 
             * @return std::shared_ptr<TrantorianInfo> 
             */
            inline std::shared_ptr<TrantorianInfo> getTrantorianInfo() const { return this->_trantorianInfo; };

            /**
             * @brief Get the Broad Cast Tab object
             * 
             * @return std::shared_ptr<BroadCastTab> 
             */
            inline std::shared_ptr<BroadCastTab> getBroadCastTab() const { return this->_broadcastTab; }

            /**
             * @brief Get the Center Tile Pos object
             * 
             * @param px 
             * @param py 
             * @param originX 
             * @param originY 
             * @param tileWidth 
             * @param tileHeight 
             * @return sf::Vector2i 
             */
            sf::Vector2i getCenterTilePos(float px, float py, float originX, float originY, float tileWidth, float tileHeight);

            /**
             * @brief Add an active animation to the animation tab
             * 
             * @param animation 
             */
            inline void addToAnimationTab(std::shared_ptr<OneShotAnimationPlayer> animation) { this->_oneShotAnimationTab.push_back(animation); }; 

    };
}

#endif /* !GUI_HPP_ */
