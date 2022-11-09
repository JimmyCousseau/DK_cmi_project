#pragma once

#include <vector>
#include <math.h>
#include <SFML/Graphics.hpp>

#include "Rectangle.hpp"
#include "Player.hpp"
#include "Element.hpp"

class Player;

class Weapon : public Rectangle
{
public:
    Weapon(float x, float y, int width, int height, const std::vector<sf::Image> &images, Player *owner = nullptr);
    ~Weapon();

    void set_owner(Player *owner);

protected:
    float m_weaponClock = 0;
    Player *m_owner;
    bool m_isOwned = false;
    float m_timeLeft = 10;
};