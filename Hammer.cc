#include "Hammer.hpp"

#define POINTS_PER_BARREL_DESTROYED 100

Hammer::Hammer(float x, float y, int width, int height, const std::vector<sf::Image> &images, const Element *elementToCopy, std::list<Element*> &movingElements, Player *owner) :
Weapon(x, y, width, height, images, owner), m_movingElements(movingElements)
{
    m_texture.loadFromImage(m_images[0]);
    m_animationInterval = 0.05;
    m_elementToCopy = elementToCopy->clone();
}

Hammer::~Hammer()
{
    delete m_elementToCopy;
}

void Hammer::draw(sf::RenderWindow &window) 
{
    
    auto size = get_texture().getSize(); // Get the size of the texture
    sf::Texture texture = get_texture();
    sf::RectangleShape weapon(sf::Vector2f(get_width(), get_height()));
    weapon.setPosition(get_x(), get_y());
    weapon.setTexture(&texture);

    if (m_isOwned)
    { 
        if (m_owner->get_facing_direction() == FACING_RIGHT)
        {
            weapon.setTextureRect(sf::IntRect(size.x, 0, -size.x, size.y));
        }
    }

    window.draw(weapon);
}

void Hammer::update(float dt)
{
    if (!m_isOwned) { return; }
    m_timeLeft -= dt;
    this->update_animation(dt);
    this->update_hammer_relatively_to_owner();

    // if the life time of the object is finished
    if (m_timeLeft <= 0)
    {
        // unlink him self with the player
        m_owner->set_weapon(nullptr);
        this->set_should_be_deleted(true); // destroy himself
    }
}

void Hammer::update_animation(float dt)
{
    m_animationClock += dt;
    if (m_animationClock >= m_animationInterval)
    {
        // reset the clock
        m_animationClock = 0;
        
        switch (m_animation) {
            case 0:
                this->set_height(m_owner->get_width());
                this->set_width(m_owner->get_width());
                ++m_animation;
                break;
            case 1:
                this->set_height(23);
                this->set_width(40);
                m_animation = 0;
                break;
            default:
                std::cout << "Maybe there's a problem there" << std::endl;
                break;
        }
        
        // reset the animation clock
        m_animationClock -= m_animationInterval;

        // set the new frame
        m_texture.loadFromImage(m_images[m_animation]);
    }
}

void Hammer::collision_callback(Element *element)
{
    switch (element->get_element_type())
    {
        case PLAYER: // if the hammer colide with a player
            this->collide_with_player(element);
            break;
        case FALLING_BARREL:
            this->collide_with_barrel(element);
            break;
        default:
            break;
    }
}

void Hammer::collide_with_player(Element *element)
{
    Player* player = (Player*) element;

    // try to equipe the player with the weapon, if it succeed then set him as the owner
    if (!m_isOwned) 
    {
        if (player->set_weapon(this))
        {
            m_isOwned = true;
            m_owner =  player;
        }
    }
}

void Hammer::collide_with_barrel(Element *element)
{
    // if the hammer is active and nothing is wrong with the owner
    if (m_isOwned && (m_owner != nullptr))
    { 
        // the barrel will be destroyed next frame it should not collide with the player on this frame
        element->set_collide(false);
        element->set_should_be_deleted(true);
        m_owner->add_player_score(POINTS_PER_BARREL_DESTROYED);
        this->spawn_text("+ " + std::to_string(POINTS_PER_BARREL_DESTROYED));
    }
}

void Hammer::update_hammer_relatively_to_owner()
{
    switch (m_animation)
    {
        case 0:
            this->set_x(m_owner->get_x());
            this->set_y(m_owner->get_y() - this->get_height());
            break;
        case 1:
            switch (m_owner->get_facing_direction())
            {
                case FACING_LEFT:
                    this->set_x(m_owner->get_x() - this->get_width());
                    this->set_y(m_owner->get_y() + this->get_height() / 3);
                    break;
                case FACING_RIGHT:
                    this->set_x(m_owner->get_x() + m_owner->get_width());
                    this->set_y(m_owner->get_y() + this->get_height() / 3);
                    break;
                default:
                    break;
            }
            break;
        default:
            std::cout << "Possibly there's a problem here" << std::endl;
            break;
    }
}

void Hammer::spawn_text(std::string text)
{
    Element *copy = m_elementToCopy->clone();
    Text *textCopy = (Text*) copy;
    textCopy->set_text(text);
    textCopy->set_x(this->get_x() + m_owner->get_width()/2);
    textCopy->set_y(this->get_y() + this->get_height()/2);
    textCopy->set_velocity_on_y(-10);
    m_movingElements.push_back(copy);
}

Element* Hammer::clone() const
{
    return new Hammer(*this);
}