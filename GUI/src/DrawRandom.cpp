/*
** EPITECH PROJECT, 2025
** GUI
** File description:
** DrawRandom
*/

#include "../includes/DrawRandom.hpp"
#include "cmath"

Zappy::DrawRandom::DrawRandom(std::string filePath, int number, float scale)
{
    this->_number = number;
    this->_sprite = std::make_shared<Drawable>(filePath, scale);
}

Zappy::DrawRandom::DrawRandom(int starNb, int cloudNb, float starScale, float cloudScale)
{
    this->_starNb = starNb;
    this->_cloudNb = cloudNb;
    this->_star = std::make_shared<Drawable>("../GUI/assets/Star.png", starScale);
    this->_moon = std::make_shared<Drawable>("../GUI/assets/moon.png", 1);
    this->_sun = std::make_shared<Drawable>("../GUI/assets/sun.png", 1);
    this->_sun->getSprite().setPosition(sf::Vector2f(100, 1500));
    this->_moon->getSprite().setPosition(sf::Vector2f(100, 1500));
    this->_cloud.push_back(std::make_shared<Drawable>("../GUI/assets/nuage.png", cloudScale));
    this->_cloud.push_back(std::make_shared<Drawable>("../GUI/assets/nuage_gris.png", cloudScale));
    this->_cloud.push_back(std::make_shared<Drawable>("../GUI/assets/nuage_visage.png", cloudScale));
    this->_cloud.push_back(std::make_shared<Drawable>("../GUI/assets/nuage_sourire.png", cloudScale));
}
    
Zappy::DrawRandom::~DrawRandom()
{
}

void Zappy::DrawRandom::fadeSprite(sf::RenderWindow &window, float time, float fadeSpeed, std::shared_ptr<Drawable> sprite)
{
    float alpha = 0.5f * (1 + std::sin(2 * 3.14159f * fadeSpeed * time)) * 255.f;

    sf::Color color = sprite.get()->getSprite().getColor();
    color.a = static_cast<sf::Uint8>(std::clamp(alpha, 0.f, 255.f));
    sprite.get()->getSprite().setColor(color);

    window.draw(sprite.get()->getSprite());
}

sf::Vector2f Zappy::DrawRandom::lerp(sf::Vector2f pos, sf::Vector2f lerp, float speed)
{
    sf::Vector2f dist_vector = sf::Vector2f(lerp.x - pos.x, lerp.y - pos.y);
    sf::Vector2f r_val = pos + sf::Vector2f(dist_vector.x / speed, dist_vector.y / speed);
    return r_val;
}

int Zappy::DrawRandom::run(sf::RenderWindow &window, bool night, float time, bool fade)
{
    static float lastRefreshTime = -9999.f;
    const float refreshInterval = 5.f;
    sf::Vector2u winSize = window.getSize();
    sf::FloatRect spriteBounds = _sprite.get()->getSprite().getGlobalBounds();

    if (!night)
        return 1;
    if (time - lastRefreshTime >= refreshInterval) {
        _refreshPos.clear();
        float maxX = winSize.x - spriteBounds.width;
        float maxY = winSize.y - spriteBounds.height;

        for (int i = 0; i != this->_number; i++) {
            float x = static_cast<float>(std::rand()) / RAND_MAX * maxX;
            float y = static_cast<float>(std::rand()) / RAND_MAX * maxY;
            this->_refreshPos.push_back(sf::Vector2f(x, y));
        }

        lastRefreshTime = time;
    }
    for (const auto& pos : this->_refreshPos) {
        _sprite.get()->getSprite().setPosition(pos);
        if (fade)
            this->fadeSprite(window, time, 0.5f, _sprite);
        else 
            window.draw(_sprite.get()->getSprite());
    }

    return 0;
}

int Zappy::DrawRandom::runStar(sf::RenderWindow &window, float time, bool fade)
{
    static float lastRefreshTime = -9999.f;
    const float refreshInterval = 2.0f;
    sf::Vector2u winSize = window.getSize();
    sf::FloatRect spriteBounds = _star.get()->getSprite().getGlobalBounds();

    if (time - lastRefreshTime >= refreshInterval) {
        _refreshPos.clear();
        float maxX = winSize.x - spriteBounds.width;
        float maxY = winSize.y - spriteBounds.height;
        for (int i = 0; i != this->_starNb; i++) {
            this->_star.get()->getSprite().setRotation(std::rand() % 360);
            float x = static_cast<float>(std::rand()) / RAND_MAX * maxX;
            float y = static_cast<float>(std::rand()) / RAND_MAX * maxY;
            this->_refreshPos.push_back(sf::Vector2f(x, y));
        }
        lastRefreshTime = time;
    }
    for (const auto& pos : this->_refreshPos) {
        _star.get()->getSprite().setPosition(pos);
        if (fade)
            this->fadeSprite(window, time, 2.0f, _star);
        else 
            window.draw(_star.get()->getSprite());
    }

    return 0;
}

int Zappy::DrawRandom::runCloud(sf::RenderWindow &window, float time, bool fade)
{
    sf::Vector2u winSize = window.getSize();
    const float speedFront = 20.f;
    const float speedBack = 10.f;
    const int cols = 5;
    const int rows = 3;
    float dayFactor = 0.5f + 0.5f * std::cos(time / 24.f * 2.f * M_PI);

    static sf::Clock clock;
    float deltaTime = clock.restart().asSeconds();

    if (!_cloudsInitialized) {
        _cloudPositionsFront.clear();
        _cloudPositionsBack.clear();
        _cloudIndicesFront.clear();
        _cloudIndicesBack.clear();

        for (int i = 0; i < cols; ++i) {
            for (int j = 0; j < rows; ++j) {
                float x = std::rand() % winSize.x;
                float y = j * (winSize.y / static_cast<float>(rows));
                _cloudPositionsFront.emplace_back(x, y);
                _cloudIndicesFront.push_back(std::rand() % _cloud.size());
            }
        }

        for (int i = 0; i < cols - 1; ++i) {
            for (int j = 0; j < rows - 1; ++j) {
                float x = std::rand() % winSize.x;
                float y = j * (winSize.y / static_cast<float>(rows - 1));
                _cloudPositionsBack.emplace_back(x, y);
                _cloudIndicesBack.push_back(std::rand() % _cloud.size());
            }
        }

        _cloudsInitialized = true;
    }

    for (size_t i = 0; i < _cloudPositionsBack.size(); ++i) {
        _cloudPositionsBack[i].x += speedBack * deltaTime;

        if (_cloudPositionsBack[i].x > winSize.x)
            _cloudPositionsBack[i].x = -200;

        auto sprite = _cloud[_cloudIndicesBack[i]]->getSprite();
        sprite.setPosition(_cloudPositionsBack[i]);
        sprite.setColor(sf::Color(255, 255, 255, 120 * dayFactor));
        window.draw(sprite);
    }

    for (size_t i = 0; i < _cloudPositionsFront.size(); ++i) {
        _cloudPositionsFront[i].x += speedFront * deltaTime;

        if (_cloudPositionsFront[i].x > winSize.x)
            _cloudPositionsFront[i].x = -200;

        auto sprite = _cloud[_cloudIndicesFront[i]]->getSprite();
        sprite.setColor(sf::Color(255, 255, 255, 255 * dayFactor));
        sprite.setPosition(_cloudPositionsFront[i]);

        if (fade)
            this->fadeSprite(window, time, 0.25f, _cloud[_cloudIndicesFront[i]]);
        else {
            sprite.setColor(sf::Color::White);
            window.draw(sprite);
        }
    }

    return 0;
}

void Zappy::DrawRandom::drawMoonSun(sf::RenderWindow &window, bool night, float time)
{
    if (night){
         if (time > 19.0f) {
            this->_moon.get()->getSprite().setPosition(lerp(this->_moon.get()->getSprite().getPosition(), sf::Vector2f(100, 0), 6000.0));
        } else if (time > 0.1f && time < 6.0f)
            this->_moon.get()->getSprite().setPosition(lerp(this->_moon.get()->getSprite().getPosition(), sf::Vector2f(100, 1500), 35000.0));
        window.draw(this->_moon.get()->getSprite());
    } else {
        if (time > 6.0f && time < 12.0f) {
            this->_sun.get()->getSprite().setPosition(lerp(this->_sun.get()->getSprite().getPosition(), sf::Vector2f(100, 0), 15000.0));
        } else if (time > 12.0f && time < 18.5f)
            this->_sun.get()->getSprite().setPosition(lerp(this->_sun.get()->getSprite().getPosition(), sf::Vector2f(100, 1500), 30000.0));
        window.draw(this->_sun.get()->getSprite());
    }
}

void Zappy::DrawRandom::runDraw(sf::RenderWindow &window, bool night, float time)
{
    this->drawMoonSun(window, night, time);
    if (!night) {
        this->runCloud(window, time, false);
    } else {
        this->runStar(window, time, true);
    }
}

