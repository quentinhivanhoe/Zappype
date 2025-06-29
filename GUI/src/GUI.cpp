/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description: 
** GUI
*/
#include "../includes/GUI.hpp"

Zappy::GUI::GUI()
{
    this->_window.create(sf::VideoMode(1920, 1080, 8), "Zappy GUI", sf::Style::Close);
    this->runMenu();
}

Zappy::GUI::~GUI()
{
}

void Zappy::GUI::drawText(const std::string& string, sf::Vector2f position, sf::Color color, int characterSize, sf::RenderWindow &window)
{
    this->_menuText.setString(string);
    this->_menuText.setPosition(position);
    this->_menuText.setFillColor(color);
    this->_menuText.setCharacterSize(characterSize);
    window.draw(this->_menuText);
}

void Zappy::GUI::initConnectionFields()
{
    this->_ipRect.setSize({600, 150});
    this->_ipRect.setPosition({400, 250});
    this->_ipRect.setOrigin({300, 75});
    this->_ipRect.setFillColor(sf::Color(255, 255, 255, 150));
    this->_ipRect.setOutlineColor(sf::Color(255, 255, 255));
    this->_ipRect.setOutlineThickness(2);
    this->_portRect.setSize({600, 150});
    this->_portRect.setPosition({400, 550});
    this->_portRect.setOrigin({300, 75});
    this->_portRect.setFillColor(sf::Color(255, 255, 255, 150));
    this->_portRect.setOutlineColor(sf::Color(255, 255, 255));
    this->_portRect.setOutlineThickness(2);
    this->_font.loadFromFile("assets/arial.ttf");
    this->_menuText.setFont(this->_font);
    this->initEndScreenButtons();
}

void Zappy::GUI::runMenu()
{
    this->initConnectionFields();
    this->initMenuButtons();
    this->initMenuConnectionButtons();
    while (this->_window.isOpen()) {
        this->_window.setView(this->_window.getDefaultView());
        this->handleMenuEvents();
        this->_uiMouse.update(this->_window);
        if (this->_isOnConnectionPage)
            this->manageConnectionPage();
        else
            this->manageMenuPage();
        
    }
}

void Zappy::GUI::initMenuButtons()
{
    std::shared_ptr<Buttons> startButton = std::make_shared<Buttons>(this);
    startButton->setSize({400, 150});
    startButton->setPosition({960, 600});
    startButton->setMinScale({0.95, 0.95});
    startButton->setMaxScale({1.05, 1.05});
    startButton->setBgFillColor(sf::Color(230, 230, 230));
    startButton->setBgOutlineColor(sf::Color(150, 150, 150));
    startButton->setTitle("START");
    startButton->setTextFillColor(sf::Color::Black);
    startButton->setTextOutlineColor(sf::Color::Black);
    startButton->setTitlePositionOffset({0, -20});
    startButton->setCharacterSize(80);
    startButton->setFunction(&GUI::goToConnectionPage);
    this->_menuButtons.push_back(startButton);
    std::shared_ptr<Buttons> quitButton = std::make_shared<Buttons>(this);
    quitButton->setSize({400, 150});
    quitButton->setPosition({960, 800});
    quitButton->setMinScale({0.95, 0.95});
    quitButton->setMaxScale({1.05, 1.05});
    quitButton->setBgFillColor(sf::Color(230, 230, 230));
    quitButton->setBgOutlineColor(sf::Color(150, 150, 150));
    quitButton->setTitle("QUIT");
    quitButton->setTextFillColor(sf::Color::Black);
    quitButton->setTextOutlineColor(sf::Color::Black);
    quitButton->setTitlePositionOffset({0, -20});
    quitButton->setCharacterSize(80);
    quitButton->setFunction(&GUI::quit);
    this->_menuButtons.push_back(quitButton);
}

void Zappy::GUI::initMenuConnectionButtons()
{
    std::shared_ptr<Buttons> goBackButton = std::make_shared<Buttons>(this);
    goBackButton->setSize({200, 100});
    goBackButton->setPosition({1920 - 30 - 100, 1080 - 30 - 50});
    goBackButton->setMinScale({0.95, 0.95});
    goBackButton->setMaxScale({1.05, 1.05});
    goBackButton->setBgFillColor(sf::Color(230, 230, 230, 150));
    goBackButton->setBgOutlineColor(sf::Color::White);
    goBackButton->setTitle("RETURN");
    goBackButton->setTextFillColor(sf::Color::Black);
    goBackButton->setTextOutlineColor(sf::Color::Black);
    goBackButton->setTitlePositionOffset({0, -20});
    goBackButton->setCharacterSize(30);
    goBackButton->setFunction(&GUI::goBackToMenu);
    this->_connectionButtons.push_back(goBackButton);
    std::shared_ptr<Buttons> confirmButton = std::make_shared<Buttons>(this);
    confirmButton->setSize({510, 150});
    confirmButton->setPosition({360, 1080 - 30 - 75});
    confirmButton->setMinScale({0.95, 0.95});
    confirmButton->setMaxScale({1.05, 1.05});
    confirmButton->setBgFillColor(sf::Color(230, 230, 230, 150));
    confirmButton->setBgOutlineColor(sf::Color::White);
    confirmButton->setTitle("Connect");
    confirmButton->setTextFillColor(sf::Color::Black);
    confirmButton->setTextOutlineColor(sf::Color::Black);
    confirmButton->setTitlePositionOffset({0, -20});
    confirmButton->setCharacterSize(50);
    confirmButton->setFunction(&GUI::connect);
    this->_connectionButtons.push_back(confirmButton);
    std::shared_ptr<Buttons> selectIpButton = std::make_shared<Buttons>(this);
    selectIpButton->setSize({510, 150});
    selectIpButton->setPosition({1010, 250});
    selectIpButton->setMinScale({0.95, 0.95});
    selectIpButton->setMaxScale({1.05, 1.05});
    selectIpButton->setBgFillColor(sf::Color(230, 230, 230, 150));
    selectIpButton->setBgOutlineColor(sf::Color::White);
    selectIpButton->setTitle("Select");
    selectIpButton->setTextFillColor(sf::Color::Black);
    selectIpButton->setTextOutlineColor(sf::Color::Black);
    selectIpButton->setTitlePositionOffset({0, -20});
    selectIpButton->setCharacterSize(50);
    selectIpButton->setFunction(&GUI::selectIp);
    this->_connectionButtons.push_back(selectIpButton);
    std::shared_ptr<Buttons> confirmIpButton = std::make_shared<Buttons>(this);
    confirmIpButton->setSize({510, 150});
    confirmIpButton->setPosition({1580, 250});
    confirmIpButton->setMinScale({0.95, 0.95});
    confirmIpButton->setMaxScale({1.05, 1.05});
    confirmIpButton->setBgFillColor(sf::Color(230, 230, 230, 150));
    confirmIpButton->setBgOutlineColor(sf::Color::White);
    confirmIpButton->setTitle("Confirm");
    confirmIpButton->setTextFillColor(sf::Color::Black);
    confirmIpButton->setTextOutlineColor(sf::Color::Black);
    confirmIpButton->setTitlePositionOffset({0, -20});
    confirmIpButton->setCharacterSize(50);
    confirmIpButton->setFunction(&GUI::confirmIp);
    this->_connectionButtons.push_back(confirmIpButton);
    std::shared_ptr<Buttons> selectPortButton = std::make_shared<Buttons>(this);
    selectPortButton->setSize({510, 150});
    selectPortButton->setPosition({1010, 550});
    selectPortButton->setMinScale({0.95, 0.95});
    selectPortButton->setMaxScale({1.05, 1.05});
    selectPortButton->setBgFillColor(sf::Color(230, 230, 230, 150));
    selectPortButton->setBgOutlineColor(sf::Color::White);
    selectPortButton->setTitle("Select");
    selectPortButton->setTextFillColor(sf::Color::Black);
    selectPortButton->setTextOutlineColor(sf::Color::Black);
    selectPortButton->setTitlePositionOffset({0, -20});
    selectPortButton->setCharacterSize(50);
    selectPortButton->setFunction(&GUI::selectPort);
    this->_connectionButtons.push_back(selectPortButton);
    std::shared_ptr<Buttons> confirmPortButton = std::make_shared<Buttons>(this);
    confirmPortButton->setSize({510, 150});
    confirmPortButton->setPosition({1580, 550});
    confirmPortButton->setMinScale({0.95, 0.95});
    confirmPortButton->setMaxScale({1.05, 1.05});
    confirmPortButton->setBgFillColor(sf::Color(230, 230, 230, 150));
    confirmPortButton->setBgOutlineColor(sf::Color::White);
    confirmPortButton->setTitle("Confirm");
    confirmPortButton->setTextFillColor(sf::Color::Black);
    confirmPortButton->setTextOutlineColor(sf::Color::Black);
    confirmPortButton->setTitlePositionOffset({0, -20});
    confirmPortButton->setCharacterSize(50);
    confirmPortButton->setFunction(&GUI::confirmPort);
    this->_connectionButtons.push_back(confirmPortButton);
}

void Zappy::GUI::connect()
{
    this->_ipSelected = false;
    this->_portSelected = false;
    this->_hasConnectionFailed = false;
    if (this->_tmpIp.empty() || this->_tmpPort.empty())
        return;
    try {
        this->_networkInfo = std::make_shared<Network>(this);
        this->_networkInfo->establishConnection(this->_tmpIp, std::stoi(this->_tmpPort));
        this->runGame();
        this->_isOnConnectionPage = false;
        this->_networkInfo.reset();
    } catch(const Error& e) {
        std::cerr << "Zappy Exception - [From : " << e.where() << "] - [" << e.what() << "]" << std::endl;
        this->_hasConnectionFailed = true;
        this->_isOnConnectionPage = true;
        this->_networkInfo.reset();
    }
}

void Zappy::GUI::selectIp()
{
    this->_ipSelected = true;
    this->_portSelected = false;
}

void Zappy::GUI::confirmIp()
{
    this->_ipSelected = false;
}

void Zappy::GUI::selectPort()
{
    this->_ipSelected = false;
    this->_portSelected = true;
}

void Zappy::GUI::confirmPort()
{
    this->_portSelected = false;
}


void Zappy::GUI::quit()
{
    this->_window.close();
}

void Zappy::GUI::goBackToMenu()
{
    this->_hasConnectionFailed = false;
    this->_isOnConnectionPage = false;
}

void Zappy::GUI::goToConnectionPage()
{
    this->_isOnConnectionPage = true;
}

void Zappy::GUI::renderIpAndPort()
{
    if (this->_tmpIp.empty())
        this->drawText("255.255.255.255", {120, 210}, sf::Color(0, 0, 0, 50), 60, this->_window);
    else
        this->drawText(this->_tmpIp, {120, 210}, sf::Color::Black, 60, this->_window);
    if (this->_tmpPort.empty())
        this->drawText("8000", {120, 510}, sf::Color(0, 0, 0, 50), 60, this->_window);
    else
        this->drawText(this->_tmpPort, {120, 510}, sf::Color::Black, 60, this->_window);
}

void Zappy::GUI::manageMenuPage()
{
    for (auto button : this->_menuButtons)
        button->update(this->_uiMouse);
    this->_window.clear(sf::Color::White);
    this->_window.draw(this->_menuBg.getSprite());
    for (auto button : this->_menuButtons)
        button->render(this->_window);
    this->_window.display();
}

void Zappy::GUI::manageConnectionPage()
{
    for (auto button : this->_connectionButtons)
        button->update(this->_uiMouse);
    if (this->_ipSelected)
        this->_ipRect.setFillColor(sf::Color(255, 255, 255, 200));
    else
        this->_ipRect.setFillColor(sf::Color(255, 255, 255, 150));
    if (this->_portSelected)
        this->_portRect.setFillColor(sf::Color(255, 255, 255, 200));
    else
        this->_portRect.setFillColor(sf::Color(255, 255, 255, 150));
    this->_window.clear(sf::Color::White);
    this->_window.draw(this->_menuBgDark.getSprite());
    for (auto button : this->_connectionButtons)
        button->render(this->_window);
    this->_window.draw(this->_ipRect);
    this->_window.draw(this->_portRect);
    if (this->_hasConnectionFailed)
        this->drawText("*Connection refused.", {120, 750}, sf::Color::Red, 60, this->_window);
    this->renderIpAndPort();
    this->_window.display();
}

void Zappy::GUI::runGame()
{
    this->_networkInfo->initProcess();
    std::srand(std::time(0));
    this->_recieveThread = std::thread(&Network::recieveFromServer, this->_networkInfo);
    this->background = sf::VertexArray(sf::Quads, 4);
    background[0].position = sf::Vector2f(0, 0);
    background[1].position = sf::Vector2f(this->_window.getSize().x, 0);
    background[2].position = sf::Vector2f(this->_window.getSize().x, this->_window.getSize().y);
    background[3].position = sf::Vector2f(0, this->_window.getSize().y);
    this->sky.getSprite().setPosition(0, 0);
    this->_TimeFont.loadFromFile("assets/fonts/clock.ttf");
    this->_TimeText = sf::Text();
    this->_TimeText.setFont(this->_TimeFont);
    this->_TimeText.setPosition(sf::Vector2f(1700, 10));
    this->_TimeText.setScale(sf::Vector2f(2.0, 2.0));
    this->init();
    this->run();
    this->_recieveThread.join();
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

void Zappy::GUI::quitGameToMenu()
{
    this->_gameIsRunning = false;
    this->_lastTeamAlive = "";
}

void Zappy::GUI::initEndScreenButtons()
{
    std::shared_ptr<Buttons> backToMenuButton = std::make_shared<Buttons>(this);
    backToMenuButton->setSize({400, 150});
    backToMenuButton->setPosition({960, 600});
    backToMenuButton->setMinScale({0.95, 0.95});
    backToMenuButton->setMaxScale({1.05, 1.05});
    backToMenuButton->setBgFillColor(sf::Color(230, 230, 230));
    backToMenuButton->setBgOutlineColor(sf::Color(150, 150, 150));
    backToMenuButton->setTitle("MENU");
    backToMenuButton->setTextFillColor(sf::Color::Black);
    backToMenuButton->setTextOutlineColor(sf::Color::Black);
    backToMenuButton->setTitlePositionOffset({0, -20});
    backToMenuButton->setCharacterSize(80);
    backToMenuButton->setFunction(&GUI::quitGameToMenu);
    this->_endScreenButtons.push_back(backToMenuButton);
    std::shared_ptr<Buttons> quitButton = std::make_shared<Buttons>(this);
    quitButton->setSize({400, 150});
    quitButton->setPosition({960, 800});
    quitButton->setMinScale({0.95, 0.95});
    quitButton->setMaxScale({1.05, 1.05});
    quitButton->setBgFillColor(sf::Color(230, 230, 230));
    quitButton->setBgOutlineColor(sf::Color(150, 150, 150));
    quitButton->setTitle("QUIT");
    quitButton->setTextFillColor(sf::Color::Black);
    quitButton->setTextOutlineColor(sf::Color::Black);
    quitButton->setTitlePositionOffset({0, -20});
    quitButton->setCharacterSize(80);
    quitButton->setFunction(&GUI::quit);
    this->_endScreenButtons.push_back(quitButton);
}

void Zappy::GUI::init()
{
    initPaths();
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
    this->spritePaths.push_back("assets/egg_filled.png");
    this->spritePaths.push_back("assets/meat.png");
    this->spritePaths.push_back("assets/Gray_Cristal.png");
    this->spritePaths.push_back("assets/Green_Cristal.png");
    this->spritePaths.push_back("assets/Red_Cristal.png");
    this->spritePaths.push_back("assets/Yellow_Cristal.png");
    this->spritePaths.push_back("assets/Blue_Cristal.png");
    this->spritePaths.push_back("assets/Orange_Cristal.png");
}

void Zappy::GUI::handleMenuEvents()
{
    sf::Event event;
    while (this->_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            this->_window.close();
        if (event.type == sf::Event::TextEntered) {
            char letter = event.text.unicode;
            if (this->_ipSelected) {
                if (letter == '\b' && !this->_tmpIp.empty())
                    this->_tmpIp.pop_back();
                if (Parser::isNum({letter}) || letter == '.'){
                    if (this->_tmpIp.size() >= 15)
                        this->_tmpIp.pop_back();
                    this->_tmpIp += {letter};
                }
            }
            if (this->_portSelected) {
                if (letter == '\b' && !this->_tmpPort.empty())
                    this->_tmpPort.pop_back();
                if (Parser::isNum({letter})){
                    if (this->_tmpPort.size() >= 4)
                        this->_tmpPort.pop_back();
                    this->_tmpPort += {letter};
                }
            }
        }
    }
}

void Zappy::GUI::handleWindowEvents(  )
{
    while (this->_window.pollEvent(this->_event)) {
        if (this->_event.type == sf::Event::Closed)
            this->_window.close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            this->_gameIsRunning = false;
        zoomScroll();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
            this->_tileInfo->setTile(nullptr);
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
    while (this->_window.isOpen() && this->_gameIsRunning) {
        if (this->_framerateClock.getElapsedTime().asMicroseconds() < 1000000 / 60)
            continue;
        if (!this->_window.isOpen())
            break;
        this->_framerateClock.restart();
        this->_mouse.update(this->_window);
        this->_uiMouse.update(this->_window);
        if (this->_isEnding)
            continue;
        this->_tileInfo->update(this->_uiMouse);
        this->_trantorianInfo->update(this->_uiMouse);
        this->_broadcastTab->update();
        this->updateTrantor();
        this->handleTileButtons();
        this->updateSky();
        touchView();
    }
}

void Zappy::GUI::manageEndOfGame()
{
    for (auto button : this->_endScreenButtons)
        button->update(this->_uiMouse);
    this->_window.setView(this->_window.getDefaultView());
    this->_window.clear(sf::Color::Black);
    this->_window.draw(this->_menuBgDark.getSprite());
    if (!this->_lastTeamAlive.empty())
        this->drawText(this->_lastTeamAlive + " won the game !", {500, 200}, sf::Color::White, 100, this->_window);
    else
        this->drawText("nobody won ...?", {500, 500}, sf::Color::White, 100, this->_window);
    for (auto button : this->_endScreenButtons)
        button->render(this->_window);
    this->_window.display();

}

void Zappy::GUI::run()
{
    this->_gameIsRunning = true;
    this->_isEnding = false;
    std::thread updateThread = std::thread(&GUI::update, this);
    while (this->_window.isOpen() && this->_gameIsRunning) {
        this->handleWindowEvents();
        if (this->_isEnding) {
            this->manageEndOfGame();
            continue;
        }
        this->_window.clear(sf::Color::Black);
        this->_window.setView(this->_window.getDefaultView());
        this->_window.draw(this->background);
        this->_effect.runDraw(this->_window, night, time);
        this->updateClock();
        this->_window.draw(this->_TimeText);
        this->_window.setView(this->_view);
        this->display_map();
        this->display_eggs();
        this->display_trantor();
        this->displayOneShotAnimation();
        this->_window.setView(this->_window.getDefaultView());
        this->_trantorianInfo->render(this->_window);
        this->_tileInfo->render(this->_window);
        this->_broadcastTab->render(this->_window);
        this->_window.setView(this->_view);
        this->_window.display();
    }
    updateThread.join();
    this->_networkInfo->shutDown();
}

void Zappy::GUI::handleTileButtons()
{
    sf::Vector2f size = {392, 225};
    sf::Vector2f pos = this->_map->getTiles()[0][0]->getTile()->getSprite().getPosition();
    pos.y += 55;
    sf::Vector2f viewPos = this->_view.getCenter();
    sf::Vector2i targetTileIndex = this->getCenterTilePos(viewPos.x, viewPos.y, pos.x + (size.x / 2), pos.y + (size.y / 2), size.x, size.y);
    targetTileIndex.x -= 6;
    targetTileIndex.y -= 6;
    for (int j = targetTileIndex.y; j < this->getMap()->getSize().getY() && j < targetTileIndex.y + 16; j++){
        if (j < 0)
            j = 0;
        for (int i = targetTileIndex.x; i < this->getMap()->getSize().getX() && i < targetTileIndex.x + 16; i++){
            if (i < 0)
                i = 0;
            if (this->_tileInfo->getTile() == this->_map->getTiles()[j][i])
                this->_map->getTiles()[j][i]->getTile()->getSprite().setColor(sf::Color(255, 255, 100));
            else
                this->_map->getTiles()[j][i]->getTile()->getSprite().setColor(sf::Color::White);
            this->_map->getTiles()[j][i]->getButton()->update(this->_mouse);
        }
    }
}

void Zappy::GUI::display_map()
{
    sf::Vector2f size = {392, 225};
    sf::Vector2f pos = this->_map->getTiles()[0][0]->getTile()->getSprite().getPosition();
    pos.y += 55;
    sf::Vector2f viewPos = this->_view.getCenter();
    sf::Vector2i targetTileIndex = this->getCenterTilePos(viewPos.x, viewPos.y, pos.x + (size.x / 2), pos.y + (size.y / 2), size.x, size.y);
    targetTileIndex.x -= 6;
    targetTileIndex.y -= 6;
    for (int j = targetTileIndex.y; j < this->getMap()->getSize().getY() && j < targetTileIndex.y + 16; j++){
        if (j < 0)
            j = 0;
        for (int i = targetTileIndex.x; i < this->getMap()->getSize().getX() && i < targetTileIndex.x + 16; i++){
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

void Zappy::GUI::updateTrantor()
{
    for (auto trantorian: this->getMap()->getAllTrantorians()) {
        if (!trantorian.second)
            continue;
        trantorian.second->updateTrantorSprite();
    }
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
        this->_oneShotAnimationTab[i]->update();
        if (this->_oneShotAnimationTab[i]->isAlive())
            this->_window.draw(this->_oneShotAnimationTab[i]->getDrawable()->getSprite());
        if (!this->_oneShotAnimationTab[i]->isAlive())
            this->_oneShotAnimationTab.erase(this->_oneShotAnimationTab.begin() + i);
    }
}
