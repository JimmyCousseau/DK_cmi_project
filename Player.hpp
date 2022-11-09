#pragma once

#include "Weapon.hpp"
#include "Resources.hpp"
#include "Inputs.hpp"

class Weapon;

class Player : public Rectangle
{
public:
    Player(float x, float y, int width, int height, const std::vector<sf::Image> &images, Repeated repeated, float rotation = 0, bool hasGravity = false, float velocityOnX = 0, float velocityOnY = 0, bool collide = true, Weapon *weapon = nullptr);
    Player(float x, float y, int width, int height, float rotation = 0, bool hasGravity = false, float velocityOnX = 0, float velocityOnY = 0, bool collide = true, Weapon *weapon = nullptr, sf::Color color = sf::Color::White);
    ~Player();

    void draw(sf::RenderWindow & window) override;

    // update the player animation accordingly with the inputs, also update the player velocity
    // in the direction he try to move, if the player try to move return true
    void update_player(Inputs &inputs, float dt);
    void update(float dt) override;
    void collision_callback(Element *element) override;
    void update_animation(float dt) override;

    // return a pointer to a copy of this element
    Element* clone() const override;

    // Getters
    int get_player_life() const;
    int get_player_score() const;
    Rectangle* get_player_weapon() const;
    bool get_is_on_ground() const;
    bool get_is_on_ladder() const;
    bool get_player_is_victorious() const;
    bool get_player_is_touched_by_a_barrel() const;
    FacingDirection get_facing_direction() const;

    // Setters
    void set_player_life(int life); // Pour le moment inutile
    void set_player_score(int score); // Idem
    void set_is_on_ground(bool isOnGround);
    void set_is_on_ladder(bool isOnLadder);
    void set_is_climbing_ladder(bool isClimbingLadder);
    void set_player_is_touched_by_a_barrel(bool isTouched);
    void set_facing_direction(FacingDirection facingDirection);
    bool set_weapon(Weapon *weapon);

    void add_player_life(int life);
    void add_player_score(int score);

private:
    int m_life = 3;
    int m_score = 0;
    bool m_playerIsVictorious = false;
    bool m_playerIsTouchedByABarrel = false;
    bool m_isOnLadder = false;
    bool m_isClimbingLadder = false;
    bool m_isOnGround = false;
    Weapon *m_weapon;
    FacingDirection m_facingDirection = FACING_LEFT;
};
