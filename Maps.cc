#include "Maps.hpp"

void Maps::set_map(Game &game, int mapTag)
{
    game.set_change_map(false);
    switch (mapTag)
    {
    case 1:
        Maps::set_map1(game);
        game.set_change_map(false);
        break;
    default:
        break;
    }
}

void Maps::set_map1(Game &game)
{
    const int WINDOW_WIDTH = game.get_windowWidth();
    const int WINDOW_HEIGHT = game.get_windowHeight();
    const int PLATFORM_HEIGHT = 20;
    const int LADDER_WIDTH = 21;
    const int MARIO_HEIGHT = 41;
    const int MARIO_WIDTH = 29;

    game.set_map_tag(1);

    // loading the ressources only if needed
    if (game.get_resources_tag() != 1) 
    {
        Resources *currentGameRessources(game.get_game_resources_pointer());
        if (currentGameRessources != nullptr) { delete currentGameRessources; }

        // load the textures into the game
        Resources *gameResources = new Resources();
        Resources::load_resources1(gameResources);
        game.set_ressources_tag(1);
        game.set_game_ressources(gameResources);
    }

    Resources *gameResources = game.get_game_resources_pointer();

    // Creating mario only if needed
    const float marioX = 76;
    const float marioY = 737;
    Player *currentGameMario = game.get_mario_pointer();
    Player *mario;

    Text *text = new Text(0, 0, " ", gameResources->m_fonts[0], 20, 1.5);
    Weapon *hammer = new Hammer(390, 520, 40, 40, gameResources->m_hammer, text, game.get_moving_elements_list());
    game.add_moving_element(hammer);
    delete text;

    if ((currentGameMario != nullptr) && (currentGameMario->get_player_life() > 0))
    {
        currentGameMario->set_position(Vector2D(marioX, marioY));
        currentGameMario->set_velocity(Vector2D(0, 0));
        currentGameMario->set_facing_direction(FACING_RIGHT);
        currentGameMario->set_player_score(0);

        // in case mario died while climbing on a ladder
        currentGameMario->set_has_gravity(true);
        currentGameMario->set_physically_collide(true);
        currentGameMario->set_is_climbing_ladder(false);
        currentGameMario->set_weapon(nullptr);
        mario = currentGameMario;
    }
    else
    {
        // Delete the dead mario
        if (currentGameMario != nullptr) { delete currentGameMario; }

        // create a new one
        mario = new Player(marioX, marioY, MARIO_WIDTH, MARIO_HEIGHT, gameResources->m_player, NO, 0, true, 0, 0, true);
        game.set_mario(mario);
    }

    // Creating Bordure
    Rectangle *rightBordure = new Rectangle(WINDOW_WIDTH, 0, 10, WINDOW_HEIGHT);
    rightBordure->set_mass(0);
    rightBordure->set_bounciness(100);
    game.add_element_to_background(rightBordure);

    Rectangle *leftBordure = new Rectangle(-10, 0, 10, WINDOW_HEIGHT);
    leftBordure->set_mass(0);
    leftBordure->set_bounciness(100);
    game.add_element_to_background(leftBordure);

    // Creating walls
    Rectangle *firstFloor = new Rectangle(0, WINDOW_HEIGHT - PLATFORM_HEIGHT, WINDOW_WIDTH, PLATFORM_HEIGHT, gameResources->m_wall, HORIZONTALY, 0, false, 0, 0, true);
    firstFloor->set_mass(0);
    game.add_element_to_background(firstFloor);

    Rectangle *plat_1 = new Rectangle(0, 658, 560, PLATFORM_HEIGHT, gameResources->m_wall, HORIZONTALY, 4.29, false, 0, 0, true);
    plat_1->set_mass(0);
    game.add_element_to_background(plat_1);

    Rectangle *plat_2 = new Rectangle(71, 544.8 + 65.7 - PLATFORM_HEIGHT, 569, PLATFORM_HEIGHT, gameResources->m_wall, HORIZONTALY, -3.95, false, 0, 0, true);
    plat_2->set_mass(0);
    game.add_element_to_background(plat_2);

    Rectangle *plat_3 = new Rectangle(0, 428.8, 573, PLATFORM_HEIGHT,gameResources->m_wall, HORIZONTALY, 4.17, false, 0, 0, true);
    plat_3->set_mass(0);
    game.add_element_to_background(plat_3);

    Rectangle *plat_4 = new Rectangle(64.8, 328 + 64 - PLATFORM_HEIGHT, 575, PLATFORM_HEIGHT, gameResources->m_wall, HORIZONTALY,-4.47, false, 0, 0, true);
    plat_4->set_mass(0);
    game.add_element_to_background(plat_4);

    Rectangle *plat_5 = new Rectangle(0, 223, 317, PLATFORM_HEIGHT, gameResources->m_wall, HORIZONTALY, 0, false, 0, 0, true);
    plat_5->set_mass(0);
    game.add_element_to_background(plat_5);

    Rectangle *plat_6 = new Rectangle(316, 223, 243, PLATFORM_HEIGHT, gameResources->m_wall, HORIZONTALY, 10.18, false, 0, 0, true);
    plat_6->set_mass(0);
    game.add_element_to_background(plat_6);

    Rectangle *final = new Rectangle(168, 126.4, 134, PLATFORM_HEIGHT, gameResources->m_wall, HORIZONTALY, 0, false, 0, 0, true);
    final->set_mass(0);
    game.add_element_to_background(final);

    // Creating barrels
    Rectangle *blue_barrel = new Rectangle(12, 739.2, 40, 40, gameResources->m_blue_barrel, NO, 0, false, 0, 0, true);
    blue_barrel->set_mass(0);
    blue_barrel->set_element_type(BLUE_BARREL);
    game.add_element_to_background(blue_barrel);

    Rectangle *vertical_barrel = new Rectangle(0, 148.9, 46, 74, gameResources->m_vertical_barrel, NO, 0, false, 0, 0, true);
    vertical_barrel->set_mass(0);
    game.add_element_to_background(vertical_barrel);

    // Creating ladders
    Rectangle *ladder1 = new Rectangle(501, 697.6, LADDER_WIDTH, 82, gameResources->m_ladder, VERTICALY, 0, false, 0, 0, true);
    ladder1->set_element_type(LADDER);
    ladder1->set_physically_collide(false);
    game.add_element_to_background(ladder1);

    Rectangle *ladder2 = new Rectangle(120, 587, LADDER_WIDTH, 85, gameResources->m_ladder, VERTICALY, 0, false, 0, 0, true);
    ladder2->set_element_type(LADDER);
    ladder2->set_physically_collide(false);
    game.add_element_to_background(ladder2);

    Rectangle *ladder3 = new Rectangle(484.8, 465.6, LADDER_WIDTH, 91, gameResources->m_ladder, VERTICALY, 0, false, 0, 0, true);
    ladder3->set_element_type(LADDER);
    ladder3->set_physically_collide(false);
    game.add_element_to_background(ladder3);

    Rectangle *ladder4 = new Rectangle(352.8, 348.8, LADDER_WIDTH, 109, gameResources->m_ladder, VERTICALY, 0, false, 0, 0, true);
    ladder4->set_element_type(LADDER);
    ladder4->set_physically_collide(false);
    game.add_element_to_background(ladder4);

    Rectangle *ladder5 = new Rectangle(113.6, 368.2, LADDER_WIDTH, 72, gameResources->m_ladder, VERTICALY, 0, false, 0, 0, true);
    ladder5->set_element_type(LADDER);
    ladder5->set_physically_collide(false);
    game.add_element_to_background(ladder5);

    Rectangle *ladder6 = new Rectangle(460, 252.8, LADDER_WIDTH, 91, gameResources->m_ladder, VERTICALY, 0, false, 0, 0, true);
    ladder6->set_element_type(LADDER);
    ladder6->set_physically_collide(false);
    game.add_element_to_background(ladder6);

    Rectangle *ladder7 = new Rectangle(281.6, 126.4, LADDER_WIDTH, 100, gameResources->m_ladder, VERTICALY, 0, false, 0, 0, true);
    ladder7->set_element_type(LADDER);
    ladder7->set_physically_collide(false);
    game.add_element_to_background(ladder7);

    Rectangle *ladder8 = new Rectangle(168, 126.4, LADDER_WIDTH, 100, gameResources->m_ladder, VERTICALY, 0, false, 0, 0, true);
    ladder8->set_element_type(LADDER);
    ladder8->set_physically_collide(false);
    game.add_element_to_background(ladder8);

    // Creating DK
    FallingBarrel *donkeyKongBarrel = new FallingBarrel(0, 0, 10, gameResources->m_barrel, 100, -100);
    donkeyKongBarrel->set_bounciness(0.5);
    DonkeyKong *dk = new DonkeyKong(50.4, 162.4, 82, 61, gameResources->m_dk, donkeyKongBarrel, game.get_moving_elements_list(), 1);
    dk->set_mass(0);
    delete donkeyKongBarrel;
    game.add_moving_element(dk);

    // Creating peach
    Rectangle *peach = new Rectangle(216, 86.4, 29, 40, gameResources->m_peach, NO, 0, false, 0, 0, true);
    peach->set_mass(0);
    peach->set_element_type(PEACH);
    peach->set_physically_collide(false);
    game.add_element_to_background(peach);

    // Creating flames
    Rectangle *flame = new Rectangle(12, 700.8, 40, 38, gameResources->m_flame, NO, 0, false, 0, 0, false);
    game.add_element_to_background(flame);

    // Creating the ScoreBoard
    ScoreBoard *score = new ScoreBoard(0, 0, WINDOW_WIDTH, 200, gameResources->m_fonts, mario);
    game.add_element_to_background(score);

    // start the music
    gameResources->m_music[0].play();
    gameResources->m_music[0].setLoop(true);
}
