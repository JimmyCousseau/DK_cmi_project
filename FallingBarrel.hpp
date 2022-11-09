#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Circle.hpp"

class FallingBarrel : public Circle
{
public:
    FallingBarrel(float x, float y, int radius, std::vector<sf::Image> &images, float velocityOnX = 0, float velocityOnY = 0);
    ~FallingBarrel();

    void draw(sf::RenderWindow & window) override;
    void collision_callback(Element *element) override;

    void update(float dt) override;

    // return a pointer to a copy of this element
    Element* clone() const override;

    void set_is_already_jumped(bool isAlreadyJumped);

    bool get_is_already_jumped() const;

protected:
    void adjust_texture_rotation(float dt); // used to rotate the barrel texture as if he was really rolling
    float m_textureRotation; 
    bool m_isAlreadyJumped = false;
};
