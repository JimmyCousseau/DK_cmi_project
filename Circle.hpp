#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Element.hpp"

class Circle : public Element
{
public:
    Circle(float x, float y, int radius, std::vector<sf::Image> &images, float rotation = 0, bool hasGravity = false, float velocityOnX = 0, float velocityOnY = 0, bool collide = true);
    Circle(float x, float y, int radius, float rotation = 0, bool hasGravity = false, float velocityOnX = 0, float velocityOnY = 0, bool collide = true, sf::Color color = sf::Color::White);
    ~Circle();

    void draw(sf::RenderWindow & window) override;

    // return a pointer to a copy of this element
    Element* clone() const override;

    int get_radius() const;
    Vector2D get_center() const override;
    Vector2D get_futhest_point(const Vector2D &direction) const override;

protected:
    int m_radius;
};
