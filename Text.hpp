#pragma once

#include "Element.hpp"

class Text : public Element {
public:
    Text(float x, float y, std::string text, sf::Font font, int size = 5, float temporary = -1, float rotation = 0, bool collide = false, sf::Color color = sf::Color::White);
    ~Text();

    void draw(sf::RenderWindow & window) override;
    void update(float dt) override;

    // return a pointer to a copy of this element
    Element* clone() const override;

    // Setters
    void set_text(std::string text); // Allow to modify the text during the game

    // Getters
    Vector2D get_center() const override;
    Vector2D get_futhest_point(const Vector2D &direction) const override;

private:
    bool m_isTemporary = false;
    float m_temporary;
    float m_clock = 0;
    std::string m_text;
    int m_size; // Size of the text
    sf::Font m_font;
};
