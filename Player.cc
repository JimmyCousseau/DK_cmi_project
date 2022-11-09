#include "Player.hpp"

#define WALKING_SPEED 250
#define JUMPING_SPEED -400
#define CLIMBING_LADDER_SPEED 100
#define INDEX_IMAGE_START_WALKING 0
#define INDEX_IMAGE_END_WALKING 2
#define TIME_BETWEEN_WALKING_ANIMATION_FRAMES 0.1

Player::Player(float x, float y, int width, int height, const std::vector<sf::Image> &images, Repeated repeated, float rotation, bool hasGravity, float velocityOnX, float velocityOnY, bool collide, Weapon *weapon) : 
Rectangle(x, y, width, height, images, repeated, rotation, hasGravity, velocityOnX, velocityOnY, collide), m_weapon(weapon)
{
    m_ElementType = PLAYER;
    m_animationInterval = TIME_BETWEEN_WALKING_ANIMATION_FRAMES;
}

Player::Player(float x, float y, int width, int height, float rotation, bool hasGravity, float velocityOnX, float velocityOnY, bool collide, Weapon *weapon, sf::Color color) : 
Rectangle(x, y, width, height, rotation, hasGravity, velocityOnX, velocityOnY, collide, color), m_weapon(weapon)
{
    m_animationInterval = TIME_BETWEEN_WALKING_ANIMATION_FRAMES;
}

Player::~Player()
{

}

void Player::draw(sf::RenderWindow &window)
{
    auto size = m_texture.getSize(); // Get the size of the texture

    sf::RectangleShape player(sf::Vector2f(get_width(), get_height()));
    player.setPosition(m_position.x, m_position.y);
    player.setTexture(&m_texture);
    if (m_facingDirection == FACING_RIGHT) {
        player.setTextureRect(sf::IntRect(size.x, 0, -size.x, size.y));
    }
    if (m_hasColor) {
        player.setFillColor(m_color);

    }
    player.rotate(m_rotation);
    window.draw(player);
}

void Player::update(float dt) {
    // Useless by now because all is handled in game specifically for mario
}

void Player::collision_callback(Element* element)
{
    switch(element->get_element_type())
    {
        case FALLING_BARREL:
            --(this->m_life);
            this->m_playerIsTouchedByABarrel = true;
            break;
        case LADDER:
            this->m_isOnLadder = true;
            break;
        case PEACH:
            m_playerIsVictorious = true;
            break;
        default:
            break;
    }
}

void Player::update_player(Inputs &inputs, float dt)
{
    const bool BOTH_RIGHT_AND_LEFT_PRESSED = (inputs.leftKeyPressed && inputs.rightKeyPressed);
    const bool NO_RIGHT_NO_LEFT_PRESSED = !(inputs.leftKeyPressed || inputs.rightKeyPressed);
    const bool MARIO_ISNT_MOVING = (BOTH_RIGHT_AND_LEFT_PRESSED || NO_RIGHT_NO_LEFT_PRESSED);

    // reset the marios velocity to 0 if he's climbing
    if (m_isClimbingLadder) { m_velocity.y = 0; }

    // if mario press both left and right of don't press anything dont move
    if (MARIO_ISNT_MOVING)
    {
        m_velocity.x = 0;
        m_animation = 0;

        // Texture of mario when he's not moving
        if (m_hasTexture) { m_texture.loadFromImage(m_images[0]); }
    }
    
    // if mario only press left go to the left
    else if (inputs.leftKeyPressed)
    {
        m_velocity.x = -WALKING_SPEED;
        m_facingDirection = FACING_LEFT;
        this->update_animation(dt);
    }

    // mario last case is mario pressed right so go to the right
    else
    {
        m_velocity.x = WALKING_SPEED;
        m_facingDirection = FACING_RIGHT;
        this->update_animation(dt);
    }

    // UP KEY PRESSED
    if (inputs.upKeyPressed)
    {
        // if mario is climbing on a ladder make him climb on it
        if (m_isOnLadder && m_isClimbingLadder) 
        {
            m_velocity.y = -CLIMBING_LADDER_SPEED;
        }

        // if mario is on the ladder but not climbing make him climb on it
        else if (m_isOnLadder) 
        {
            m_isClimbingLadder = true;
            m_physicallyCollide = false;
            m_hasGravity = false;
        }

        // if mario is not on a lader and is on the ground make him jump
        else if (m_isOnGround)
        {
            m_velocity.y = JUMPING_SPEED;

            // Texture of mario when he's jumping
            if (m_hasTexture) { m_texture.loadFromImage(m_images[3]); }
        }
    }

    // DOWN KEY PRESSED
    if (inputs.downKeyPressed)
    {
        // if mario is on a ladder and currently climbing on it them move him down the ladder
        if (m_isOnLadder && m_isClimbingLadder)
        {
            m_velocity.y = CLIMBING_LADDER_SPEED;
        }
    }

    // if mario is in mid air
    if (!m_isOnGround)
    {
        // Texture of mario when he's jumping
        if (m_hasTexture)
        {
            m_texture.loadFromImage(m_images[3]);
        }
    }

    // if mario isn't on a ladder he cant climb anymore
    if (!m_isOnLadder) 
    {
        m_hasGravity = true;
        m_physicallyCollide = true;
        m_isClimbingLadder = false; 
    }

    if (inputs.pKeyPressed)
    {

    }
}

void Player::update_animation(float dt)
{
    m_animationClock += dt;

    // if enougth time passed since the last frame
    if (m_hasTexture)
    {
        if (m_animationClock >= m_animationInterval)
        {
            // reset the clock
            m_animationClock = 0;
            
            // change the frame to the next one in the loop
            if (m_animation < INDEX_IMAGE_END_WALKING) 
            {
                ++m_animation;
            }
            else
            {
                m_animation = INDEX_IMAGE_START_WALKING;
            }
            
            // set the new frame
            m_texture.loadFromImage(m_images[m_animation]);
        }
    }
}

Element* Player::clone() const
{
    return new Player(*this);
}

// Getters
int Player::get_player_life() const { return m_life; }
int Player::get_player_score() const { return m_score; }
Rectangle* Player::get_player_weapon() const { return m_weapon; }
bool Player::get_is_on_ground() const { return m_isOnGround; }
bool Player::get_is_on_ladder() const { return m_isOnLadder; }
bool Player::get_player_is_victorious() const { return m_playerIsVictorious; }
bool Player::get_player_is_touched_by_a_barrel() const { return m_playerIsTouchedByABarrel; }
FacingDirection Player::get_facing_direction() const { return m_facingDirection; }

// Setters
void Player::set_player_life(int life) { m_life = life; }
void Player::set_player_score(int score) { m_score = score; }
void Player::set_is_on_ground(bool isOnGround) { m_isOnGround = isOnGround; }
void Player::set_is_on_ladder(bool isOnLadder) { m_isOnLadder = isOnLadder; }
void Player::set_is_climbing_ladder(bool isClimbingLadder) { m_isClimbingLadder = isClimbingLadder; }
void Player::set_player_is_touched_by_a_barrel(bool isTouched) { m_playerIsTouchedByABarrel = isTouched; }
void Player::set_facing_direction(FacingDirection facingDirection) { m_facingDirection = facingDirection; }
bool Player::set_weapon(Weapon *weapon)
{
    if (weapon != nullptr) { delete m_weapon; }
    m_weapon = weapon;
    return true;
}

void Player::add_player_life(int life) { m_life += life; }
void Player::add_player_score(int score) { m_score += score; }
