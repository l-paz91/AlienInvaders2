// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <SFML/Graphics.hpp>

#include "GameConstants.h"
#include "GameManager.h"

// -----------------------------------------------------------------------------



// -----------------------------------------------------------------------------

int main()
{
	using namespace sf;

	// create the main window
	RenderWindow window(VideoMode(GameGlobals::WIDTH, GameGlobals::HEIGHT), "Alien Invaders Window");

	// set framerate - Original Space Invaders ran at 60Hz so we want to try and mimic that
	window.setFramerateLimit(60);

	// clock for timing
	Clock clock;

	// ---- GAME MANAGER
	GameManager gameManager;

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
		gameManager.mInvaders.update(dt.asSeconds());
	
		// ---- UPDATE HUD --------------------------------------------------------- //
		gameManager.mGameHUD.update();

		// ---- RENDER OBJECTS ----------------------------------------------------- //
		gameManager.mInvaders.render(window);

		// ---- RENDER HUD --------------------------------------------------------- //
		gameManager.mGameHUD.render(window);

		// ---- DISPLAY WINDOW ----------------------------------------------------- //
		window.display();
	}

	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------