#include "Element.hpp"

Element::Element(float x, float y, const std::vector<sf::Image> &images, Repeated repeated, float rotation, bool hasGravity, float velocityOnX, float velocityOnY, bool collide): 
m_position(x, y), m_previousPosition(x, y), m_velocity(velocityOnX, velocityOnY), m_collide(collide), m_physicallyCollide(collide), m_hasGravity(hasGravity), 
m_rotation(rotation), m_hasTexture(true), m_repeated(repeated), m_images(images), m_resourcesPointer(nullptr)
{
    m_texture.loadFromImage(images[0]);
}

Element::Element(float x, float y, float rotation, bool hasGravity, float velocityOnX, float velocityOnY, bool collide, sf::Color color): 
m_position(x, y), m_previousPosition(x, y),  m_velocity(velocityOnX, velocityOnY), m_collide(collide), m_physicallyCollide(collide), m_hasGravity(hasGravity),
m_rotation(rotation), m_hasColor(true), m_color(color), m_resourcesPointer(nullptr)
{

}

Element::~Element()
{
    
}

void Element::update(float dt)
{
    this->update_animation(dt);
    this->update_position(dt);
}

void Element::collision_callback(Element* element) 
{

}

void Element::update_position(float timeElapsed)
{
    m_previousPosition = m_position;
    m_position.x += m_velocity.x * timeElapsed;
    m_position.y += m_velocity.y * timeElapsed;
}

void Element::move_in_a_direction(const Vector2D &direction, float distance)
{
    m_previousPosition = m_position;
    m_position.x += direction.x * distance;
    m_position.y += direction.y * distance;
}

void Element::update_animation(float dt)
{
    m_animationClock += dt;

    // if enougth time passed since the last frame
    if (m_hasTexture)
    {
        if (m_animationClock >= m_animationInterval)
        {
            // reset the clock
            m_animationClock -= m_animationInterval;
            
            // change the frame to the next one in the loop
            if (m_animation < m_images.size() - 1) 
            {
                ++m_animation;
            }
            else
            {
                m_animation = 0;
            }
            
            // set the new frame
            m_texture.loadFromImage(m_images[m_animation]);
        }
    }
}


// Setters
void Element::set_x(float x) 
{ 
    m_previousPosition.x = m_position.x;
    m_position.x = x; 
}
void Element::set_y(float y)
{ 
    m_previousPosition.y = m_position.y;
    m_position.y = y; 
}
void Element::set_position(const Vector2D &position) 
{
    m_previousPosition = m_position;
    this->set_x(position.x);
    this->set_y(position.y);
}
void Element::set_previous_position(const Vector2D &previousPosition) { m_previousPosition = previousPosition; }
void Element::set_collide(bool collide) { m_collide = collide; }
void Element::set_has_gravity(bool hasGravity) { m_hasGravity = hasGravity; }
void Element::set_velocity_on_x(float velocityOnX) { m_velocity.x = velocityOnX; }
void Element::set_velocity_on_y(float velocityOnY) { m_velocity.y = velocityOnY; }
void Element::set_velocity(const Vector2D &velocity) { m_velocity = velocity; }
void Element::set_physically_collide(bool physicallyCollide) { m_physicallyCollide = physicallyCollide; }
void Element::set_mass(float mass)
{
    if (mass == 0) { m_invMass = 0; }
    else { m_invMass = 1/mass; }
    m_mass = mass;
}
void Element::set_bounciness(float bounciness) 
{ 
    assert(bounciness >= 0);
    m_bounciness = bounciness; 
}
void Element::set_color(sf::Color color) { m_color = color; }
void Element::set_texture(sf::Image image) { m_texture.loadFromImage(image); }
void Element::set_resources_pointer(Resources *resources) { m_resourcesPointer = resources; }
void Element::set_rotation(float rotation) { m_rotation = rotation; }
void Element::set_element_type(ElementType elementType) { m_ElementType = elementType; }
void Element::set_should_be_deleted(bool shouldBeDeleted) { m_shouldBeDeleted = shouldBeDeleted; }

// Getters
float Element::get_x() const { return m_position.x; }
float Element::get_y() const { return m_position.y; }
Vector2D Element::get_position() const { return m_position; }
bool Element::get_has_gravity() const { return m_hasGravity; }
float Element::get_velocity_on_x() const { return m_velocity.x; }
float Element::get_velocity_on_y() const {return m_velocity.y; }
Vector2D Element::get_velocity() const {return m_velocity; }
bool Element::get_physically_collide() const {return m_physicallyCollide; }
float Element::get_mass() const { return m_mass; }
float Element::get_inv_mass() const { return m_invMass; }
float Element::get_bounciness() const { return m_bounciness; }
sf::Color Element::get_color() const { return m_color; }
Vector2D Element::get_previous_position() const { return m_previousPosition; }
bool Element::get_does_collide() const { return m_collide; }
sf::Texture Element::get_texture() const { return m_texture; }
float Element::get_rotation() const { return m_rotation; }
bool Element::get_has_texture() const { return m_hasTexture; }
bool Element::get_has_color() const { return m_hasColor; }
ElementType Element::get_element_type() const { return m_ElementType; }
bool Element::get_should_be_deleted() const { return m_shouldBeDeleted; }
