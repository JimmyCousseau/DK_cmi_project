#include "Rectangle.hpp"

#define PI 3.14159265

Rectangle::Rectangle(float x, float y, int width, int height, const std::vector<sf::Image> &images, Repeated repeat, float rotation, bool hasGravity, float velocityOnX, float velocityOnY, bool collide) :
Element(x, y, images, repeat, rotation, hasGravity, velocityOnX, velocityOnY, collide), m_width(width), m_height(height)
{
}

Rectangle::Rectangle(float x, float y, int width, int height, float rotation, bool hasGravity, float velocityOnX, float velocityOnY, bool collide, sf::Color color) :
Element(x, y, rotation, hasGravity, velocityOnX, velocityOnY, collide, color), m_width(width), m_height(height)
{
}

Rectangle::~Rectangle()
{
}

void Rectangle::draw(sf::RenderWindow &window)
{
    sf::Vector2u size = m_texture.getSize(); // Get the size of the texture

    sf::RectangleShape rectangle(sf::Vector2f(m_width, m_height));
    rectangle.setPosition(m_position.x, m_position.y);
    rectangle.rotate(m_rotation);

    if (m_hasColor) { rectangle.setFillColor(m_color); }
    
    if (m_hasTexture)
    {
        m_texture.setRepeated(true);
        rectangle.setTexture(&m_texture);

        switch (m_repeated)
        {
            case VERTICALY:
                rectangle.setTextureRect(sf::IntRect(0, 0, size.x, size.y * m_height / m_width));
                break;
            case HORIZONTALY:
                rectangle.setTextureRect(sf::IntRect(0, 0, size.x * m_width / m_height, size.y));
                break;
            case BOTH:
                rectangle.setTextureRect(sf::IntRect(0, 0, size.x * m_width / m_height, size.y * m_height / m_width));
                break;
            default:
                break;
        }
    }

    window.draw(rectangle);
}

Vector2D Rectangle::get_center() const
{
    const float angleInRadiant = (m_rotation*PI)/180;
    const float cosAngle = cos(angleInRadiant);
    const float sinAngle = sin(angleInRadiant);
    const float halfWidth = m_width/2;
    const float halfHeight = m_height/2;

    const Vector2D center = {m_position.x + halfWidth*cosAngle - halfHeight*sinAngle, m_position.y + halfWidth*sinAngle + halfHeight*cosAngle};
    return center;
}

std::vector<Vector2D> Rectangle::get_vertices_coord() const
{
    const float angleInRadiant = (m_rotation*PI)/180;
    const float cosAngle = cos(angleInRadiant);
    const float sinAngle = sin(angleInRadiant);

    // calculate the coordinates of the 4 vertices by taking in account the rotation of the rectangle
    // using this formula : https://stackoverflow.com/questions/1469149/calculating-vertices-of-a-rotated-rectangle#answer-1469166
    std::vector<Vector2D> vertices;
    vertices.push_back(Vector2D(m_position.x, m_position.y)); // top left corner
    vertices.push_back(Vector2D(m_position.x + m_width*cosAngle, m_position.y + sinAngle*m_width)); // top right corner
    vertices.push_back(Vector2D(m_position.x + m_width*cosAngle - m_height*sinAngle, m_position.y + m_width*sinAngle + m_height*cosAngle)); // bottom right corner
    vertices.push_back(Vector2D(m_position.x - m_height*sinAngle, m_position.y + m_height*cosAngle)); // bottom left corner

    return vertices;
}

Vector2D Rectangle::get_futhest_point(const Vector2D &direction) const
{
    std::vector<Vector2D> vertices = Rectangle::get_vertices_coord();
    
    Vector2D futhest = vertices[0]; // initialize the futhest point with the coordinates of a random corner
    float bestScore = Math::dot(direction, futhest); // calculate the score of this point

    // search for a point with a superior score
    for (int i = 1; i < 4; ++i)
    {
        const float newScore = Math::dot(direction, vertices[i]);
        if (newScore > bestScore)
        {
            bestScore = newScore;
            futhest = vertices[i];
        }
    }

    return futhest;
}

Element* Rectangle::clone() const
{
    return new Rectangle(*this);
}

// Getters
int Rectangle::get_height() const { return m_height; }
int Rectangle::get_width() const { return m_width; }

void Rectangle::set_repeated(Repeated repeated) { m_repeated = repeated; };
void Rectangle::set_width(int width) { m_width = width; }
void Rectangle::set_height(int height) { m_height = height; }
