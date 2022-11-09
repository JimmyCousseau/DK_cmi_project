#pragma once

#include <list>
#include <vector>

#include "Element.hpp"
#include "Spawner.hpp"
#include "Rectangle.hpp"
#include "Circle.hpp"
#include "Physics.hpp"
#include "Player.hpp"
#include "Text.hpp"
#include "Resources.hpp"
#include "Inputs.hpp"
#include "Text.hpp"
#include "FallingBarrel.hpp"


enum GameState
{
    GAME_MENU,
    GAME_PLAYING,
    GAME_PAUSED,
    GAME_FINISHED,
    GAME_START,
    GAME_RESTART
};

class Game
{
public:
    Game();
    ~Game();

    void update(float dt); // update every elements of the game by aplying physics on them
    void update_game_menu(float dt);
    void update_game_playing(float dt);
    void update_game_paused();
    void update_game_finished(float dt);
    void update_game_state();
    void render(); // render a frame of the game

    void add_element_to_background(Element *element);
    void add_moving_element(Element *element);
    void level_completed();
    void level_failed();
    void game_restart();

    // Getters
    bool is_open() const;
    int get_windowWidth() const;
    int get_windowHeight() const;
    std::list<Element *> &get_moving_elements_list();
    GameState get_game_state() const;
    int get_resources_tag() const;
    Resources *get_game_resources_pointer();
    Player *get_mario_pointer();
    int get_map_tag() const;
    bool get_change_map() const;

    // Setter
    void set_mario(Player *mario);
    void set_game_ressources(Resources *gameResources);
    void set_ressources_tag(int ressourceTag);
    void set_map_tag(int mapTag);
    void set_change_map(bool changeMap);

private:
    // update mario's attributes (is_on_ground, velocity, position...) by colliding him with all background elements
    void update_mario(float dt, Inputs inputs);
    bool m_changeMap = true;

    GameState m_gameState = GAME_PLAYING;
    int m_windowWidth;
    int m_windowHeight;
    Inputs m_userInputs;

    std::vector<Element *> m_backGroundElements;
    std::list<Element *> m_movingElements; // Avant c'était list
    Player *m_mario = nullptr;

    sf::RenderWindow m_window;
    Rectangle *m_pause = nullptr;

    Resources *m_gameResources = nullptr;
    int m_resourcesTag = 0; // This memorize the ressources of which map is currently loaded in the game
    int m_mapTag = 1;
};
