// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <SFML/Graphics.hpp>

#include "GameConstants.h"
#include "HUD.h"
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

	// ---- PLAYER
	Sprite playerSprite(Sprite(TextureManager::getTexture("Graphics/player.png")));
	playerSprite.setOrigin(GameConstants::PLAYER_OFFSET, 0); // top middle
	playerSprite.setPosition(GameConstants::HALFW, GameConstants::PLAYER_Y);

	GameObjects::PlayerShot playerShot;

	// ---- INVADERS
	std::vector<GameObjects::Invader> invaders(55);	
	GameFunctions::initInvaders(invaders);

	// ---- HUD
	HUD gameHUD;

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

		// end the game for now
		if (GameConstants::INVADERS_DESTROYED == 55)
		{
			break;
		}

		// ---- CLEAR SCREEN ------------------------------------------------------- //
		window.clear();

		// ---- UPDATE OBJECTS ----------------------------------------------------- //
		GameFunctions::movePlayer(playerSprite, dt.asSeconds());
		GameFunctions::moveInvaders(invaders);

		GameFunctions::updatePlayerShot(playerShot, playerSprite.getPosition().x, dt.asSeconds());
		GameFunctions::hasPlayerHitInvader(playerShot, invaders, gameHUD);

		
		// ---- UPDATE HUD --------------------------------------------------------- //
		gameHUD.update();

		// ---- RENDER OBJECTS ----------------------------------------------------- //
		window.draw(playerSprite);
		GameFunctions::drawInvaders(invaders, window);
		GameFunctions::drawPlayerShot(playerShot, window);

		// ---- RENDER HUD --------------------------------------------------------- //
		gameHUD.render(window);

		// ---- DISPLAY WINDOW ----------------------------------------------------- //
		window.display();
	}

	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------