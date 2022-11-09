#include "Circle.hpp"

Circle::Circle(float x, float y, int radius, std::vector<sf::Image> &images, float rotation, bool hasGravity, float velocityOnX, float velocityOnY, bool collide) : 
Element(x, y, images, NO, rotation, hasGravity, velocityOnX, velocityOnY, collide), m_radius(radius)
{
}

Circle::Circle(float x, float y, int radius, float rotation, bool hasGravity, float velocityOnX, float velocityOnY, bool collide, sf::Color color) : 
Element(x, y, rotation, hasGravity, velocityOnX, velocityOnY, collide, color), m_radius(radius)
{
}

Circle::~Circle()
{
}

void Circle::draw(sf::RenderWindow &window)
{
    sf::CircleShape circle(m_radius);
    circle.setPosition(m_position.x, m_position.y);
    circle.rotate(m_rotation);

    if (m_hasColor) { circle.setFillColor(m_color); }

    if (m_hasTexture)
    {
        m_texture.setRepeated(true);
        circle.setTexture(&m_texture);
    }
    
    window.draw(circle);
}

Element* Circle::clone() const
{
    return new Circle(*this);
}

Vector2D Circle::get_center() const
{
    const Vector2D center = {m_position.x + m_radius, m_position.y + m_radius};
    return center;
}

Vector2D Circle::get_futhest_point(const Vector2D &direction) const
{
    const Vector2D center = get_center();
    const Vector2D futhest = center + direction*m_radius; // the distance vector MUST be normalised
    return futhest;
}

int Circle::get_radius() const { return m_radius; }