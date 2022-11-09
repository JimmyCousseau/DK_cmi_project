#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

#include "Game.hpp"
#include "Spawner.hpp"
#include "Rectangle.hpp"
#include "Circle.hpp"
#include "Text.hpp"
#include "ScoreBoard.hpp"
#include "Resources.hpp"
#include "DonkeyKong.hpp"
#include "FallingBarrel.hpp"
#include "Hammer.hpp"
#include "Weapon.hpp"

struct Maps
{
    // take a game and initialise it with every elements of the first level and load the according textures
    static void set_map(Game &game, int mapTag);
    static void set_map1(Game &game);
};
