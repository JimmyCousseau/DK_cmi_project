#include "Text.hpp"

#define VELOCITY_ON_Y 10

Text::Text(float x, float y, std::string text, sf::Font font, int size, float temporary, float rotation, bool collide, sf::Color color)
    : Element(x, y, 0, false, 0, 0, collide, color), m_temporary(temporary), m_text(text), m_size(size), m_font(font)
{
    if (temporary == -1)
    {
        m_isTemporary = false;
    }
    else
    {
        m_isTemporary = true;
    }
}

Text::~Text() {}

void Text::update(float dt) {
    if (m_isTemporary)
    {
        m_clock += dt;

        // if the text stayed long enought mark it has should be deleted
        if (m_clock >= m_temporary) { this->set_should_be_deleted(true); }
    }

    this->update_position(dt);
}

// Draw text into the window
void Text::draw(sf::RenderWindow &window)
{
    sf::Text text;
    text.setString(m_text);
    text.setFont(m_font);
    text.setCharacterSize(m_size);
    text.setFillColor(m_color);
    text.setPosition(m_position.x, m_position.y);
    window.draw(text);
}

Element* Text::clone() const
{
    return new Text(*this);
}

// Setters
void Text::set_text(std::string text) { m_text = text; }

// There is no proprer implementation  yet
Vector2D Text::get_center() const { return Vector2D(0, 0); }
Vector2D Text::get_futhest_point(const Vector2D &direction) const { return Vector2D(0, 0); }
