// #pragma once

// #include <vector>
// #include <SFML/Graphics.hpp>

// #include "Element.hpp"
// #include "Physics.hpp"
// #include "Player.hpp"

// class Spawner : public Element
// {
// public:
//     Spawner(int x, int y, float frequency = 20, int limitOfMob = 5, sf::Color color = sf::Color::Transparent);
//     ~Spawner();

//     void draw(sf::RenderWindow &window);

//     void update_animation(float dt, const sf::Image img[]);
//     void update_animation2(float dt, const sf::Image img[]);

//     void update_spawn(float dt);
//     void collide_handler(const std::vector<Element *> &m_backGroundElements,
//                          const std::vector<Element *> &m_movingElements,
//                          Player *player);
//     void dispawn_handler(const int windowWidth);

//     // Getters
//     Vector2D get_center() const;
//     Vector2D get_futhest_point(const Vector2D &direction) const;

// private:
//     float m_frequency;
//     int m_limitOfMob;
//     double m_clock = 0;
//     double m_clock2 = 0;
//     Circle *m_circle;
//     std::vector<Circle> m_allCircle;
//     /* FacingDirection m_facingDirection = FACING_LEFT; */
// };
