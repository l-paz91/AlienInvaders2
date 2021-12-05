// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <SFML/Graphics.hpp>

#include "GameConstants.h"
#include "TextureManager.h"

// -----------------------------------------------------------------------------



// -----------------------------------------------------------------------------

int main()
{
	using namespace sf;

	// create the main window
	RenderWindow window(VideoMode(GameConstants::WIDTH, GameConstants::HEIGHT), "Alien Invaders Window");

	// set framerate - Original Space Invaders ran at 60Hz so we want to try and mimic that
	window.setFramerateLimit(60);

	// clock for timing
	Clock clock;

	// ---- SPRITES
	Sprite playerSprite(Sprite(TextureManager::getTexture("Graphics/player.png")));
	playerSprite.setOrigin(20, 0); // top middle
	playerSprite.setPosition(GameConstants::HALFW, GameConstants::PLAYER_Y);

	// start the game loop
	while (window.isOpen())
	{
		// Handle Timing
		Time dt = clock.restart();

		// ---- PROCESS EVENTS ----------------------------------------------------- //
		Event event;
		while (window.pollEvent(event))
		{
			// close the window: exit
			if (event.type == Event::Closed || event.key.code == Keyboard::Escape)
			{
				window.close();
			}
		}

		// ---- CLEAR SCREEN ------------------------------------------------------- //
		window.clear();

		// ---- UPDATE OBJECTS ----------------------------------------------------- //


		// ---- UPDATE HUD --------------------------------------------------------- //


		// ---- RENDER OBJECTS ----------------------------------------------------- //
		window.draw(playerSprite);

		// ---- RENDER HUD --------------------------------------------------------- //


		// ---- DISPLAY WINDOW ----------------------------------------------------- //
		window.display();
	}

	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------