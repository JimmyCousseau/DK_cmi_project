#include "Weapon.hpp"

Weapon::Weapon(float x, float y, int width, int height, const std::vector<sf::Image> &images, Player *owner) : 
Rectangle(x, y, width, height, images, NO, 0, false, 0, 0, true), m_owner(owner)
{
    set_physically_collide(false);

    if (owner != nullptr) { m_isOwned = true; }
}

Weapon::~Weapon ()
{

}

void Weapon::set_owner(Player *owner) { m_owner = owner; }