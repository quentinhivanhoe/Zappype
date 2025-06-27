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
        void fadeSprite(sf::RenderWindow &window, float time, float fadeSpeed, std::shared_ptr<Drawable> sprite);
        sf::Vector2f lerp(sf::Vector2f pos, sf::Vector2f lerp, float speed);
        int run(sf::RenderWindow &window, bool night, float time, bool fade);
        int runStar(sf::RenderWindow &window, float time, bool fade);
        int runCloud(sf::RenderWindow &window, float time, bool fade);
        void runDraw(sf::RenderWindow &window, bool night, float time);
        void drawMoonSun(sf::RenderWindow &window, bool night, float time);
        std::shared_ptr<Drawable> getSprite() {return this->_sprite;};
    };
    
   
    
}

#endif /* !DRAWRANDOM_HPP_ */
