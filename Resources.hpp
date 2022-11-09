#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <array>

struct Resources
{
    // Elements textures
    std::vector<sf::Image> m_player;
    std::vector<sf::Image> m_dk;
    std::vector<sf::Image> m_flame;
    std::vector<sf::Image> m_peach;
    std::vector<sf::Image> m_wall;
    std::vector<sf::Image> m_players_life;
    std::vector<sf::Image> m_ladder;
    std::vector<sf::Image> m_barrel;
    std::vector<sf::Image> m_vertical_barrel;
    std::vector<sf::Image> m_blue_barrel;
    std::vector<sf::Image> m_weapon;
    std::vector<sf::Image> m_victory;
    std::vector<sf::Image> m_defeat;
    std::vector<sf::Image> m_hammer;
    std::vector<sf::Image> m_pause;

    // Fonts
    std::vector<sf::Font> m_fonts;
    std::array<sf::Music, 1> m_music;

    static void load_resources1(Resources *resources);
};
