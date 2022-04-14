#include "Text.hpp"

Text::Text(std::string text, float x, float y, int size, sf::Font font, sf::Color color)
    : Element(x, y, color), m_text(text), m_font(font), m_size
{
}

Text::~Text()
{
}

// Draw text into the window
void Text::draw(sf::RenderWindow &window)
{
    sf::Text text;
    text.setString(m_text);
    text.setFont(m_font);
    text.setCharacterSize(m_size);
    text.setFillColor(m_color);
    text.setPosition(m_x, m_y);
    game.set_text_score(m_text);
    window.draw(text);
}

// Setters
void Text::set_text() {}


// Getters
Vector2D Rectangle::get_center() const {}
Vector2D Rectangle::get_futhest_point(const Vector2D &direction) const {}
