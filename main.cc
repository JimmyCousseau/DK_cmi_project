#include <iostream>

#include "Game.hpp"
#include "Maps.hpp"

int main()
{
	Game game;
	Maps::set_map(game, game.get_map_tag());

	/*
	* GAME LOOP
	*/
	sf::Clock clock;
	while (game.is_open())
	{
		// set a new map if needed
		if (game.get_change_map()) { Maps::set_map(game, game.get_map_tag()); }

		/*
		* update state
		*/
		float dt = clock.restart().asSeconds();
		game.update(dt);

		/*
		* render states
		*/

		game.render();
	}

	return 0;
}
