// #include "Spawner.hpp"

// Spawner::Spawner(int x, int y, float frequency, int limitOfMob, sf::Color color) : 
// Element(x, y, 0, false, 0, 0, false), m_frequency(frequency), m_limitOfMob(limitOfMob)
// {

// }
// Spawner::~Spawner() {

// }

// void Spawner::draw(sf::RenderWindow &window)
// {

// }

// void Spawner::update_spawn(float dt) {
//     m_clock2 = dt;
//     m_clock += dt;
//     if (m_clock >= m_frequency)
//     {
//         m_clock = 0;
//         if (m_allCircle.size() < m_limitOfMob) {
//             Circle elem = *m_circle;

//             // Copy the content of m_element into element
//             m_allCircle.push_back(elem);
//         }
//     }
// }

// void Spawner::collide_handler(const std::vector<Element *> &backGroundElements,
//                       const std::vector<Element *> &movingElements,
//                       Player *player)
// {
//     Vector2D direction;
//     for (int i = 0; i < backGroundElements.size(); i++) {
//         if (backGroundElements[i]->get_does_collide())
//         {
//             for (int j = 0; j < m_allCircle.size(); j++)
//             {
//                 const float distance = Physics::EPA(&m_allCircle[j], backGroundElements[i], direction);

//                 if (distance < 0 && m_allCircle[j].get_does_collide()) // if there is collision and that the spawner allow collision
//                 {
//                     m_allCircle[j].move_in_a_direction(direction, distance);
//                     m_allCircle[j].set_velocity_on_y(-150);
//                 }
//             }
//         }
//     }


//     for (int j = 0; j < m_allCircle.size(); j++)
//     {
//         const float distance1 = Physics::EPA(player, &m_allCircle[j], direction);
//         const float distance2 = Physics::EPA(player->get_player_weapon(), &m_allCircle[j], direction);

//         if (distance1 < 0 && m_allCircle[j].get_does_collide()) // if there is collision and that the spawner allow collision
//         {
//             player->move_in_a_direction(direction, distance1);
//             // There's collision between the spawner's object and the player
//             // Here is the effect
//         }
//         if (distance2 < 0 && m_allCircle[j].get_does_collide())
//         {
//             m_allCircle.erase(m_allCircle.begin() + j);
//             player->add_player_score(100);
//         }
//     }
// }

// void Spawner::dispawn_handler(const int windowWidth) {
//     for (int i = 0; i < m_allCircle.size(); i++) {
//         if (m_allCircle[i].get_x() > windowWidth || m_allCircle[i].get_x() < 0) {
//             m_allCircle.erase(m_allCircle.begin() + i);
//         }
//     }
// }

// void Spawner::update_animation(float dt, const sf::Image img[])
// {
    
// }
// void Spawner::update_animation2(float dt, const sf::Image img[])
// {
// }

// // Getters
// Vector2D Spawner::get_center() const {}
// Vector2D Spawner::get_futhest_point(const Vector2D &direction) const {}
