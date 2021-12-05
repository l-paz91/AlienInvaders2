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
#include "TextureManager.h"

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

	constexpr int INVADER_XSTART = 75;
	constexpr int INVADER_YSTART = 192;
	const sf::IntRect octopus1 = sf::IntRect(0, 0, 36, 24);
	const sf::IntRect octopus2 = sf::IntRect(36, 0, 36, 24);

	const sf::IntRect crab1 = sf::IntRect(0, 24, 32, 24);
	const sf::IntRect crab2 = sf::IntRect(36, 24, 32, 24);

	const sf::IntRect squid1 = sf::IntRect(0, 48, 24, 24);
	const sf::IntRect squid2 = sf::IntRect(36, 48, 24, 24);

	const sf::IntRect destroyed = sf::IntRect(0, 72, 32, 24);
}

// -----------------------------------------------------------------------------

namespace GameObjects
{
	using namespace sf;

	// -----------------------------------------------------------------------------

	enum class InvaderType
	{
		eOCTOPUS,	// large invader - rows 4 & 5
		eCRAB,		// medium invader - rows 2 & 3
		eSQUID		// small invader - row 1
	};

	// -----------------------------------------------------------------------------

	struct Invader
	{
		Invader()
			: mSprite(Sprite(TextureManager::getTexture("Graphics/InvaderSpritesheet.png")))
			, mType(InvaderType::eOCTOPUS)
		{}

		Sprite mSprite;
		InvaderType mType;
	};
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

	template <size_t rows, size_t cols>
	static void drawInvaders(const GameObjects::Invader (&pInvaders)[rows][cols], sf::RenderWindow& pWindow)
	{
		for (const auto& invaderRow : pInvaders)
		{
			for (const auto& invader : invaderRow)
			{
				pWindow.draw(invader.mSprite);
			}
		}
	}

	// -----------------------------------------------------------------------------

	template <size_t rows, size_t cols>
	static void initInvaders(GameObjects::Invader(&pInvaders)[rows][cols])
	{
		float x = INVADER_XSTART;
		float y = INVADER_YSTART;

		// row 1
		for (int c = 0; c < 11; ++c)
		{
			pInvaders[0][c].mSprite.setTextureRect(squid2);
			pInvaders[0][c].mSprite.setPosition(Vector2f(x, y));
			x += 48;
		}

		y += 48;
		x = INVADER_XSTART;

		// row 2 & 3
		for (int r = 1; r < 3; ++r)
		{
			for (int c = 0; c < 11; ++c)
			{
				pInvaders[r][c].mSprite.setTextureRect(crab2);
				pInvaders[r][c].mSprite.setPosition(Vector2f(x, y));
				x += 48;
			}

			y += 48;
			x = INVADER_XSTART;
		}

		// row 4 & 5
		for (int r = 3; r < 5; ++r)
		{
			for (int c = 0; c < 11; ++c)
			{
				pInvaders[r][c].mSprite.setTextureRect(octopus2);
				pInvaders[r][c].mSprite.setPosition(Vector2f(x, y));
				x += 48;
			}

			y += 48;
			x = INVADER_XSTART;
		}

	}

	// -----------------------------------------------------------------------------

}

// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !GameConstants_H