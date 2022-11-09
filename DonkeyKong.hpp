#pragma once

#include <list>
#include <assert.h>

#include "Rectangle.hpp"
#include "FallingBarrel.hpp"

class DonkeyKong : public Rectangle
{
public:
    DonkeyKong(float x, float y, int width, int height, const std::vector<sf::Image> &images, const Element* elementToCopy, std::list<Element*> &movingElements, float frequency = 20);
    ~DonkeyKong();

    void draw(sf::RenderWindow & window) override;
    void update(float dt) override;
    void update_animation(float dt) override;

    // return a pointer to a copy of this element
    Element* clone() const override;

    void spawn_element();

private:
    float m_frequency; // the duration between every spawn
    std::list<Element*> &m_movingElements;
    Element* m_elementToCopy;
    FacingDirection m_facingDirection = FACING_FRONT;
};
