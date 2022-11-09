#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <assert.h>

#include "Math.hpp"
#include "Resources.hpp"

enum Repeated
{
    NO,
    VERTICALY,
    HORIZONTALY,
    BOTH
};

enum ElementType
{
    NONE,
    PLAYER,
    DONKEY_KONG,
    PEACH,
    LADDER,
    FALLING_BARREL,
    BLUE_BARREL,
    WEAPON
};

enum FacingDirection
{
    FACING_LEFT,
    FACING_RIGHT,
    FACING_FRONT
};

class Element
{
public:
    Element(float x, float y, const std::vector<sf::Image> &images, Repeated repeated, float rotation = 0, bool hasGravity = false, float velocityOnX = 0, float velocityOnY = 0, bool collide = true);
    Element(float x, float y, float rotation = 0, bool hasGravity = false, float velocityOnX = 0, float velocityOnY = 0, bool collide = true, sf::Color color = sf::Color::White);
    virtual ~Element();

    // Used when the Element has to move
    void update_position(float timeElapsed);
    void move_in_a_direction(const Vector2D &direction, float distance);

    // return a pointer to a copy of this element
    virtual Element* clone() const = 0;

    // Used to render the Element
    virtual void draw(sf::RenderWindow &window) = 0;
    virtual void update(float dt);
    virtual void collision_callback(Element *element);

    // Used to calculate colision between Elements
    virtual Vector2D get_center() const = 0;
    virtual Vector2D get_futhest_point(const Vector2D &direction) const = 0;

    void set_x(float x);
    void set_y(float y);
    void set_position(const Vector2D &position);
    void set_previous_position(const Vector2D &previousPosition);
    void set_collide(bool collide);
    void set_has_gravity(bool hasGravity);
    void set_velocity_on_x(float velocityOnX);
    void set_velocity_on_y(float velocityOnY);
    void set_velocity(const Vector2D &velocity);
    void set_physically_collide(bool physicallyCollide);
    void set_mass(float mass);
    void set_bounciness(float bounciness);
    void set_color(sf::Color color);
    void set_texture(sf::Image image);  
    void set_resources_pointer(Resources *resources);
    void set_rotation(float rotation);
    void set_element_type(ElementType elementType);
    void set_should_be_deleted(bool shouldBeDeleted);

    float get_x() const;
    float get_y() const;
    Vector2D get_position() const;
    Vector2D get_previous_position() const;
    bool get_has_gravity() const;
    float get_velocity_on_x() const;
    float get_velocity_on_y() const;
    Vector2D get_velocity() const;
    bool get_physically_collide() const;
    float get_mass() const;
    float get_inv_mass() const;
    float get_bounciness() const;
    sf::Color get_color() const;
    bool get_does_collide() const;
    sf::Texture get_texture() const;
    float get_rotation() const;
    std::vector<sf::Image>* get_images() const;
    bool get_has_texture() const;
    bool get_has_color() const;
    ElementType get_element_type() const;
    bool get_should_be_deleted() const;

protected :
    virtual void update_animation(float dt); // take in parameter the time since the last call

    Vector2D m_position;
    Vector2D m_previousPosition;
    Vector2D m_velocity;
    bool m_collide;
    bool m_physicallyCollide;
    bool m_hasGravity;
    float m_rotation;
    float m_mass = 1;
    float m_invMass = 1;
    float m_bounciness = 0; // the bounciness must remain positive, when set to 0 the restitution is null
    ElementType m_ElementType = NONE; // Store the type of the element used to resolve colision between specific objects (like barrels and players)

    bool m_hasColor = false;
    bool m_hasTexture = false;
    bool m_shouldBeDeleted = false;
    Repeated m_repeated = NO;
    int m_animation = 0; // store the index of the current element texture
    float m_animationClock = 0; // store the time elipsed since the last animation update
    float m_animationInterval = 0.3; // store the time that must pass between two animations steps
    sf::Color m_color;
    sf::Texture m_texture;
    std::vector<sf::Image> m_images;
    Resources *m_resourcesPointer; // Pointing to the loaded resources of the running game, usefull when the Element has more than one texture (animation)
};
