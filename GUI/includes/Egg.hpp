/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Egg header
*/

#ifndef EGG_H
    #define EGG_H
    #include "Drawable.hpp"
    #include <memory>
    #include <string>
namespace Zappy
{
    class Egg
    {
        private:
            std::shared_ptr<Drawable> _drawable;
            size_t _id;
            sf::Vector2f _pos;
            sf::Vector2i _indexPos;
            std::string _teamName;
        public:
            Egg(size_t id = 0, sf::Vector2i indexPos = {0, 0}, const std::string& teamName = "default");
            inline ~Egg() = default;

            /**
             * @brief Get the Drawable object
             * 
             * @return std::shared_ptr<Drawable> 
             */
            inline std::shared_ptr<Drawable> getDrawable() const { return this->_drawable; };

            /**
             * @brief Set the Id object
             * 
             * @param id 
             */
            inline void setId(size_t id) { this->_id = id; };

            /**
             * @brief Set the Pos object
             * 
             * @param pos 
             */
            inline void setPos(sf::Vector2f pos) { this->_pos = pos; };

            /**
             * @brief Set the Index Pos object
             * 
             * @param pos 
             */
            inline void setIndexPos(sf::Vector2i pos) { this->_indexPos= pos; };

            /**
             * @brief Set the Team Name object
             * 
             * @param name 
             */
            inline void setTeamName(const std::string& name) { this->_teamName = name; };

            /**
             * @brief Get the Pos object
             * 
             * @return sf::Vector2f 
             */
            inline sf::Vector2f getPos() const { return this->_pos; };

            /**
             * @brief Get the Index Pos object
             * 
             * @return sf::Vector2i 
             */
            inline sf::Vector2i getIndexPos() const { return this->_indexPos; };

            /**
             * @brief Get the Team Name object
             * 
             * @return std::string 
             */
            inline std::string getTeamName() const { return this->_teamName; };

            /**
             * @brief Get the Id object
             * 
             * @return size_t 
             */
            inline size_t getId() const { return this->_id; };
    };
} // namespace Zappy


#endif /* !EGG_H */
