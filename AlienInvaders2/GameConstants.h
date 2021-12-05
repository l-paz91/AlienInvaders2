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

	constexpr int PLAYER_Y = 648;
	constexpr int BARRIER_Y = 576;
	constexpr int BARRIER1_X = 96;
	constexpr int BARRIER_GAP = 69;

	constexpr int INVADER_YSTART = 192;

	constexpr float TOP_BANNER = 99;
	constexpr float BOT_BANNER = 51;
	constexpr float LEFT_EDGE = 27;
	constexpr float RIGHT_EDGE = WIDTH - LEFT_EDGE;

	constexpr float PLAYER_SPEED = 180;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !GameConstants_H