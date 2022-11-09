#include "Game.hpp"

#define MARIO_GRAVITY_ACCELERATION 1500
#define MOVING_ELEMENT_GRAVITY_ACCELERATION 1000
#define POINTS_JUMP_ABOVE_BARREL 50

Game::Game() : m_windowWidth(640), m_windowHeight(800), m_mario(nullptr), m_window(sf::VideoMode(m_windowWidth, m_windowHeight), L"Donkey Kong Arcade Incroyable")
{
    m_window.setFramerateLimit(144);
}

Game::~Game()
{
    // delete every elements
    for (Element *element : m_backGroundElements) { delete element; }
    for (Element *element : m_movingElements) { delete element; }
    delete m_mario;

    // empty the list/vector of elements
    m_backGroundElements.clear();
    m_movingElements.clear();

    if (m_gameResources != nullptr) { delete m_gameResources; }
}

void Game::update_mario(float dt, Inputs inputs)
{
    // resolve collision with mario and the background elements
    // also check if mario is on the ground and update mario's attribute to true if he is
    Vector2D direction;
    m_mario->set_is_on_ground(false);
    m_mario->set_is_on_ladder(false);
    for (Element *backGroundElement : m_backGroundElements)
    {
        // if one of theme doesnt collide just continue
        if ((!backGroundElement->get_does_collide()) || (!m_mario->get_does_collide())) { continue; }

        const float distance = Physics::EPA(m_mario, backGroundElement, direction);
        if (distance < 0) // if there is collision
        {
            m_mario->collision_callback(backGroundElement);
            backGroundElement->collision_callback(m_mario);

            // check if mario's collision vector is pointing up enought, if so it mean mario is on the ground
            const float ON_GROUND_THRESHOLD(0.3);
            if (Math::dot(-direction, Vector2D(0, -1)) > ON_GROUND_THRESHOLD)
            {
                m_mario->set_is_on_ground(true);
            }

            // if mario and the background element should physically collide, them resolve the collision
            if (m_mario->get_physically_collide() && backGroundElement->get_physically_collide())
            {
                Physics::resolve_collision(m_mario, backGroundElement, direction, distance);
            }
        }
    }

    Physics::apply_gravity(m_mario, dt, MARIO_GRAVITY_ACCELERATION);
    m_mario->update_player(m_userInputs, dt);
    m_mario->update_position(dt);
}

void Game::update_game_menu(float dt)
{
}

void Game::update_game_playing(float dt)
{
    // remove every moving element with a m_shouldBeDeleted attribute set to true
    std::list<Element *>::const_iterator itr = m_movingElements.cbegin();
    while (itr != m_movingElements.cend())
    {
        if ((*itr)->get_should_be_deleted()) { itr = m_movingElements.erase(itr); }
        else { ++itr; }
    }

    // update mario
    this->update_mario(dt, m_userInputs);

    // apply gravity on moving elements
    for (Element *movingElement : m_movingElements) { Physics::apply_gravity(movingElement, dt, MOVING_ELEMENT_GRAVITY_ACCELERATION); }

    // update every elements
    for (Element *backGroundElement : m_backGroundElements) { backGroundElement->update(dt); }
    for (Element *movingElement : m_movingElements) { movingElement->update(dt); }

    // resolve colision of every moving elements with background elements
    Vector2D direction;
    for (Element *movingElement : m_movingElements)
    {
        if (!movingElement->get_does_collide()) { continue; }

        for (Element *backGroundElement : m_backGroundElements)
        {
            if (!backGroundElement->get_does_collide()) { continue; }

            const float distance = Physics::EPA(backGroundElement, movingElement, direction);
            if (distance < 0) // if there is collision
            {
                backGroundElement->collision_callback(movingElement);
                movingElement->collision_callback(backGroundElement);
                if (backGroundElement->get_physically_collide() && movingElement->get_physically_collide())
                {
                    Physics::resolve_collision(backGroundElement, movingElement, direction, distance);
                }
            }
        }
    }

    // collide every moving elements with mario
    for (Element *movingElement : m_movingElements)
    {
        if (!movingElement->get_does_collide()) { continue; }

        const float distance = Physics::EPA(m_mario, movingElement, direction);
        if (distance < 0) // if there is collision
        {
            movingElement->collision_callback(m_mario);
            m_mario->collision_callback(movingElement);
            if (movingElement->get_physically_collide() && m_mario->get_physically_collide())
            {
                Physics::resolve_collision(movingElement, m_mario, direction, distance);
            }
        }

        // if mario jumped above the barrel, he should get points
        if (movingElement->get_element_type() == FALLING_BARREL)
        {
            FallingBarrel* barrel = (FallingBarrel*) movingElement;

            // if mario already jumped above this barrel he cant gain points anymore
            if (!barrel->get_is_already_jumped())
            {
                const float maximumHeightAboveToGetPoints = 40;
                const float RIGHT_ABOVE_THRESHOLD = 0.9;
                bool isAbove(Math::dot(direction, Vector2D(0, 1)) > RIGHT_ABOVE_THRESHOLD);
                bool marioShouldGetPoints((distance > 0) && (distance < maximumHeightAboveToGetPoints) && isAbove );
                if (marioShouldGetPoints)
                {
                    m_mario->get_center();
                    m_mario->add_player_score(POINTS_JUMP_ABOVE_BARREL);
                    barrel->set_is_already_jumped(true);
                    
                    // adding a nice litle text
                    m_movingElements.push_back(new Text(barrel->get_x() - barrel->get_radius(),
                                                        barrel->get_y() + barrel->get_radius(), "+ " + std::to_string(POINTS_JUMP_ABOVE_BARREL), 
                                                        m_gameResources->m_fonts[0], 20, 1.5));
                }
            }
        }

    }

    // collide every moving elements to each others
    for (Element *movingElement1 : m_movingElements)
    {
        if (!movingElement1->get_does_collide()) { continue; }

        for (Element *movingElement2 : m_movingElements)
        {
            if (!movingElement2->get_does_collide()) { continue; }
            if (movingElement1 == movingElement2) { continue; }

            const float distance = Physics::EPA(movingElement1, movingElement2, direction);
            if (distance < 0) // if there is collision
            {
                movingElement1->collision_callback(movingElement2);
                movingElement2->collision_callback(movingElement1);
                if (movingElement1->get_physically_collide() && movingElement2->get_physically_collide())
                {
                    Physics::resolve_collision(movingElement1, movingElement2, direction, distance);
                }
            }
        }
    }

    // if mario won call the level completed method
    if (m_mario->get_player_is_victorious()) { this->level_completed(); }
    if (m_mario->get_player_is_touched_by_a_barrel()) { this->level_failed(); }
}

void Game::update_game_paused()
{
    if (m_pause == nullptr)
    {
        m_pause = new Rectangle(0, 0, m_windowWidth, m_windowHeight, m_gameResources->m_pause);
        m_movingElements.push_back(m_pause);
    }
}

void Game::update_game_finished(float dt)
{
}

void Game::game_restart()
{
    for (Element *element : m_movingElements) { delete element; }
    for (Element *element : m_backGroundElements) { delete element; }
    m_backGroundElements.clear();
    m_movingElements.clear();
    delete m_mario;
    m_mario = nullptr;
    m_changeMap = true;
}

void Game::update(float dt)
{
    // retrieve the user inputs
    m_userInputs.update(m_window);

    this->update_game_state();

    switch (m_gameState)
    {
    case GAME_MENU:
        this->update_game_menu(dt);
        break;
    case GAME_PLAYING:
        this->update_game_playing(dt);
        break;
    case GAME_PAUSED:
        this->update_game_paused();
        break;
    case GAME_FINISHED:
        this->update_game_finished(dt);
        break;
    case GAME_RESTART:
        this->game_restart();
        break;
    default:
        break;
    }
}

void Game::update_game_state()
{
    switch (m_gameState)
    {
    case GAME_MENU:
        break;
    case GAME_PLAYING:
        // Check if the game have to be paused according to the inputs
        if (m_userInputs.echapKeyPressed || m_userInputs.paused)
        {
            m_gameState = GAME_PAUSED;
        }
        break;
    case GAME_PAUSED:
        // if the echap key is pressed again, go back to the playing state
        if (!m_userInputs.paused && !m_userInputs.echapKeyPressed)
        {
            m_gameState = GAME_PLAYING;
            m_pause->set_should_be_deleted(true);
            m_pause = nullptr;
        }

        // if delete key is pressed during game pause, restart the game
        if (m_userInputs.deleteKeyPressed)
        {
            m_userInputs.deleteKeyPressed = false;
            m_gameState = GAME_RESTART;
        }
        break;
    case GAME_FINISHED:
        // if delete key is pressed during the finished screen, restart the game
        if (m_userInputs.deleteKeyPressed)
        {
            m_userInputs.deleteKeyPressed = false;
            m_gameState = GAME_RESTART;
        }
        break;
    case GAME_RESTART:
        // The game is now already restarted, the game is now put in game playing state
        m_gameState = GAME_PLAYING;
        // if m_pause is not a nullptr, this means that the game was in paused state, so this break the pause mode
        if (m_pause != nullptr)
        {
            m_pause->set_should_be_deleted(true);
            m_pause = nullptr;
            m_userInputs.paused = false;
        }
        break;
    default:
        break;
    }
}

void Game::level_completed()
{
    m_gameState = GAME_FINISHED;
    for (Element *element : m_movingElements) { delete element; }
    m_movingElements.clear();
    Rectangle *victory = new Rectangle(0, 0, m_windowWidth, m_windowHeight, m_gameResources->m_victory);

    m_backGroundElements.push_back(victory);
}

void Game::level_failed()
{
    m_mario->set_player_is_touched_by_a_barrel(false);
    if (m_mario->get_player_life() == 0)
    {
        for (Element *element : m_movingElements) { delete element; }
        m_movingElements.clear();
        Rectangle *defeat = new Rectangle(0, 0, m_windowWidth, m_windowHeight, m_gameResources->m_defeat);
        m_backGroundElements.push_back(defeat);
        m_gameState = GAME_FINISHED;
    }
    else
    {
        for (Element *element : m_movingElements) { delete element; }
        for (Element *element : m_backGroundElements) { delete element; }
        m_movingElements.clear();
        m_backGroundElements.clear();
        m_changeMap = true;
    }
}

void Game::render()
{
    m_window.clear(sf::Color::Black);

    // draw every elements of the game
    for (Element *element : m_backGroundElements) { if (element != nullptr) { element->draw(m_window); } }
    for (Element *element : m_movingElements) { element->draw(m_window); }

    if (m_mario != nullptr) { m_mario->draw(m_window); }

    m_window.display();
}

void Game::add_element_to_background(Element *element)
{
    m_backGroundElements.push_back(element);
}

void Game::add_moving_element(Element *element)
{
    m_movingElements.push_back(element);
}

// getters
int Game::get_windowWidth() const { return m_windowWidth; }
int Game::get_windowHeight() const { return m_windowHeight; }
bool Game::is_open() const { return m_window.isOpen(); }
std::list<Element *> &Game::get_moving_elements_list() { return m_movingElements; }
GameState Game::get_game_state() const { return m_gameState; }
int Game::get_resources_tag() const { return m_resourcesTag; }
Resources *Game::get_game_resources_pointer() { return m_gameResources; }
Player *Game::get_mario_pointer() { return m_mario; }
int Game::get_map_tag() const { return m_mapTag; }
bool Game::get_change_map() const { return m_changeMap; }

// setters
void Game::set_mario(Player *mario) { m_mario = mario; }
void Game::set_game_ressources(Resources *resources) { m_gameResources = resources; }
void Game::set_ressources_tag(int ressourceTag) { m_resourcesTag = ressourceTag; }
void Game::set_map_tag(int mapTag) { m_mapTag = mapTag; }
void Game::set_change_map(bool changeMap) { m_changeMap = changeMap; }
