#pragma once

#include <vector>
#include <math.h>
#include <SFML/Graphics.hpp>

#include "Element.hpp"

class Rectangle : public Element 
{
public:
    Rectangle(float x, float y, int width, int height, const std::vector<sf::Image> &images, Repeated repeat = NO, float rotation = 0, bool hasGravity = false, float velocityOnX = 0, float velocityOnY = 0, bool collide = true);
    Rectangle(float x, float y, int width, int height, float rotation = 0, bool hasGravity = false, float velocityOnX = 0, float velocityOnY = 0, bool collide = true, sf::Color color = sf::Color::White);
    ~Rectangle();
    
    void draw(sf::RenderWindow &window) override;
    Vector2D get_center() const override;
    Vector2D get_futhest_point(const Vector2D &direction) const override;
    std::vector<Vector2D> get_vertices_coord() const;

    // return a pointer to a copy of this element
    Element* clone() const override;

    // Getters
    int get_height() const;
    int get_width() const;
    float get_clocks() const;

    // Setters
    void set_repeated(Repeated repeat);
    void set_width(int width);
    void set_height(int height);

private:
    int m_width;
    int m_height;
};
