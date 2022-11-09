#include "FallingBarrel.hpp"
#define PI 3.14159265

FallingBarrel::FallingBarrel(float x, float y, int radius, std::vector<sf::Image> &images, float velocityOnX, float velocityOnY):
Circle(x, y, radius, images, 0, true, velocityOnX, velocityOnY, true), m_textureRotation(0)
{
    m_ElementType = FALLING_BARREL;
}

FallingBarrel::~FallingBarrel()
{

}

void FallingBarrel::draw(sf::RenderWindow &window)
{
    sf::CircleShape circle(m_radius);
    circle.setPosition(m_position.x, m_position.y);

    // create a transformation that will rotate the barrel texture accordingly to the value
    // of m_textureRotation
    Vector2D center = this->get_center();
    sf::Transform transform;
    transform.rotate(m_textureRotation, sf::Vector2f(center.x, center.y));
    circle.setTexture(&m_texture);
    window.draw(circle, transform);
}

void FallingBarrel::update(float dt)
{
    Element::update(dt);
    this->adjust_texture_rotation(dt);
}

void FallingBarrel::collision_callback(Element* element)
{
    switch (element->get_element_type())
    {
    case PLAYER:
        this->m_shouldBeDeleted = true;
        break;
    case BLUE_BARREL:
        this->m_shouldBeDeleted = true;
    default:
        break;
    }
}

void FallingBarrel::adjust_texture_rotation(float dt)
{
    // calculate the travel vector form the last position to the current one
    const Vector2D travel = m_position - m_previousPosition;

    // calculate the amont of rotation the barrel should rotate
    float rotation = Math::lenght(travel) / m_radius;
    rotation *= (180 / PI); // convert the rotation to degree

    // if the dot product is positive it mean the travel vector point to the right,
    // so we rotate the barrel clockwise, else we rotate counterclockwise
    if (Math::dot(travel, Vector2D(1, 0)) > 0)
    {
        m_textureRotation += rotation;
    }
    else
    {
        m_textureRotation -= rotation;
    }
}

Element* FallingBarrel::clone() const
{
    return new FallingBarrel(*this);
}

void FallingBarrel::set_is_already_jumped(bool isAlreadyJumped) { m_isAlreadyJumped = isAlreadyJumped; }

bool FallingBarrel::get_is_already_jumped() const { return m_isAlreadyJumped; }