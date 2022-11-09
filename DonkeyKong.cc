#include "DonkeyKong.hpp"

DonkeyKong::DonkeyKong(float x, float y, int width, int height, const std::vector<sf::Image> &images, const Element* elementToCopy, std::list<Element*> &movingElements, float frequency) : 
Rectangle(x, y, width, height, images, NO, 0, true, 0, 0, false), m_frequency(frequency), m_movingElements(movingElements)
{
    // If DonkeyKong doesn't have any image, throw an exception
    assert(m_images.size() > 0);

    m_ElementType = DONKEY_KONG;
    m_elementToCopy = elementToCopy->clone();
    m_texture.loadFromImage(m_images[0]);
    
    // placing the position of the element in his hands
    m_elementToCopy->set_x(m_position.x + width);
    m_elementToCopy->set_y(m_position.y + height/2);

    // adapting the animation interval to the frequency, 
    m_animationInterval = m_frequency/m_images.size();
}

DonkeyKong::~DonkeyKong()
{
    delete m_elementToCopy;
}

void DonkeyKong::draw(sf::RenderWindow &window) {
    auto size = m_texture.getSize(); // Get the size of the texture

    sf::RectangleShape dk(sf::Vector2f(get_width(), get_height()));
    dk.setPosition(m_position.x, m_position.y);
    dk.rotate(m_rotation);
    dk.setTexture(&m_texture);

    if (m_facingDirection == FACING_RIGHT)
    {
        dk.setTextureRect(sf::IntRect(size.x, 0, -size.x, size.y));
    }
    window.draw(dk);
}

void DonkeyKong::update(float dt)
{
    this->update_animation(dt);
}

void DonkeyKong::update_animation(float dt)
{
    m_animationClock += dt;

    if (m_animationClock >= m_animationInterval)
    {
        // reset the clock
        m_animationClock -= m_animationInterval;
        switch (m_animation)
        {
        case 0:
            m_texture.loadFromImage(m_images[0]);
            ++m_animation;
            m_facingDirection = FACING_FRONT;
            break;
        case 1:
            m_texture.loadFromImage(m_images[1]);
            ++m_animation;
            m_facingDirection = FACING_FRONT;
            break;
        case 2:
            m_texture.loadFromImage(m_images[2]);
            ++m_animation;
            m_facingDirection = FACING_FRONT;
            break;
        case 3:
            m_texture.loadFromImage(m_images[3]);
            ++m_animation;
            m_facingDirection = FACING_LEFT;
            break;
        case 4:
            m_texture.loadFromImage(m_images[3]);
            ++m_animation;
            m_facingDirection = FACING_RIGHT;
            break;
        case 5:
            m_texture.loadFromImage(m_images[0]);
            ++m_animation;
            m_facingDirection = FACING_FRONT;
            break;
        case 6:
            m_texture.loadFromImage(m_images[4]);
            ++m_animation;
            m_facingDirection = FACING_LEFT;
            break;
        case 7:
            m_texture.loadFromImage(m_images[4]);
            m_animation = 0;
            m_facingDirection = FACING_RIGHT;
            this->spawn_element();
            break;
        default:
            std::cout << "Error: Unknown animation" << std::endl;
        }
    }
}

Element* DonkeyKong::clone() const
{
    return new DonkeyKong(*this);
}

void DonkeyKong::spawn_element()
{
    Element *copy = m_elementToCopy->clone();
    m_movingElements.push_back(copy);
}