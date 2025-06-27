/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description: 
** GUI
*/
#include "../includes/GUI.hpp"
#include "../includes/TrantorButtons.hpp"
#include "../includes/TileInfo.hpp"
#include <cmath>
#include <algorithm>
#include "GUI.hpp"

Zappy::GUI::GUI(const std::string &ip, size_t port)
{
    std::cout << "---------------SERVER---------------" << std::endl;
    this->_networkInfo = std::make_shared<Network>(this);
    this->_networkInfo->establishConnection(ip, port);
    this->_networkInfo->initProcess();
    std::srand(std::time(0));
    this->_recieveThread = std::thread(&Network::recieveFromServer, this->_networkInfo);
    this->_window.create(sf::VideoMode(1920, 1080, 8), "Zappy GUI", sf::Style::Close);
    this->background = sf::VertexArray(sf::Quads, 4);
    background[0].position = sf::Vector2f(0, 0);
    background[1].position = sf::Vector2f(this->_window.getSize().x, 0);
    background[2].position = sf::Vector2f(this->_window.getSize().x, this->_window.getSize().y);
    background[3].position = sf::Vector2f(0, this->_window.getSize().y);

    this->sky.getSprite().setPosition(0, 0);
    this->_TimeFont.loadFromFile("../GUI/assets/fonts/clock.ttf");
    this->_TimeText = sf::Text();
    this->_TimeText.setFont(this->_TimeFont);
    this->_TimeText.setPosition(sf::Vector2f(1700, 10));
    this->_TimeText.setScale(sf::Vector2f(2.0, 2.0));
    this->init();
    this->run();
    this->_recieveThread.join();
}

Zappy::GUI::~GUI()
{
}

void Zappy::GUI::updateClock()
{
    if (this->time < 0.0f) this->time = 0.0f;
    if (this->time >= 24.0f) this->time = 23.9999f;
    int hours = static_cast<int>(this->time);
    float fractionalHours = this->time - hours;
    int minutes = static_cast<int>(fractionalHours * 60);
    float fractionalMinutes = fractionalHours * 60 - minutes;
    int seconds = static_cast<int>(std::round(fractionalMinutes * 60));
    
    if (seconds == 60) {
        seconds = 0;
        minutes++;
    }
    if (minutes == 60) {
        minutes = 0;
        hours = (hours + 1) % 24;
    }

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << hours << ":"
        << std::setfill('0') << std::setw(2) << minutes << ":"
        << std::setfill('0') << std::setw(2) << seconds;

    this->_TimeText.setString(oss.str());
}

sf::Color Zappy::GUI::lerpColor(const sf::Color &a, sf::Color &b, float t)
{
    return sf::Color(
        a.r + t * (b.r - a.r),
        a.g + t * (b.g - a.g),
        a.b + t * (b.b - a.b)
    );
}

void Zappy::GUI::updateSky()
{
    sf::Color dawnColor(150, 180, 255);
    sf::Color noonColor(135, 206, 235);
    sf::Color duskColor(255, 100, 50);
    sf::Color nightColor(10, 10, 30);
    sf::Color dawnBottom(100, 100, 180);
    sf::Color noonBottom(200, 220, 255);
    sf::Color duskBottom(255, 150, 80);
    sf::Color nightBottom(10, 20, 40);
    sf::Color Bottom;
    sf::Color Top;

    float timeElapsed = this->_clock.getElapsedTime().asSeconds();
    this->time = timeElapsed * 0.1f;
    if (this->time > 24.f) {
        this->time -= 24;
        this->_clock.restart();
    }
    if (time < 6.f) {
        Top = lerpColor(nightColor, dawnColor, time / 6.f);
        Bottom = lerpColor(nightBottom, dawnBottom, time / 6.f);
    } else if (time < 12.f) {
        this->night = false;
        Top = lerpColor(dawnColor, noonColor, (time - 6.f) / 6.f);
        Bottom = lerpColor(dawnBottom, noonBottom, (time - 6.f) / 6.f);
    } else if (time < 18.f) {
        Top = lerpColor(noonColor, duskColor, (time - 12.f) / 6.f);
        Bottom = lerpColor(noonColor, duskBottom, (time - 12.f)/ 6.f);
    } else if (time < 20.f) {
        Top = lerpColor(duskColor, nightColor, (time - 18.f) / 2.f);
        Bottom = lerpColor(duskBottom, nightBottom, (time - 18.f) / 2.f);
    } else {
        Top = lerpColor(nightColor, dawnColor, (time - 20.f) / 4.f);
        Bottom = lerpColor(nightBottom, dawnBottom, (time - 20.F) / 4.f);
        this->night = true;
    }
    background[0].color = Top;
    background[1].color = Top;
    background[2].color = Bottom;
    background[3].color = Bottom;
}

void Zappy::GUI::dragView()
{
    if (this->_event.type == sf::Event::MouseButtonPressed && this->_event.mouseButton.button == sf::Mouse::Right) {
        _dragging = true;
        origin = this->_window.mapPixelToCoords(sf::Mouse::getPosition(this->_window));
    }
    if (this->_event.type == sf::Event::MouseButtonReleased && this->_event.mouseButton.button == sf::Mouse::Right) {
        _dragging = false;
    }
    if (this->_event.type == sf::Event::MouseMoved && _dragging) {
        sf::Vector2f newWorldPos = this->_window.mapPixelToCoords(sf::Mouse::getPosition(this->_window));
        sf::Vector2f delta = origin - newWorldPos;
        this->_view.move(delta);
        origin = this->_window.mapPixelToCoords(sf::Mouse::getPosition(_window));
    }
}

void Zappy::GUI::init()
{
    initPaths();
    this->_view = sf::View(sf::FloatRect(0, 0, this->_window.getSize().x, this->_window.getSize().y));
    this->_window.setView(this->_view);
    this->_view.setCenter(sf::Vector2f(this->_window.getSize().x/2, this->_window.getSize().y/2));
    for (int i = 0; i < 8; i++) {
        this->_items.push_back(std::make_shared<Items>(this->spritePaths[i], i));
    }
    this->_tileInfo = std::make_shared<TileInfo>(this);
    this->_trantorianInfo = std::make_shared<TrantorianInfo>(this);
    this->_broadcastTab = std::make_shared<BroadCastTab>();
    this->_view = sf::View(sf::FloatRect(0, 0, this->_window.getSize().x, this->_window.getSize().y));
    this->_window.setView(this->_view);
}

void Zappy::GUI::initPaths()
{
    this->spritePaths.push_back("../GUI/assets/egg_filled.png");
    this->spritePaths.push_back("../GUI/assets/food_filled.png");
    this->spritePaths.push_back("../GUI/assets/Gray_Cristal.png");
    this->spritePaths.push_back("../GUI/assets/Green_Cristal.png");
    this->spritePaths.push_back("../GUI/assets/Red_Cristal.png");
    this->spritePaths.push_back("../GUI/assets/Yellow_Cristal.png");
    this->spritePaths.push_back("../GUI/assets/Blue_Cristal.png");
    this->spritePaths.push_back("../GUI/assets/Orange_Cristal.png");
    std::cout << "init path done" << std::endl;
}

void Zappy::GUI::handleWindowEvents(  )
{
    int test = std::rand() % 20;
    while (this->_window.pollEvent(this->_event)) {
        if (this->_event.type == sf::Event::Closed)
            this->_window.close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            this->_window.close();
        zoomScroll();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
            this->_tileInfo->setTile(nullptr);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            this->_broadcastTab->pushToMessages("Blaaablaaabla" + std::to_string(test));
        }
    }
}

void Zappy::GUI::zoomScroll()
{
    if (_event.type == sf::Event::MouseWheelScrolled) {
        if (_event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
            float zoomFactor = 1.1f;
            if (_event.mouseWheelScroll.delta > 0) {
                this->_view.zoom(1.f / zoomFactor);
            } else {
                this->_view.zoom(zoomFactor);
            }
        }
    }
    this->_view.setSize(vclamp(this->_view.getSize(), sf::Vector2f(1920/2, 1080/2), sf::Vector2f(1920 * 1.5, 1080 * 1.5)));
}

sf::Vector2f Zappy::GUI::vclamp(sf::Vector2f val, sf::Vector2f min, sf::Vector2f max)
{
    if(val.x < min.x)
        val.x = min.x;
    if(val.y < min.y)
        val.y = min.y;
    if(val.x > max.x)
        val.x = max.x;
    if(val.y > max.y)
        val.y = max.y;

    return val;
}

void Zappy::GUI::touchView()
{
    sf::Vector2f pos = sf::Vector2f(0, 0);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        pos.y -= 15;
        this->_view.move(pos);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        pos.y += 15;
        this->_view.move(pos);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        pos.x -= 15;
        this->_view.move(pos);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        pos.x += 15;
        this->_view.move(pos);
    }
}

float Zappy::GUI::get_dist_to_cam(sf::View view, Vector2D pos)
{
    return (sqrt(pow(view.getCenter().x - pos.getX(), 2) + pow(view.getCenter().y - pos.getY(), 2)));
}

sf::Vector2i Zappy::GUI::getCenterTilePos(float px, float py, float originX, float originY, float tileWidth, float tileHeight)
{
    int rectIndexX = (originX / tileWidth) - (px / tileWidth);
    int rectIndexY = (py / tileHeight) - (originY / tileHeight);
    sf::Vector2i finalIndex(0, 0);
    finalIndex += sf::Vector2i(1, 1) * rectIndexY;
    finalIndex.x += rectIndexX;
    finalIndex.y -= rectIndexX;
    return finalIndex;
}

void Zappy::GUI::update()
{
    while (this->_window.isOpen()) {
        if (this->_framerateClock.getElapsedTime().asMicroseconds() < 1000000 / 60)
            continue;
        if (!this->_window.isOpen())
            break;
        touchView();
        this->_framerateClock.restart();
        this->_mouse.update(this->_window);
        this->_tileInfo->update(this->_mouse);
        this->_trantorianInfo->update(this->_mouse);
        this->_broadcastTab->update();
    }
}


void Zappy::GUI::display()
{
}

void Zappy::GUI::run()
{
    // this->_view.zoom(2);
    std::thread updateThread = std::thread(&GUI::update, this);
    while (this->_window.isOpen()) {
        this->handleWindowEvents();
        this->_window.clear(sf::Color::Black);
        this->_window.setView(this->_window.getDefaultView());
        this->updateSky();
        this->_window.draw(this->background);
        this->_effect.runDraw(this->_window, night, time);
        this->updateClock();
        this->_window.draw(this->_TimeText);
        this->_window.setView(this->_view);
        this->display_map();
        // this->display_objects();
        this->display_trantor();
        this->_window.setView(this->_window.getDefaultView());
        this->_trantorianInfo->render(this->_window);
        this->_tileInfo->render(this->_window);
        this->_broadcastTab->render(this->_window);
        this->displayOneShotAnimation();
        this->_window.setView(this->_view);
        this->_window.display();
    }
    updateThread.join();
    this->_networkInfo->shutDown();
}

void Zappy::GUI::display_map()
{
    sf::Vector2f size = {392, 225};
    sf::Vector2f pos = this->_map->getTiles()[0][0]->getTile()->getSprite().getPosition();
    pos.y += 55;
    sf::Vector2f viewPos = this->_view.getCenter();
    sf::Vector2i targetTileIndex = this->getCenterTilePos(viewPos.x, viewPos.y, pos.x + (size.x / 2), pos.y + (size.y / 2), size.x, size.y);
    targetTileIndex.x -= 5;
    targetTileIndex.y -= 5;
    for (int j = targetTileIndex.y; j < this->getMap()->getSize().getY() && j < targetTileIndex.y + 10; j++){
        if (j < 0)
            j = 0;
        for (int i = targetTileIndex.x; i < this->getMap()->getSize().getX() && i < targetTileIndex.x + 10; i++){
            if (i < 0)
                i = 0;
            this->_window.draw(_map->getTiles()[j][i]->getTile()->getSprite());
            for (size_t k = 1; k < 8; k++){
                if (this->_map->getTiles()[j][i].get()->getItems()[k] > 0){
                    this->_items[k]->getSprite()->getSprite().setPosition(this->_map->getTiles()[j][i]->getCenter().getX() + this->_map->getTiles()[j][i]->getOffsetsList()[k].getX(), 
                    this->_map->getTiles()[j][i]->getCenter().getY() + this->_map->getTiles()[j][i]->getOffsetsList()[k].getY() + 70);
                    this->_window.draw(this->_items[k]->getSprite()->getSprite());
                }
            }
        }
    }
}

void Zappy::GUI::display_sky()
{
    this->_window.draw(this->sky.getSprite());
}

void Zappy::GUI::display_trantor()
{
    for (auto trantorian: this->getMap()->getAllTrantorians()) {
        if (!trantorian.second)
            continue;
        this->_window.draw(trantorian.second->getSprite()->getSprite());
    }
}

void Zappy::GUI::display_eggs()
{
    for (auto egg: this->getMap()->getAllEggs()) {
        if (!egg.second)
            continue;
        this->_window.draw(egg.second->getDrawable()->getSprite());
    }
}

void Zappy::GUI::displayOneShotAnimation()
{
    for (size_t i = 0; i < this->_oneShotAnimationTab.size(); i++) {
        std::cout << "i: " << i << std::endl;
        this->_oneShotAnimationTab[i]->update();
        if (this->_oneShotAnimationTab[i]->isAlive())
            this->_window.draw(this->_oneShotAnimationTab[i]->getDrawable()->getSprite());
        if (!this->_oneShotAnimationTab[i]->isAlive())
            this->_oneShotAnimationTab.erase(this->_oneShotAnimationTab.begin() + i);
    }
}