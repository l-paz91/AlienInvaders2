// -----------------------------------------------------------------------------
#ifndef GameConstants_H
#define GameConstants_H
// -----------------------------------------------------------------------------

/*
*
*	In the original Space Invaders the screen is 224x256
*	Everything in this game is scaled by 3. This game is 672x768.
*	Banners relate to the screen padding at the top and bottom where the score
*   and lives are held.
*
*/

//--INCLUDES--//

// -----------------------------------------------------------------------------

namespace GameConstants
{
	constexpr int WIDTH = 672;
	constexpr int HEIGHT = 768;
	constexpr int HALFW = WIDTH / 2;
	constexpr int HALFH = HEIGHT / 2;

	constexpr int TOP_BANNER = 99;
	constexpr int BOT_BANNER = 51;
	constexpr int LEFT_EDGE = 27;
	constexpr int RIGHT_EDGE = WIDTH - LEFT_EDGE;

	constexpr int PLAYER_Y = 648;
	constexpr int PLAYER_OFFSET = 20;
	constexpr int PLAYER_MINX = LEFT_EDGE + PLAYER_OFFSET;
	constexpr int PLAYER_MAXX = RIGHT_EDGE - PLAYER_OFFSET;
	constexpr int PLAYER_SPEED = 180;

	constexpr int BARRIER_Y = 576;
	constexpr int BARRIER1_X = 96;
	constexpr int BARRIER_GAP = 69;

	constexpr int INVADER_YSTART = 192;
}

// -----------------------------------------------------------------------------

namespace GameFunctions
{
	using namespace GameConstants;

	// -----------------------------------------------------------------------------

	static void movePlayer(sf::Sprite& pPlayer, const float& pDeltaTime)
	{
		using namespace sf;

		// player can only move on X axis
		const Vector2f& pos = pPlayer.getPosition();

		const bool left = Keyboard::isKeyPressed(Keyboard::Left);
		const bool a = Keyboard::isKeyPressed(Keyboard::A);
		if (left || a)
		{
			if (!(pos.x <= PLAYER_MINX))
			{
				pPlayer.move(-PLAYER_SPEED * pDeltaTime, 0);
			}
		}

		const bool right = Keyboard::isKeyPressed(Keyboard::Right);
		const bool d = Keyboard::isKeyPressed(Keyboard::D);
		if (right || d)
		{
			if (!(pos.x >= PLAYER_MAXX))
			{
				pPlayer.move(PLAYER_SPEED * pDeltaTime, 0);
			}
		}
	}

	// -----------------------------------------------------------------------------


}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !GameConstants_H