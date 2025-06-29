/*
** EPITECH PROJECT, 2025
** GUI
** File description:
** DrawRandom
*/

#ifndef DRAWRANDOM_HPP_
    #define DRAWRANDOM_HPP_
    #include "iostream"
    #include "memory"
    #include "Drawable.hpp"
namespace Zappy
{
    class DrawRandom
    {
    private:
        int _number = 0;
        int _starNb = 0;
        int _cloudNb = 0;
        std::shared_ptr<Drawable> _sprite;
        std::shared_ptr<Drawable> _star;
        std::shared_ptr<Drawable> _moon;
        std::shared_ptr<Drawable> _sun;
        std::vector<std::shared_ptr<Drawable>>  _cloud;
        std::vector<sf::Vector2f> _refreshPos;
        std::vector<sf::Vector2f> _cloudPositionsFront;
        std::vector<sf::Vector2f> _cloudPositionsBack;
        std::vector<int> _cloudIndicesFront;
        std::vector<int> _cloudIndicesBack;
        bool _cloudsInitialized = false;
    public:
        DrawRandom(std::string filePath, int number, float scale);
        DrawRandom(int starNb, int cloudNb, float starScale, float cloudScale);
        ~DrawRandom();

        /**
         * @brief Fade the sprite
         * 
         * @param window 
         * @param time 
         * @param fadeSpeed 
         * @param sprite 
         */
        void fadeSprite(sf::RenderWindow &window, float time, float fadeSpeed, std::shared_ptr<Drawable> sprite);

        /**
         * @brief Lerp function
         * 
         * @param pos 
         * @param lerp 
         * @param speed 
         * @return sf::Vector2f 
         */
        sf::Vector2f lerp(sf::Vector2f pos, sf::Vector2f lerp, float speed);

        /**
         * @brief Run function
         * 
         * @param window 
         * @param night 
         * @param time 
         * @param fade 
         * @return int 
         */
        int run(sf::RenderWindow &window, bool night, float time, bool fade);

        /**
         * @brief Run function for Star
         * 
         * @param window 
         * @param time 
         * @param fade 
         * @return int 
         */
        int runStar(sf::RenderWindow &window, float time, bool fade);

        /**
         * @brief Run function for clouds
         * 
         * @param window 
         * @param time 
         * @param fade 
         * @return int 
         */
        int runCloud(sf::RenderWindow &window, float time, bool fade);

        /**
         * @brief Run function for rendering
         * 
         * @param window 
         * @param night 
         * @param time 
         */
        void runDraw(sf::RenderWindow &window, bool night, float time);

        /**
         * @brief Render the moon and the sun
         * 
         * @param window 
         * @param night 
         * @param time 
         */
        void drawMoonSun(sf::RenderWindow &window, bool night, float time);

        /**
         * @brief Get the Sprite object
         * 
         * @return std::shared_ptr<Drawable> 
         */
        std::shared_ptr<Drawable> getSprite() {return this->_sprite;};
    };
    
   
    
}

#endif /* !DRAWRANDOM_HPP_ */
