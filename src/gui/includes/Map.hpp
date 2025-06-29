/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** Map
*/

#ifndef MAP_HPP_
    #define MAP_HPP_
    #include <memory>
    #include "Interfaces/IObject.hpp"
    #include "Tile.hpp"
    #include "Team.hpp"

namespace Zappy
{
    class Team;
    class Trantorian;
    class Egg;
    class TrantorButtons;
    class GUI;
    class Tile;
    class Map
    {
    private:
        GUI *_gui;
        std::map<std::string, std::shared_ptr<Team>> _teams;
        std::map<size_t, std::shared_ptr<Trantorian>> _trantorians;
        std::map<size_t, std::shared_ptr<Egg>> _eggs;
        std::vector<std::vector<std::shared_ptr<Tile>>> _tiles;
        Vector2D _size;
        float _tileScale = 0.5 * 3.07;
    public:
        Map(GUI *gui, Vector2D size = Vector2D(5.0, 5.0));
        ~Map();

        /**
         * @brief Create the components needed by the whole map
         * 
         */
        void init();

        /**
         * @brief Get the Size object
         * 
         * @return Vector2D 
         */
        inline Vector2D getSize() const {return this->_size;};

        /**
         * @brief Get the Teams object
         * 
         * @return std::map<std::string, std::shared_ptr<Team>> 
         */
        inline std::map<std::string, std::shared_ptr<Team>> getTeams() const { return this->_teams; };

        /**
         * @brief Get the Tiles object
         * 
         * @return std::vector<std::vector<std::shared_ptr<Tile>>> 
         */
        inline std::vector<std::vector<std::shared_ptr<Tile>>> getTiles() {return this->_tiles;};

        /**
         * @brief Get the Trantorian By I D object
         * 
         * @param id 
         * @return std::shared_ptr<Trantorian> 
         */
        inline std::shared_ptr<Trantorian> getTrantorianByID(size_t id) { return this->_trantorians[id]; };

        /**
         * @brief Get the All Trantorians object
         * 
         * @return std::map<size_t, std::shared_ptr<Trantorian>> 
         */
        inline std::map<size_t, std::shared_ptr<Trantorian>> getAllTrantorians() const { return this->_trantorians; };

        /**
         * @brief Add a trantorian to the list of trantorians and to its respective team
         * 
         * @param trantorian 
         */
        void addTrantorian(std::shared_ptr<Trantorian> trantorian);

        /**
         * @brief Add a egg to the list of eggs and to its respective team
         * 
         * @param egg 
         */
        void addEgg(std::shared_ptr<Egg> egg);

        /**
         * @brief Remove the egg from the tab
         * 
         * @param id 
         */
        inline void removeEggById(size_t id) { this->_eggs.erase(id); };

        /**
         * @brief Get the Egg By Id object
         * 
         * @param id 
         * @return std::shared_ptr<Egg> 
         */
        inline std::shared_ptr<Egg> getEggById(size_t id) { return this->_eggs[id]; };

        /**
         * @brief Get the All Eggs object
         * 
         * @return std::map<size_t, std::shared_ptr<Egg>> 
         */
        inline std::map<size_t, std::shared_ptr<Egg>> getAllEggs() const { return this->_eggs; };
    };
}

#endif /* !MAP_HPP_ */
