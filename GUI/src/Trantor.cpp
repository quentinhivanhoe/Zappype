/*
** EPITECH PROJECT, 2025
** B-YEP-400-RUN-4-1-zappy-loic.rabearivelo
** File description:
** Trantorian
*/
#include "../includes/Trantor.hpp"

Zappy::Trantorian::Trantorian(/* args */)
{
    this->_inventory = std::make_shared<Tile>();
    this->_sprite = std::make_shared<Drawable>("assets/trantorian_sprite_sheet.png", 0.8);
    this->getSprite()->getSprite().setOrigin(128, 128);
    this->_textureRect = sf::IntRect(0, 256, 256, 256);
    this->getSprite()->getSprite().setTextureRect(this->_textureRect);
}
    
Zappy::Trantorian::~Trantorian()
{
}
   
void Zappy::Trantorian::manageDeadSprite()
{
    if (this->_clock.getElapsedTime().asMicroseconds() < 1000000 / 9)
        return;
    this->_clock.restart();
    this->_textureRect.left += 256;
    if (this->_textureRect.left >= this->_maxSizeDead)
        this->_textureRect.left = this->_maxSizeDead;
    this->getSprite()->getSprite().setTextureRect(this->_textureRect);
}

void Zappy::Trantorian::manageElevatingSprite()
{
    if (this->_clock.getElapsedTime().asMicroseconds() < 1000000 / 3)
        return;
    this->_clock.restart();
    this->_textureRect.left += 256;
    if (this->_textureRect.left >= this->_maxSizeElevating)
        this->_textureRect.left = 0;
    this->getSprite()->getSprite().setTextureRect(this->_textureRect);
}

void Zappy::Trantorian::manageIdleSprite()
{
}

void Zappy::Trantorian::updateTrantorSprite()
{
    if (this->_isDead)
        this->manageDeadSprite();
    if (this->_isElevating)
        this->manageElevatingSprite();
    if (this->_isIdling)
        this->manageIdleSprite();
}

void Zappy::Trantorian::kill()
{
    this->_isIdling = false;
    this->_isElevating = false;
    this->_isDead = true;
    this->_textureRect.top = 512;
    this->_textureRect.left = 0;
    this->getSprite()->getSprite().setTextureRect(this->_textureRect);
}

void Zappy::Trantorian::idle()
{
    this->_isIdling = true;
    this->_isElevating = false;
    this->_isDead = false;
    this->_textureRect.top = 256;
    this->_textureRect.left = 0;
    this->getSprite()->getSprite().setTextureRect(this->_textureRect);
}

void Zappy::Trantorian::elevate()
{
    this->_isIdling = false;
    this->_isElevating = true;
    this->_isDead = false;
    this->_textureRect.top = 0;
    this->_textureRect.left = 0;
    this->getSprite()->getSprite().setTextureRect(this->_textureRect);
}
