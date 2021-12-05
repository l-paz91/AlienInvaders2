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
	constexpr int INVADER_MAX_SHOTS = 3;

	const sf::IntRect octopus1 = sf::IntRect(0, 0, 36, 24);
	const sf::IntRect octopus2 = sf::IntRect(36, 0, 36, 24);

	const sf::IntRect crab1 = sf::IntRect(0, 24, 32, 24);
	const sf::IntRect crab2 = sf::IntRect(36, 24, 32, 24);

	const sf::IntRect squid1 = sf::IntRect(0, 48, 24, 24);
	const sf::IntRect squid2 = sf::IntRect(36, 48, 24, 24);

	const sf::IntRect destroyed = sf::IntRect(0, 72, 32, 24);

	static int INVADER_GRID[5][11];
	static float INVADER_SPEED = 6.0f;
	static int INVADER_SIZE = 48;
	static int INVADERS_DESTROYED = 0;
	static float INVADER_SHOT_ELAPSED_TIME = 0.0f;
	static int INVADER_TO_UPDATE = 0;
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
			, mDestroyed(false)
		{}

		Sprite mSprite;
		InvaderType mType;
		bool mDestroyed;
	};

	// -----------------------------------------------------------------------------

	struct PlayerShot
	{
		PlayerShot()
			: mPlayerShotRect()
			, mShotsFired(false)
		{
			mPlayerShotRect.setSize(Vector2f(3.0f, 12.0f));
			mPlayerShotRect.setFillColor(Color::White);
		}

		RectangleShape mPlayerShotRect;
		bool mShotsFired;
	};

	// -----------------------------------------------------------------------------

	struct InvaderShot
	{
		InvaderShot(Vector2f pPos)
		{
			mInvaderShotRect.setSize(Vector2f(3.0f, 12.0f));
			mInvaderShotRect.setFillColor(Color::White);
			mInvaderShotRect.setPosition(pPos);
		}

		RectangleShape mInvaderShotRect;
	};

	// -----------------------------------------------------------------------------
}

// -----------------------------------------------------------------------------

namespace GameFunctions
{
	using namespace GameConstants;

	// -----------------------------------------------------------------------------

	template<typename T1, typename T2>
	static bool hasSpriteCollided(const T1& pSprite1, const T2& pSprite2)
	{
		return pSprite1.getGlobalBounds().intersects(pSprite2.getGlobalBounds());
	}

	// -----------------------------------------------------------------------------

	inline int randint(int min, int max)
	{
		std::default_random_engine ran((unsigned int)time(0));
		return std::uniform_int_distribution<>{min, max}(ran);
	}

	// -----------------------------------------------------------------------------

	inline int randint(int max) { return randint(0, max); }

	// -----------------------------------------------------------------------------

	static void initGrid()
	{
		for (int c = 0, i = 44; c < 11; ++c, ++i)
			INVADER_GRID[0][c] = i;

		for (int c = 0, i = 43; c < 11; ++c, --i)
			INVADER_GRID[1][c] = i;

		for (int c = 0, i = 22; c < 11; ++c, ++i)
			INVADER_GRID[2][c] = i;

		for (int c = 0, i = 21; c < 11; ++c, --i)
			INVADER_GRID[3][c] = i;

		for (int c = 0, i = 0; c < 11; ++c, ++i)
			INVADER_GRID[4][c] = i;
	}

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
			if(!i.mDestroyed)
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

	static bool canInvaderShoot(const std::vector<GameObjects::Invader>& pInvaders)
	{
		bool invaderCanShoot = true;
		// find invader
		for (int r = 0; r < 5; ++r)
		{
			for (int c = 0; c < 11; ++c)
			{
				if (INVADER_GRID[r][c] == INVADER_TO_UPDATE)
				{				
					if (r == 4)
					{
						return true;
					}

					// check invaders below to see if they are destroyed
					for (int r2 = r+1; r2 < 5; ++r2)
					{
						int index = INVADER_GRID[r2][c];
						invaderCanShoot &= pInvaders[index].mDestroyed;
					}
					return invaderCanShoot;
				}
			}
		}

		return false;
	}

	// -----------------------------------------------------------------------------

	static void updateInvaderShots(
		  GameObjects::Invader& pInvader
		, std::vector<GameObjects::InvaderShot>& pInvaderShots
		, const std::vector<GameObjects::Invader>& pInvaders
		, const float& pDeltaTime)
	{
		// a random invader will choose to shoot every second
		INVADER_SHOT_ELAPSED_TIME += pDeltaTime;
		if (INVADER_SHOT_ELAPSED_TIME >= 1 && pInvaderShots.size() < INVADER_MAX_SHOTS)
		{
			int shouldShoot = randint(1);
			if (canInvaderShoot(pInvaders))
			{
				pInvaderShots.push_back(GameObjects::InvaderShot(pInvader.mSprite.getPosition()));
			}
			INVADER_SHOT_ELAPSED_TIME = 0;
		}

		// move the shot down the screen
		for (int i = pInvaderShots.size() - 1; i >= 0; --i)
		{
			pInvaderShots[i].mInvaderShotRect.move(Vector2f(0, 4));

			if (pInvaderShots[i].mInvaderShotRect.getPosition().y >= (GameConstants::HEIGHT - GameConstants::BOT_BANNER))
			{
				pInvaderShots.erase(pInvaderShots.begin() + i);
			}
		}
	}

	// -----------------------------------------------------------------------------

	static void updateInvaders(std::vector<GameObjects::Invader>& pInvaders
		, std::vector<GameObjects::InvaderShot>& pInvaderShots
		, const float& pDeltaTime)
	{
		using namespace GameObjects;

		// invaders move in time from the bottom left-hand invader in a snake-like pattern
		// up to the top right-hand invader

		// all invaders must have moved in 55 frames (1 each)
		// this is why the invaders speed up as they are destroyed
		// as each invader can be updated more times in 1 second	

		// skip updating invaders that have been destroyed
		while (pInvaders[INVADER_TO_UPDATE].mDestroyed && INVADERS_DESTROYED < 55)
		{
			++INVADER_TO_UPDATE;
			if (INVADER_TO_UPDATE == pInvaders.size())
			{
				INVADER_TO_UPDATE = 0;
			}
		}

		Invader& invader = pInvaders[INVADER_TO_UPDATE];

		// allow the invader a chance to shoot if it's not blocked
		updateInvaderShots(invader, pInvaderShots, pInvaders, pDeltaTime);
		
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

			INVADER_TO_UPDATE = 0;
			return;
		}

		++INVADER_TO_UPDATE;
		if (INVADER_TO_UPDATE == pInvaders.size())
		{
			INVADER_TO_UPDATE = 0;
		}
	}

	// -----------------------------------------------------------------------------

	static void updatePlayerShot(GameObjects::PlayerShot& pShot, const float& pPlayerPosX, const float& pDeltaTime)
	{
		const bool s = Keyboard::isKeyPressed(Keyboard::S);
		if (s && !pShot.mShotsFired)
		{
			// ensure shot always spawns direct top-centre of the player
			pShot.mPlayerShotRect.setPosition(sf::Vector2f(pPlayerPosX - 2, PLAYER_Y - 12));
			pShot.mShotsFired = true;
		}

		// update it
		if (pShot.mShotsFired)
		{
			pShot.mPlayerShotRect.move(0, -(720 * pDeltaTime));

			// if it hits the top, remove it
			if (pShot.mPlayerShotRect.getPosition().y <= TOP_BANNER)
			{
				pShot.mPlayerShotRect.setPosition(sf::Vector2f(0, 0));
				pShot.mShotsFired = false;
			}
		}
	}

	// -----------------------------------------------------------------------------

	static void drawPlayerShot(const GameObjects::PlayerShot& pShot, sf::RenderWindow& pWindow)
	{
		if (pShot.mShotsFired)
		{
			pWindow.draw(pShot.mPlayerShotRect);
		}
	}

	// -----------------------------------------------------------------------------

	static void hasPlayerHitInvader(
		  GameObjects::PlayerShot& pShot
		, std::vector<GameObjects::Invader>& pInvaders
		, HUD& pGameHud)
	{
		// ignore the collision if the alien has already been destroyed
		// we don't remove sprites from the vector - just hide them
		for (GameObjects::Invader& i : pInvaders)
		{
			if (!i.mDestroyed && hasSpriteCollided(pShot.mPlayerShotRect, i.mSprite))
			{
				++INVADERS_DESTROYED;

				i.mDestroyed = true;

				// move the shot out of the way so it doesn't collide with other invaders
				pShot.mPlayerShotRect.setPosition(Vector2f(0, 0));
				pShot.mShotsFired = false;

				// increase the score
				switch (i.mType)
				{
				case GameObjects::InvaderType::eOCTOPUS:
					pGameHud.updatePlayer1Score(10);
					break;
				case GameObjects::InvaderType::eCRAB:
					pGameHud.updatePlayer1Score(20);
					break;
				case GameObjects::InvaderType::eSQUID:
					pGameHud.updatePlayer1Score(30);
					break;
				}
			}
		}
	}

	// -----------------------------------------------------------------------------

	static void drawInvaderShots(const std::vector<GameObjects::InvaderShot>& pInvaderShots, sf::RenderWindow& pWindow)
	{
		for (const GameObjects::InvaderShot& shot : pInvaderShots)
		{
			pWindow.draw(shot.mInvaderShotRect);
		}
	}
}

// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !GameConstants_H