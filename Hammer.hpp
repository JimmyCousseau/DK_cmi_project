#pragma once

#include "Player.hpp"
#include "Weapon.hpp"
#include "Text.hpp"
#include <list>
#include <string>

class Hammer : public Weapon
{
public:
    Hammer(float x, float y, int width, int height, const std::vector<sf::Image> &images, const Element *elementToCopy, std::list<Element*> &movingElements, Player *owner = nullptr);
    ~Hammer();

    void update(float dt) override;
    void update_animation(float dt) override;
    void collision_callback(Element *element) override;
    void draw(sf::RenderWindow &window) override;
    void spawn_text(std::string text);
    Element* clone() const override;

private:
    void collide_with_player(Element *element);
    void collide_with_barrel(Element *element);
    void update_hammer_relatively_to_owner();
    std::list<Element *> &m_movingElements;
    Element *m_elementToCopy;

};