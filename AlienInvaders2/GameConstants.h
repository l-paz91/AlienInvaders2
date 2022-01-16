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
#include <SFML/Graphics.hpp>
#include <random>

#include "HUD.h"
#include "TextureManager.h"

// -----------------------------------------------------------------------------

namespace GameGlobals
{
	constexpr int WIDTH = 672;
	constexpr int HEIGHT = 768;
	constexpr int HALFW = WIDTH / 2;
	constexpr int HALFH = HEIGHT / 2;

	constexpr int TOP_BANNER = 99;
	constexpr int BOT_BANNER = 51;
	constexpr int LEFT_EDGE = 27;
	constexpr int RIGHT_EDGE = WIDTH - LEFT_EDGE;

	inline int randint(int min, int max)
	{
		static std::default_random_engine ran((unsigned int)time(0));
		return std::uniform_int_distribution<>{min, max}(ran);
	}
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !GameConstants_H