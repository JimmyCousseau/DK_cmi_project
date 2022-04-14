#pragma once

#include "Element.hpp"

class Text : public Element {
public:
    Text(std::string text, float x, float y, int size, sf::Font font, sf::Color color = sf::Color::White);
    ~Text();

    void draw(sf::RenderWindow & window);

    // Setters
    void set_text(); // Allow to modify the text during the game

    // Getters
    Vector2D get_center() const;
    Vector2D get_futhest_point(const Vector2D &direction) const;

private:
    std::string m_text; 
    int m_size; // Size of the text
    sf::Font m_font;
};
