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
	constexpr int INVADER_YSTART = 384;
	const sf::IntRect octopus1 = sf::IntRect(0, 0, 36, 24);
	const sf::IntRect octopus2 = sf::IntRect(36, 0, 36, 24);

	const sf::IntRect crab1 = sf::IntRect(0, 24, 32, 24);
	const sf::IntRect crab2 = sf::IntRect(36, 24, 32, 24);

	const sf::IntRect squid1 = sf::IntRect(0, 48, 24, 24);
	const sf::IntRect squid2 = sf::IntRect(36, 48, 24, 24);

	const sf::IntRect destroyed = sf::IntRect(0, 72, 32, 24);

	static float INVADER_SPEED = 6.0f;
	static int INVADER_SIZE = 48;
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

	static void drawInvaders(const std::vector<GameObjects::Invader>& pInvaders, sf::RenderWindow& pWindow)
	{
		for (const GameObjects::Invader& i : pInvaders)
		{
			pWindow.draw(i.mSprite);
		}
	}

	// -----------------------------------------------------------------------------

	static void initInvaders(std::vector<GameObjects::Invader>& pInvaders)
	{
		using namespace GameObjects;

		float x = INVADER_XSTART;
		float y = INVADER_YSTART;

		// rows 0 & 1
		for (uint32_t i = 0; i < 22; ++i)
		{
			pInvaders[i].mSprite.setTextureRect(octopus2);
			pInvaders[i].mType = InvaderType::eOCTOPUS;
		}

		// rows 2 & 3
		for (uint32_t i = 22; i < 44; ++i)
		{
			pInvaders[i].mSprite.setTextureRect(crab2);
			pInvaders[i].mType = InvaderType::eCRAB;
		}

		// row 4
		for (uint32_t i = 44; i < 55; ++i)
		{
			pInvaders[i].mSprite.setTextureRect(squid2);
			pInvaders[i].mType = InvaderType::eSQUID;
		}

		// set positions
		for (uint32_t i = 0; i < pInvaders.size(); ++i)
		{
			// start a new row after 11 invaders
			if (i % 11 == 0 && (i != 0))
			{
				y -= 48;
				x -= INVADER_SIZE;
				INVADER_SIZE *= -1;			
			}

			pInvaders[i].mSprite.setPosition(Vector2f(x, y));
			x += INVADER_SIZE;
		}
	}

	// -----------------------------------------------------------------------------

	static void moveInvaders(std::vector<GameObjects::Invader>& pInvaders)
	{
		using namespace GameObjects;

		// invaders move in time from the bottom left-hand invader in a snake-like pattern
		// up to the top right-hand invader

		// all invaders must have moved in 55 frames (1 each)
		// this is why the invaders speed up as they are destroyed
		// as each invader can be updated more times in 1 second

		static int invaderToUpdate = 0;
		Invader& invader = pInvaders[invaderToUpdate];
		
		// move it over
		invader.mSprite.move(Vector2f(INVADER_SPEED, 0));

		// check to see if an alien has hit an edge
		const float x = invader.mSprite.getPosition().x;
		if (x <= LEFT_EDGE || x >= RIGHT_EDGE - 48)
		{
			// drop the aliens by 1 row
			for (Invader& i : pInvaders)
			{
				i.mSprite.move(Vector2f(0, 24));
			}

			// set reverse speed
			INVADER_SPEED *= -1.0f;

			invaderToUpdate = 0;
			return;
		}

		++invaderToUpdate;
		if (invaderToUpdate == pInvaders.size())
		{
			invaderToUpdate = 0;
		}
	}
}

// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !GameConstants_H