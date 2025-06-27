/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** One shot animation player functions
*/

#include "../includes/OneShotAnimationPlayer.hpp"

Zappy::OneShotAnimationPlayer::OneShotAnimationPlayer(int framerate, sf::Vector2f scale, sf::Vector2f singleTileSize, sf::Vector2f fullSize, sf::Vector2f pos, const std::string& spritePath)
{
    this->_frameRate = framerate;
    this->_scale = scale;
    this->_singleTileSize = singleTileSize;
    this->_fullSize = fullSize;
    this->_path = spritePath;
    this->_pos = pos;
    this->_spriteSheet = std::make_shared<Drawable>(spritePath);
    this->_spriteSheet->getSprite().setScale(this->_scale);
    this->_innerRect = sf::IntRect(0, 0, this->_singleTileSize.x, this->_singleTileSize.y);
    this->_spriteSheet->getSprite().setTextureRect(this->_innerRect);
    this->_spriteSheet->getSprite().setPosition(pos);
    this->_spriteSheet->getSprite().setOrigin(sf::Vector2f(singleTileSize.x / 2.0, singleTileSize.y / 2.0));
    this->_innerClock.restart();
}

void Zappy::OneShotAnimationPlayer::update()
{
    if (this->_isFading)
        this->alphaValue -= 10;
    if (this->alphaValue < 0) {
        this->alphaValue = 0;
        this->_alive = false;
        this->_isFading = false;
    }
    if (!this->_alive)
        return;
    this->getDrawable()->getSprite().setColor(sf::Color(255, 255, 255, this->alphaValue));
    if (this->_isFading)
        return;
    if (this->_innerClock.getElapsedTime().asMicroseconds() < 1000000 / this->_frameRate)
        return;
    this->_innerClock.restart();
    this->_innerRect.left += this->_singleTileSize.x;
    if (this->_innerRect.left >= this->_fullSize.x) {
        this->_innerRect.left = 0;
        this->_innerRect.top += this->_singleTileSize.y;
    }
    if (this->_innerRect.top >= this->_fullSize.y) {
        this->_innerRect.left = this->_fullSize.x - this->_singleTileSize.x;
        this->_innerRect.top = this->_fullSize.y - this->_singleTileSize.y;
        this->_isFading = true;
    }
    if (this->_alive)
        this->_spriteSheet->getSprite().setTextureRect(this->_innerRect);
}
