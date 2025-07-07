/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** Parser functions
*/

#include "../includes/Parser.hpp"

std::vector<std::string> Zappy::Parser::parseLine(const std::string& line, char delimiter)
{
    std::vector<std::string> tab;
    std::string temp = line;
    while (temp.find('\n') != temp.npos)
        temp.replace(temp.find('\n'), 1, " ");
    std::stringstream tempLine(temp);
    std::string element;
    while (std::getline(tempLine, element, delimiter))
        if (!element.empty())
            tab.push_back(element);
    return tab;
}

void Zappy::Parser::showArgs(std::vector<std::string> args)
{
    std::cout << "[Debug] {";
    for (size_t i = 0; i < args.size(); i++) {
        std::cout << args[i];
        if (i + 1 < args.size())
            std::cout << ", ";
    }
    std::cout << "}" << std::endl;
}

void Zappy::Parser::manageResponse(std::vector<std::string> args, [[maybe_unused]] Zappy::Network *network)
{
    std::map<std::string, void (Zappy::Parser:: *)(std::vector<std::string>, Network *)> funcTab = {
        {"msz", &Zappy::Parser::manageMSZ},
        {"pls", &Zappy::Parser::manageSPI},
        {"pnu", &Zappy::Parser::manageSPN},
        {"enu", &Zappy::Parser::manageENU},
        {"bct", &Zappy::Parser::manageBCT},
        {"ppo", &Zappy::Parser::managePPO},
        {"plv", &Zappy::Parser::managePLV},
        {"pin", &Zappy::Parser::managePIN},
        {"sgt", &Zappy::Parser::manageSGT},
        {"sst", &Zappy::Parser::manageSST},
        {"pnw", &Zappy::Parser::managePNW},
        {"pex", &Zappy::Parser::managePEX},
        {"pbc", &Zappy::Parser::managePBC},
        {"pic", &Zappy::Parser::managePIC},
        {"pie", &Zappy::Parser::managePIE},
        {"pfk", &Zappy::Parser::managePFK},
        {"pdr", &Zappy::Parser::managePDR},
        {"pgt", &Zappy::Parser::managePGT},
        {"pdi", &Zappy::Parser::managePDI},
        {"enw", &Zappy::Parser::manageENW},
        {"ebo", &Zappy::Parser::manageEBO},
        {"edi", &Zappy::Parser::manageEDI},
        {"els", &Zappy::Parser::manageELS},
        {"seg", &Zappy::Parser::manageSEG},
        {"smg", &Zappy::Parser::manageSMG},
        {"suc", &Zappy::Parser::manageSUC},
        {"sbp", &Zappy::Parser::manageSBP},
    };
    if (args.empty())
        return;
    if (funcTab[args.front()])
        (this->*funcTab[args.front()])(args, network);
    else {
        if (network->getGui()->isDebugging())
            std::cout << "[DEBUG] response not found" << std::endl;
    }
}

bool Zappy::Parser::isNum(const std::string& string)
{
    std::regex regExp("[0-9]+");
    return std::regex_match(string, regExp);
}

bool Zappy::Parser::isIndex(const std::string& string)
{
    std::regex regExp("#[0-9]+");
    return std::regex_match(string, regExp);
}

size_t Zappy::Parser::nbOccur(const std::string& string, const std::string& key)
{
    std::string tempString = string;
    size_t count = 0;
    size_t pos = tempString.find(key);
    while (pos != tempString.npos) {
        tempString = tempString.substr(pos + key.size());
        pos = tempString.find(key);
        count++;
    }
    return count;
}

std::vector<std::string> Zappy::Parser::splitLine(const std::string& string, const std::string& sep)
{
    std::string tempString = string;
    std::vector<std::string> tab;
    size_t pos = tempString.find(sep);
    while (pos != tempString.npos) {
        if (!tempString.substr(0, pos).empty())
            tab.push_back(tempString.substr(0, pos));
        tempString = tempString.substr(pos + sep.size());
        pos = tempString.find(sep);
    }
    return tab;
}

std::vector<std::string> Zappy::Parser::argsToString(std::vector<int> args)
{
    std::vector<std::string> tab;

    for (auto item: args)
        tab.push_back(std::to_string(item));
    return tab;
}

//----------------------------------------------------------------------//

void Zappy::Parser::manageMSZ([[maybe_unused]] std::vector<std::string> args, [[maybe_unused]] Zappy::Network *network)
{
    if (args.size() != 3) {
        if (network->getGui()->isDebugging())
            std::cout << "[DEBUG] Wrong number of args, response failed." << std::endl;
        return;
    }
    if (!Parser::isNum(args[1]) || !Parser::isNum(args[2])) {
        if (network->getGui()->isDebugging())
            std::cout << "[DEBUG] Args must be positive numbers." << std::endl;
        return;
    }
    network->setMapSize({std::stoi(args[1]), std::stoi(args[2])});
    network->getGui()->setMapSize({std::stoi(args[1]), std::stoi(args[2])});
    if (network->getGui()->isDebugging())
        Parser::showArgs(args);
}

void Zappy::Parser::manageBCT([[maybe_unused]] std::vector<std::string> args, [[maybe_unused]] Zappy::Network *network)
{
    if (args.size() != 10) {
        if (network->getGui()->isDebugging())
            std::cout << "[DEBUG] Wrong number of args, response failed." << std::endl;
        return;
    }
    for (size_t i = 1; i < args.size(); i++) {
        if (!Parser::isNum(args[i])) {
        if (network->getGui()->isDebugging())
                std::cout << "[DEBUG] Args must be positive numbers." << std::endl;
            return;
        }
    }
    size_t posX = std::stoi(args[1]);
    size_t posY = std::stoi(args[2]);
    if (posY >= network->getGui()->getMap()->getTiles().size())
        return Parser::showArgs(args);
    if (posX >= network->getGui()->getMap()->getTiles()[posY].size())
        return Parser::showArgs(args);
    for (size_t i = 3; i < args.size(); i++)
        network->getGui()->getMap()->getTiles()[posY][posX]->setNItem(static_cast<Item>(i - 2), std::stoi(args[i]));
    if (network->getGui()->isDebugging())
        Parser::showArgs(args);
}

void Zappy::Parser::manageSPN([[maybe_unused]] std::vector<std::string> args, [[maybe_unused]] Zappy::Network *network)
{
    if (args.size() != 2) {
        if (network->getGui()->isDebugging())
            std::cout << "[DEBUG] Wrong number of args, response failed." << std::endl;
        return;
    }
    if (!Parser::isNum(args[1])) {
        if (network->getGui()->isDebugging())
            std::cout << "[DEBUG] Args must be positive numbers." << std::endl;
        return;
    }
    network->setPlayerNb(std::stoi(args[1]));
    network->getGui()->setPlayerNb(std::stoi(args[1]));
    if (network->getGui()->isDebugging())
        Parser::showArgs(args);
}

void Zappy::Parser::manageENU([[maybe_unused]] std::vector<std::string> args, [[maybe_unused]] Zappy::Network *network)
{
    if (args.size() != 2) {
        if (network->getGui()->isDebugging())
            std::cout << "[DEBUG] Wrong number of args, response failed." << std::endl;
        return;
    }
    if (!Parser::isNum(args[1])) {
        if (network->getGui()->isDebugging())
            std::cout << "[DEBUG] Args must be positive numbers." << std::endl;
        return;
    }
    network->setEggNb(std::stoi(args[1]));
    if (network->getGui()->isDebugging())
        Parser::showArgs(args);
}

void Zappy::Parser::manageSPI([[maybe_unused]] std::vector<std::string> args, [[maybe_unused]] Zappy::Network *network)
{
    if (args.size() != 8) {
        if (network->getGui()->isDebugging())
            std::cout << "[DEBUG] Wrong number of args, response failed." << std::endl;
        return;
    }
    if (!Parser::isIndex(args[1])) {
        if (network->getGui()->isDebugging())
            std::cout << "[DEBUG] Index must be a # followed by a positive number." << std::endl;
        return;
    }
    for (size_t i = 2; i < 5; i++) {
        if (!Parser::isNum(args[i])) {
        if (network->getGui()->isDebugging())
                std::cout << "[DEBUG] Args must be positive numbers." << std::endl;
            return;
        }
    }
    if (!Parser::isNum(args[7])) {
        if (network->getGui()->isDebugging())
            std::cout << "[DEBUG] Args must be positive numbers." << std::endl;
        return;
    }
    std::shared_ptr<Trantorian> targetTrantorian = network->getGui()->getMap()->getTrantorianByID(std::stoi(args[1].substr(1)));
    if (!targetTrantorian)
        targetTrantorian = std::make_shared<Trantorian>();
    sf::Vector2i pos = {std::stoi(args[2]), std::stoi(args[3])};
    targetTrantorian->setId(std::stoi(args[1].substr(1)));
    targetTrantorian->setTilePos(pos);
    targetTrantorian->setDirection(std::stoi(args[4]));
    targetTrantorian->setTeamName(args[6]);
    targetTrantorian->setLevel(std::stoi(args[7]));
    network->getGui()->getMap()->addTrantorian(targetTrantorian);
    network->getGui()->getMap()->getTrantorianByID(std::stoi(args[1].substr(1)))->getSprite()->getSprite().setPosition(network->getGui()->getMap()->getTiles()[pos.y][pos.x]->getCenter().getX(), network->getGui()->getMap()->getTiles()[pos.y][pos.x]->getCenter().getY());
    if (network->getGui()->isDebugging())
        Parser::showArgs(args);
}

void Zappy::Parser::manageELS(std::vector<std::string> args, [[maybe_unused]] Zappy::Network *network)
{
    if (args.size() != 5) {
        if (network->getGui()->isDebugging())
            std::cout << "[DEBUG] Wrong number of args, response failed." << std::endl;
        return;
    }
    if (!Parser::isIndex(args[1])) {
        if (network->getGui()->isDebugging())
            std::cout << "[DEBUG] Index must be a # followed by a positive number." << std::endl;
        return;
    }
    if (!Parser::isNum(args[2]) || !Parser::isNum(args[3])) {
        if (network->getGui()->isDebugging())
            std::cout << "[DEBUG] Args must be positive numbers." << std::endl;
        return;
    }
    std::shared_ptr<Egg> targetEgg = network->getGui()->getMap()->getEggById(std::stoi(args[1].substr(1)));
    if (!targetEgg)
        targetEgg = std::make_shared<Egg>();
    sf::Vector2i pos = {std::stoi(args[2]), std::stoi(args[3])};
    std::shared_ptr<Tile> targetTile = network->getGui()->getMap()->getTiles()[pos.y][pos.x];
    targetEgg->setId(std::stoi(args[1].substr(1)));
    targetEgg->setIndexPos(pos);
    targetEgg->setTeamName(args[4]);
    network->getGui()->getMap()->addEgg(targetEgg);
    targetEgg->getDrawable()->getSprite().setPosition(targetTile->getCenter().getX() + targetTile->getOffsetsList()[0].getX(), targetTile->getCenter().getY() + targetTile->getOffsetsList()[0].getY() + 70);
    network->getGui()->getMap()->getEggById(std::stoi(args[1].substr(1)))->getDrawable()->getSprite().setPosition(targetTile->getCenter().getX() + targetTile->getOffsetsList()[0].getX(), targetTile->getCenter().getY() + targetTile->getOffsetsList()[0].getY() + 70);
    if (network->getGui()->isDebugging())
        Parser::showArgs(args);
}

void Zappy::Parser::managePPO(std::vector<std::string> args, [[maybe_unused]] Zappy::Network *network)
{
    if (args.size() != 5) {
        if (network->getGui()->isDebugging())
            std::cout << "[DEBUG] Wrong number of args, response failed." << std::endl;
        return;
    }
    if (!Parser::isIndex(args[1])) {
        if (network->getGui()->isDebugging())
            std::cout << "[DEBUG] Index must be a # followed by a positive number." << std::endl;
        return;
    }
    for (size_t i = 2; i < args.size(); i++) {
        if (!Parser::isNum(args[i])) {
        if (network->getGui()->isDebugging())
                std::cout << "[DEBUG] Args must be positive numbers." << std::endl;
            return;
        }
    }
    std::shared_ptr<Trantorian> targetTrantorian = network->getGui()->getMap()->getTrantorianByID(std::stoi(args[1].substr(1)));
    if (!targetTrantorian)
        return;
    sf::Vector2i pos = {std::stoi(args[2]), std::stoi(args[3])};
    targetTrantorian->setTilePos(pos);
    targetTrantorian->getSprite()->getSprite().setPosition(network->getGui()->getMap()->getTiles()[pos.y][pos.x]->getCenter().getX(), network->getGui()->getMap()->getTiles()[pos.y][pos.x]->getCenter().getY());
    targetTrantorian->setDirection(std::stoi(args[4]));
    if (network->getGui()->isDebugging())
        Parser::showArgs(args);
}

void Zappy::Parser::managePLV(std::vector<std::string> args, [[maybe_unused]] Zappy::Network *network)
{
    if (args.size() != 3) {
        if (network->getGui()->isDebugging())
            std::cout << "[DEBUG] Wrong number of args, response failed." << std::endl;
        return;
    }
    if (!Parser::isIndex(args[1])) {
        if (network->getGui()->isDebugging())
            std::cout << "[DEBUG] Index must be a # followed by a positive number." << std::endl;
        return;
    }
    if (!Parser::isNum(args[2])) {
        std::cout << "Level must be a positive number." << std::endl;
        return;
    }
    std::shared_ptr<Trantorian> targetTrantorian = network->getGui()->getMap()->getTrantorianByID(std::stoi(args[1].substr(1)));
    if (!targetTrantorian)
        return;
    targetTrantorian->setLevel(std::stoi(args[2]));
    if (network->getGui()->isDebugging())
        Parser::showArgs(args);
}

void Zappy::Parser::managePIN(std::vector<std::string> args, [[maybe_unused]] Zappy::Network *network)
{
    if (args.size() != 11) {
        if (network->getGui()->isDebugging())
            std::cout << "[DEBUG] Wrong number of args, response failed." << std::endl;
        return;
    }
    if (!Parser::isIndex(args[1])) {
        if (network->getGui()->isDebugging())
            std::cout << "[DEBUG] Index must be a # followed by a positive number." << std::endl;
        return;
    }
    for (size_t i = 2; i < args.size(); i++) {
        if (!Parser::isNum(args[i])) {
        if (network->getGui()->isDebugging())
                std::cout << "[DEBUG] Args must be positive numbers." << std::endl;
            return;
        }
    }
    std::shared_ptr<Trantorian> targetTrantorian = network->getGui()->getMap()->getTrantorianByID(std::stoi(args[1].substr(1)));
    if (!targetTrantorian)
        return;
    for (size_t i = 4; i < args.size(); i++)
        targetTrantorian->getInventory()->setNItem(static_cast<Item>(i - 3), std::stoi(args[i]));
    if (network->getGui()->isDebugging())
        Parser::showArgs(args);
}

void Zappy::Parser::manageSGT(std::vector<std::string> args, [[maybe_unused]] Zappy::Network *network)
{
    if (args.size() != 2) {
        if (network->getGui()->isDebugging())
            std::cout << "[DEBUG] Wrong number of args, response failed." << std::endl;
        return;
    }
    if (!Parser::isNum(args[1])) {
        if (network->getGui()->isDebugging())
            std::cout << "[DEBUG] Args must be positive numbers." << std::endl;
        return;
    }
    network->getGui()->setTimeUnit(std::stoi(args[1]));
    if (network->getGui()->isDebugging())
        Parser::showArgs(args);
}

void Zappy::Parser::manageSST(std::vector<std::string> args, [[maybe_unused]] Zappy::Network *network)
{
    if (args.size() != 2) {
        if (network->getGui()->isDebugging())
            std::cout << "[DEBUG] Wrong number of args, response failed." << std::endl;
        return;
    }
    if (!Parser::isNum(args[1])) {
        if (network->getGui()->isDebugging())
            std::cout << "[DEBUG] Args must be positive numbers." << std::endl;
        return;
    }
    network->getGui()->setTimeUnit(std::stoi(args[1]));
    if (network->getGui()->isDebugging())
        Parser::showArgs(args);
}

void Zappy::Parser::managePNW(std::vector<std::string> args, [[maybe_unused]] Zappy::Network *network)
{
    if (args.size() != 7) {
        if (network->getGui()->isDebugging())
            std::cout << "[DEBUG] Wrong number of args, response failed." << std::endl;
        return;
    }
    if (!Parser::isIndex(args[1])) {
        if (network->getGui()->isDebugging())
            std::cout << "[DEBUG] Index must be a # followed by a positive number." << std::endl;
        return;
    }
    for (size_t i = 2; i < args.size() - 1; i++) {
        if (!Parser::isNum(args[i])) {
        if (network->getGui()->isDebugging())
                std::cout << "[DEBUG] Args must be positive numbers." << std::endl;
            return;
        }
    }
    std::shared_ptr<Trantorian> newTrantorian = std::make_shared<Trantorian>();
    sf::Vector2i pos = {std::stoi(args[2]), std::stoi(args[3])};
    newTrantorian->setId(std::stoi(args[1].substr(1)));
    newTrantorian->setTilePos(pos);
    newTrantorian->setDirection(std::stoi(args[4]));
    newTrantorian->setLevel(std::stoi(args[5]));
    newTrantorian->setTeamName(args[6]);
    newTrantorian->getSprite()->getSprite().setPosition(network->getGui()->getMap()->getTiles()[pos.y][pos.x]->getCenter().getX(), network->getGui()->getMap()->getTiles()[pos.y][pos.x]->getCenter().getY());
    network->getGui()->getMap()->addTrantorian(newTrantorian);
    if (network->getGui()->isDebugging())
        Parser::showArgs(args);
}

void Zappy::Parser::managePEX(std::vector<std::string> args, [[maybe_unused]] Zappy::Network *network)
{
    if (args.size() != 2) {
        if (network->getGui()->isDebugging())
            std::cout << "[DEBUG] Wrong number of args, response failed." << std::endl;
        return;
    }
    if (!Parser::isIndex(args[1])) {
        if (network->getGui()->isDebugging())
            std::cout << "[DEBUG] Index must be a # followed by a positive number." << std::endl;
        return;
    }
    std::shared_ptr<Trantorian> targetTrantorian = network->getGui()->getMap()->getTrantorianByID(std::stoi(args[1].substr(1)));
    if (!targetTrantorian)
        return;
    targetTrantorian->setState("Expulsed");
    if (network->getGui()->isDebugging())
        Parser::showArgs(args);
}

void Zappy::Parser::managePBC(std::vector<std::string> args, [[maybe_unused]] Zappy::Network *network)
{
    if (args.size() != 3) {
        if (network->getGui()->isDebugging())
            std::cout << "[DEBUG] Wrong number of args, response failed." << std::endl;
        return;
    }
    if (!Parser::isIndex(args[1])) {
        if (network->getGui()->isDebugging())
            std::cout << "[DEBUG] Index must be a # followed by a positive number." << std::endl;
        return;
    }
    network->getGui()->getBroadCastTab()->resetTimer();
    network->getGui()->getBroadCastTab()->pushToMessages(args[1] + ": " + args[2]);
}

void Zappy::Parser::managePIC(std::vector<std::string> args, [[maybe_unused]] Zappy::Network *network)
{
    if (args.size() < 5) {
        if (network->getGui()->isDebugging())
            std::cout << "[DEBUG] Wrong number of args, response failed." << std::endl;
        return;
    }
    for (size_t i = 1; i < 4; i++) {
        if (!Parser::isNum(args[i])) {
        if (network->getGui()->isDebugging())
                std::cout << "[DEBUG] Args must be positive numbers." << std::endl;
            return;
        }
    }
    for (size_t i = 4; i < args.size(); i++) {
        if (!Parser::isIndex(args[i])) {
        if (network->getGui()->isDebugging())
                std::cout << "[DEBUG] Index must be a # followed by a positive number." << std::endl;
            return;
        }
    }
    for (size_t i = 4; i < args.size(); i++) {
        std::shared_ptr<Trantorian> targetTrantorian = network->getGui()->getMap()->getTrantorianByID(std::stoi(args[i].substr(1)));
        if (!targetTrantorian)
            return;
        targetTrantorian->elevate();
        targetTrantorian->setState("Elevating");
    }
    if (network->getGui()->isDebugging())
        Parser::showArgs(args);
}

void Zappy::Parser::managePIE(std::vector<std::string> args, [[maybe_unused]] Zappy::Network *network)
{
    if (args.size() < 4) {
        if (network->getGui()->isDebugging())
            std::cout << "[DEBUG] Wrong number of args, response failed." << std::endl;
        return;
    }
    if (!Parser::isNum(args[1]) || !Parser::isNum(args[2])) {
        if (network->getGui()->isDebugging())
            std::cout << "[DEBUG] Args must be positive numbers." << std::endl;
        return;
    }
    sf::Vector2f pos;
    for (auto trantorian : network->getGui()->getMap()->getAllTrantorians()) {
        if (!trantorian.second)
            continue;
        if (trantorian.second->getTilePos().x == std::stoi(args[1]) && trantorian.second->getTilePos().y == std::stoi(args[2])) {
            trantorian.second->idle();
            trantorian.second->setState("Idling");
            network->askPlayerLevel({std::to_string(trantorian.second->getID())});
            pos = trantorian.second->getSprite()->getSprite().getPosition();
        }
    }
    pos.y -= 20;
    pos.x += 20;
    if (args[3] == "T") {
        std::shared_ptr<OneShotAnimationPlayer> animation = std::make_shared<OneShotAnimationPlayer>(10, sf::Vector2f(0.5, 0.5), sf::Vector2f(256, 256), sf::Vector2f(2560, 256), pos, "assets/elevation_sucess.png");
        network->getGui()->addToAnimationTab(animation);
    } else {
        std::shared_ptr<OneShotAnimationPlayer> animation = std::make_shared<OneShotAnimationPlayer>(4, sf::Vector2f(0.5, 0.5), sf::Vector2f(256, 256), sf::Vector2f(1024, 256), pos, "assets/elevation_fail.png");
        network->getGui()->addToAnimationTab(animation);
    }
    if (network->getGui()->isDebugging())
        Parser::showArgs(args);
}

void Zappy::Parser::managePFK(std::vector<std::string> args, [[maybe_unused]] Zappy::Network *network)
{
    if (args.size() != 2) {
        if (network->getGui()->isDebugging())
            std::cout << "[DEBUG] Wrong number of args, response failed." << std::endl;
        return;
    }
    if (!Parser::isIndex(args[1])) {
        if (network->getGui()->isDebugging())
            std::cout << "[DEBUG] Index must be a # followed by a positive number." << std::endl;
        return;
    }
    std::shared_ptr<Trantorian> targetTrantorian = network->getGui()->getMap()->getTrantorianByID(std::stoi(args[1].substr(1)));
    if (!targetTrantorian)
        return;
    targetTrantorian->setState("Forking");
    if (network->getGui()->isDebugging())
        Parser::showArgs(args);
}

void Zappy::Parser::managePDR(std::vector<std::string> args, [[maybe_unused]] Zappy::Network *network)
{
    if (args.size() != 3) {
        if (network->getGui()->isDebugging())
            std::cout << "[DEBUG] Wrong number of args, response failed." << std::endl;
        return;
    }
    if (!Parser::isIndex(args[1])) {
        if (network->getGui()->isDebugging())
            std::cout << "[DEBUG] Index must be a # followed by a positive number." << std::endl;
        return;
    }
    std::shared_ptr<Trantorian> targetTrantorian = network->getGui()->getMap()->getTrantorianByID(std::stoi(args[1].substr(1)));
    if (!targetTrantorian)
        return;
    targetTrantorian->setState("Dropping item");
    if (network->getGui()->isDebugging())
        Parser::showArgs(args);
}

void Zappy::Parser::managePGT(std::vector<std::string> args, [[maybe_unused]] Zappy::Network *network)
{
    if (args.size() != 3) {
        if (network->getGui()->isDebugging())
            std::cout << "[DEBUG] Wrong number of args, response failed." << std::endl;
        return;
    }
    if (!Parser::isIndex(args[1])) {
        if (network->getGui()->isDebugging())
            std::cout << "[DEBUG] Index must be a # followed by a positive number." << std::endl;
        return;
    }
    std::shared_ptr<Trantorian> targetTrantorian = network->getGui()->getMap()->getTrantorianByID(std::stoi(args[1].substr(1)));
    if (!targetTrantorian)
        return;
    if (args[2] == "food") {
        std::shared_ptr<OneShotAnimationPlayer> animation = std::make_shared<OneShotAnimationPlayer>(10, sf::Vector2f(0.5, 0.5), sf::Vector2f(256, 256), sf::Vector2f(1536, 256), targetTrantorian->getSprite()->getSprite().getPosition(), "assets/food_sheet.png");
        network->getGui()->addToAnimationTab(animation);
    }
    targetTrantorian->setState("Getting item");
    if (network->getGui()->isDebugging())
        Parser::showArgs(args);
}

void Zappy::Parser::managePDI(std::vector<std::string> args, [[maybe_unused]] Zappy::Network *network)
{
    if (args.size() != 2) {
        if (network->getGui()->isDebugging())
            std::cout << "[DEBUG] Wrong number of args, response failed." << std::endl;
        return;
    }
    if (!Parser::isIndex(args[1])) {
        if (network->getGui()->isDebugging())
            std::cout << "[DEBUG] Index must be a # followed by a positive number." << std::endl;
        return;
    }
    std::shared_ptr<Trantorian> targetTrantorian = network->getGui()->getMap()->getTrantorianByID(std::stoi(args[1].substr(1)));
    if (!targetTrantorian)
        return;
    targetTrantorian->kill();
    targetTrantorian->setState("Dead");
    if (network->getGui()->isDebugging())
        Parser::showArgs(args);
}

void Zappy::Parser::manageENW(std::vector<std::string> args, [[maybe_unused]] Zappy::Network *network)
{
    if (args.size() != 5) {
        if (network->getGui()->isDebugging())
            std::cout << "[DEBUG] Wrong number of args, response failed." << std::endl;
        return;
    }
    if (!Parser::isIndex(args[1]) || !Parser::isIndex(args[2])) {
        if (network->getGui()->isDebugging())
            std::cout << "[DEBUG] Index must be a # followed by a positive number." << std::endl;
        return;
    }
    std::shared_ptr<Trantorian> targetTrantorian = network->getGui()->getMap()->getTrantorianByID(std::stoi(args[2].substr(1)));
    if (!targetTrantorian)
        return;
    sf::Vector2i pos = {std::stoi(args[3]), std::stoi(args[4])};
    std::shared_ptr<Tile> targetTile = network->getGui()->getMap()->getTiles()[pos.y][pos.x];
    std::shared_ptr<Egg> newEgg = std::make_shared<Egg>(std::stoi(args[1].substr(1)), pos, targetTrantorian->getTeamName());
    newEgg->getDrawable()->getSprite().setPosition(targetTile->getCenter().getX() + targetTile->getOffsetsList()[0].getX(), targetTile->getCenter().getY() + targetTile->getOffsetsList()[0].getY() + 70);
    network->getGui()->getMap()->addEgg(newEgg);
    if (network->getGui()->isDebugging())
        Parser::showArgs(args);
}

void Zappy::Parser::manageEBO(std::vector<std::string> args, [[maybe_unused]] Zappy::Network *network)
{
    if (args.size() != 2) {
        if (network->getGui()->isDebugging())
            std::cout << "[DEBUG] Wrong number of args, response failed." << std::endl;
        return;
    }
    if (!Parser::isIndex(args[1])) {
        if (network->getGui()->isDebugging())
            std::cout << "[DEBUG] Index must be a # followed by a positive number." << std::endl;
        return;
    }
    std::shared_ptr<Egg> targetEgg = network->getGui()->getMap()->getEggById(std::stoi(args[1].substr(1)));
    if (!targetEgg)
        return;
    network->getGui()->getMap()->removeEggById(targetEgg->getId());
    if (network->getGui()->isDebugging())
        Parser::showArgs(args);
}

void Zappy::Parser::manageEDI(std::vector<std::string> args, [[maybe_unused]] Zappy::Network *network)
{
    if (args.size() != 2) {
        if (network->getGui()->isDebugging())
            std::cout << "[DEBUG] Wrong number of args, response failed." << std::endl;
        return;
    }
    if (!Parser::isIndex(args[1])) {
        if (network->getGui()->isDebugging())
            std::cout << "[DEBUG] Index must be a # followed by a positive number." << std::endl;
        return;
    }
    std::shared_ptr<Egg> targetEgg = network->getGui()->getMap()->getEggById(std::stoi(args[1].substr(1)));
    if (!targetEgg)
        return;
    network->getGui()->getMap()->removeEggById(targetEgg->getId());
    if (network->getGui()->isDebugging())
        Parser::showArgs(args);
}

void Zappy::Parser::manageSEG(std::vector<std::string> args, [[maybe_unused]] Zappy::Network *network)
{
    if (args.size() != 2) {
        if (network->getGui()->isDebugging())
            std::cout << "[DEBUG] Wrong number of args, response failed." << std::endl;
        return;
    }
    network->getGui()->setLastTeamAlive(args[1]);
    network->getGui()->endGame();
    network->shutDown();
    if (network->getGui()->isDebugging())
        Parser::showArgs(args);
}

void Zappy::Parser::manageSMG(std::vector<std::string> args, [[maybe_unused]] Zappy::Network *network)
{
    if (args.size() != 2) {
        if (network->getGui()->isDebugging())
            std::cout << "[DEBUG] Wrong number of args, response failed." << std::endl;
        return;
    }
    if (network->getGui()->isDebugging())
        Parser::showArgs(args);
}

void Zappy::Parser::manageSUC(std::vector<std::string> args, [[maybe_unused]] Zappy::Network *network)
{
    if (network->getGui()->isDebugging())
        Parser::showArgs(args);
}

void Zappy::Parser::manageSBP(std::vector<std::string> args, [[maybe_unused]] Zappy::Network *network)
{
    if (network->getGui()->isDebugging())
        Parser::showArgs(args);
}
