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
    for (size_t i = 0; i < this->_map->getTiles().size(); i++){
        for (size_t j = 0; j < this->_map->getTiles()[i].size(); j++){
            this->_map->getTiles()[j][i]->getTile()->set_offsets();
            this->_map->getTiles()[i][j].get()->setOffsetsList(this->_map->getTiles()[j][i]->getTile()->get_offsets());
        }
    }
    
    this->sky.getSprite().setPosition(0, 0);
    this->init();
    this->run();
    this->_recieveThread.join();
}

Zappy::GUI::~GUI()
{
}

void Zappy::GUI::dragView()
{
    sf::Vector2f origin;

    if (this->_event.type == sf::Event::MouseButtonPressed && this->_event.mouseButton.button == sf::Mouse::Right) {
        // printf("right click\n");
        _dragging = true;
        origin = this->_window.mapPixelToCoords(sf::Mouse::getPosition(this->_window));
    }
    if (this->_event.type == sf::Event::MouseButtonReleased && this->_event.mouseButton.button == sf::Mouse::Right) {
        // printf("right released\n");
        _dragging = false;
    }
    if (this->_event.type == sf::Event::MouseMoved && _dragging) {
        // printf("mouse moving\n");
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
    while (this->_window.pollEvent(this->_event)) {
        if (this->_event.type == sf::Event::Closed)
            this->_window.close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            this->_window.close();
        touchView();
        zoomScroll();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
            this->_tileInfo->setTile(nullptr);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            this->_tileInfo->setTile(this->_map->getTiles()[20][20]);
            this->_tileInfo->updateTrantorButtonsTab();
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

void Zappy::GUI::run()
{
    // this->_view.zoom(2);
    set_map();
    while (this->_window.isOpen()) {
        if (this->_framerateClock.getElapsedTime().asMicroseconds() < 1000000 / 60)
            continue;
        this->_framerateClock.restart();
        this->_mouse.update(this->_window);
        this->_tileInfo->update(this->_mouse);
        this->_trantorianInfo->update(this->_mouse);
        this->handleWindowEvents();
        this->_window.clear(sf::Color::Black);
        this->_window.setView(this->_window.getDefaultView());
        this->display_sky();
        this->_window.setView(this->_view);
        this->display_map();
        this->display_objects();
        this->display_trantor();
        this->_window.setView(this->_window.getDefaultView());
        this->_trantorianInfo->render(this->_window);
        this->_tileInfo->render(this->_window);
        this->_window.setView(this->_view);
        this->_window.display();
    }
    this->_networkInfo->shutDown();
}

void Zappy::GUI::set_map()
{
    Vector2D offset = Vector2D(1920/2, 0);
    Vector2D size = Vector2D(500, 500);
    for (size_t j = 0; j < this->getMap()->getSize().getY(); j++){
        for (int i = 0; i < this->getMap()->getSize().getX(); i++){
            Vector2D size = Vector2D(_map->getTiles()[j][i]->getTile()->getTexture().getSize().x * this->getTileScale() / (2) - 5, _map->getTiles()[j][i]->getTile()->getTexture().getSize().y  * this->getTileScale() / (2) - 85);
            offset.setX(offset.getX() - size.getX());
            offset.setY(offset.getY() + size.getY());

            std::cout << offset.getX() << " " << offset.getY() << std::endl;
            this->_map->getTiles()[j][i]->getTile()->getSprite().setPosition(offset.getX(), offset.getY());
            std::cout << this->_map->getTiles()[j][i]->getTile()->getSprite().getPosition().x << " " << this->_map->getTiles()[j][i]->getTile()->getSprite().getPosition().y << std::endl;
            _map->getTiles()[j][i].get()->setCenter(Vector2D(offset.getX() + (size.getX()), offset.getY() + (size.getY())));
            _map->getTiles()[j][i].get()->setPos(offset);
        }
        offset = Vector2D(
        (1920/2 + (size.getX() - 310) * (j + 1)),
        (0 + (size.getY() - 390) * (j + 1)));
    }
}

void Zappy::GUI::display_map()
{
    for (int j = 0; j < this->getMap()->getSize().getY(); j++){
        for (int i = 0; i < this->getMap()->getSize().getX(); i++){
            if (get_dist_to_cam(this->_view, this->_map->getTiles()[j][i]->getPos()) < 2000)
                this->_window.draw(_map->getTiles()[j][i]->getTile()->getSprite());
        }

    }
}

void Zappy::GUI::display_sky()
{
    this->_window.draw(this->sky.getSprite());
}

void Zappy::GUI::display_objects()
{
    return;
    for (size_t i = 0; i < this->_map->getTiles().size(); i++){
        for (size_t j = 0; j < this->_map->getTiles()[i].size(); j++){
            if (this->_map->getTiles()[i][j]->getActivity() == false)
                continue;
            for (size_t k = 0; k < 8; k++){
                if (this->_map->getTiles()[i][j].get()->getItems()[k] > 0){
                    this->_items[k]->getSprite()->getSprite().setPosition(this->_map->getTiles()[i][j]->getCenter().getX() + this->_map->getTiles()[i][j]->getOffsetsList()[k].getX(), 
                    this->_map->getTiles()[i][j]->getCenter().getY() + this->_map->getTiles()[i][j]->getOffsetsList()[k].getY());
                    this->_window.draw(this->_items[k]->getSprite()->getSprite());
                }          
            }
        }
    }
}

void Zappy::GUI::display_trantor()
{
    //printf("TEAM\n");
    for (auto team: this->_map->getTeams()) {
        for (auto trantorian: team.second->getTrantorians()) {
            //to be optimized
            trantorian->getSprite()->getSprite().setPosition(this->_map->getTiles()[trantorian->getTilePos().x][trantorian->getTilePos().y]->getCenter().getX(), this->_map->getTiles()[trantorian->getTilePos().x][trantorian->getTilePos().y]->getCenter().getY() + 70);
            this->_window.draw(trantorian->getSprite()->getSprite());
        }
    }
}