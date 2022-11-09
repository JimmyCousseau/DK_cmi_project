#include "Resources.hpp"

void Resources::load_resources1(Resources *resources)
{
    sf::Image img;
    sf::Font font;
    sf::Music music;
    // Fonts
    if (!font.loadFromFile("resources/fonts/arial.ttf"))
    {
        std::cout << "Error, could not load arial.ttf" << std::endl;
    }
    resources->m_fonts.push_back(font);

    // Murs
    if (!img.loadFromFile("resources/images/mur1.jpg"))
    {
        std::cout << "Error, could not load mur1.jpg" << std::endl;
    }
    resources->m_wall.push_back(img);

    // Mario
    if (!img.loadFromFile("resources/images/marios_life.png"))
    {
        std::cout << "Error, could not load marios_life.png" << std::endl;
    }
    resources->m_players_life.push_back(img);

    if (!img.loadFromFile("resources/images/mario_stopped.png"))
    {
        std::cout << "Error, could not load mario_stopped.png" << std::endl;
    }
    resources->m_player.push_back(img);

    if (!img.loadFromFile("resources/images/mario_running1.png"))
    {
        std::cout << "Error, could not load mario_running1.png" << std::endl;
    }
    resources->m_player.push_back(img);

    if (!img.loadFromFile("resources/images/mario_running2.png"))
    {
        std::cout << "Error, could not load mario_running2.png" << std::endl;
    }
    resources->m_player.push_back(img);

    if (!img.loadFromFile("resources/images/mario_jumping.png"))
    {
        std::cout << "Error, could not load mario_jumping.png" << std::endl;
    }
    resources->m_player.push_back(img);

    if (!img.loadFromFile("resources/images/mario_climbing_ladders.png"))
    {
        std::cout << "Error, could not load mario_climbing_ladders.png" << std::endl;
    }
    resources->m_player.push_back(img);

    // Weapons
    if (!img.loadFromFile("resources/images/shield.png"))
    {
        std::cout << "Error, could not load shield.png" << std::endl;
    }
    resources->m_weapon.push_back(img);

    // Ladders
    if (!img.loadFromFile("resources/images/ladder.png"))
    {
        std::cout << "Error, could not load ladder.png" << std::endl;
    }
    resources->m_ladder.push_back(img);

    // Barrels
    if (!img.loadFromFile("resources/images/barrel.png"))
    {
        std::cout << "Error, could not load barrel.png" << std::endl;
    }
    resources->m_barrel.push_back(img);

    if (!img.loadFromFile("resources/images/vertical_barrel.png"))
    {
        std::cout << "Error, could not load vertical_barrel.png" << std::endl;
    }
    resources->m_vertical_barrel.push_back(img);

    if (!img.loadFromFile("resources/images/blue_barrel.png"))
    {
        std::cout << "Error, could not load blue_barrel.png" << std::endl;
    }
    resources->m_blue_barrel.push_back(img);

    // Donkey Kong
    if (!img.loadFromFile("resources/images/dk_pause_relax.png"))
    {
        std::cout << "Error, could not load dk_pause_relax.png" << std::endl;
    }
    resources->m_dk.push_back(img);

    if (!img.loadFromFile("resources/images/dk_pause_tense.png"))
    {
        std::cout << "Error, could not load dk_pause_tense.png" << std::endl;
    }
    resources->m_dk.push_back(img);

    if (!img.loadFromFile("resources/images/dk_pause_tense_smiling.png"))
    {
        std::cout << "Error, could not load dk_pause_tense_smiling.png" << std::endl;
    }
    resources->m_dk.push_back(img);

    if (!img.loadFromFile("resources/images/dk_excited.png"))
    {
        std::cout << "Error, could not load dk_excited.png" << std::endl;
    }
    resources->m_dk.push_back(img);

    if (!img.loadFromFile("resources/images/dk_throwing_barrel.png"))
    {
        std::cout << "Error, could not load dk_throwing_barrel.png" << std::endl;
    }
    resources->m_dk.push_back(img);

    // Flames
    if (!img.loadFromFile("resources/images/flame1.png"))
    {
        std::cout << "Error, could not load flame1.png" << std::endl;
    }
    resources->m_flame.push_back(img);

    if (!img.loadFromFile("resources/images/flame2.png"))
    {
        std::cout << "Error, could not load flame2.png" << std::endl;
    }
    resources->m_flame.push_back(img);

    // Peach
    if (!img.loadFromFile("resources/images/peach1.png"))
    {
        std::cout << "Error, could not load peach1.png" << std::endl;
    }
    resources->m_peach.push_back(img);

    if (!img.loadFromFile("resources/images/peach2.png"))
    {
        std::cout << "Error, could not load peach2.png" << std::endl;
    }
    resources->m_peach.push_back(img);

    if (!img.loadFromFile("resources/images/victory.png"))
    {
        std::cout << "Error, could not load victory.png" << std::endl;
    }
    resources->m_victory.push_back(img);

    if (!img.loadFromFile("resources/images/defeat.png"))
    {
        std::cout << "Error, could not load defeat.png" << std::endl;
    }
    resources->m_defeat.push_back(img);

    // hammer
    if (!img.loadFromFile("resources/images/hammer.png"))
    {
        std::cout << "Error, could not load hammer.png" << std::endl;
    }
    resources->m_hammer.push_back(img);

    if (!img.loadFromFile("resources/images/hammer_striking.png"))
    {
        std::cout << "Error, could not load hammer_striking.png" << std::endl;
    }
    resources->m_hammer.push_back(img);

    if (!img.loadFromFile("resources/images/pause_img.png"))
    {
        std::cout << "Error, could not load pause_img.png" << std::endl;
    }
    resources->m_pause.push_back(img);

    // music
    if (!resources->m_music[0].openFromFile("resources/songs/main.ogg"))
    {
        std::cout << "Error, could not load main.ogg" << std::endl;
    }
}
