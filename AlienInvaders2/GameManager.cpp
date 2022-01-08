// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "GameConstants.h"

#include "GameManager.h"

// -----------------------------------------------------------------------------

GameManager::GameManager()
	: mGameHUD()
	, mInvaders()
	, mPlayerCannon()
	, mInvadersMissiles()
	, mShields()
	, mInvadersDestroyed(0)
	, mInvaderMaxShots(3)
	, mInvaderMissileElapsedTime(0.0f)
	, mPauseElapsedTime(0.0f)
	, mGameState(GameState::eTITLE)
{
	init();
}

// -----------------------------------------------------------------------------

void GameManager::init()
{
	mGameHUD.init();
	mInvaders.init();
	mPlayerCannon.init();
	mInvadersMissiles.clear();
	mInvadersDestroyed = 0;
	mInvaderMissileElapsedTime = 0.0f;
	mPauseElapsedTime = 0.0f;
	mGameState = GameState::ePLAYING;
}

// -----------------------------------------------------------------------------

void GameManager::update(const float& pDeltaTime)
{
	using namespace sf;
	// ---- UPDATE OBJECTS ----------------------------------------------------- //
	switch (mGameState)
	{
	case GameState::eTITLE:
	{
		mGameHUD.updateTitleScreenMessages(pDeltaTime);

		// has 1 been pressed? If so, start the game
		const bool num1Key = Keyboard::isKeyPressed(Keyboard::Num1);
		if (num1Key)
		{
			init();
			mGameState = GameState::ePLAYING;
		}
		break;
	}
	case GameState::eINSTRUCTIONS:
		break;
	case GameState::ePLAYING:
	{
		// the game "freezes" whilst the players destroyed animation is playing
		if (!mPlayerCannon.mPlayerDestroyed)
		{
			mPlayerCannon.moveFromInput(pDeltaTime);
			mPlayerCannon.updateCannonShot(pDeltaTime);
			hasPlayerCannonShotCollided();

			// invaders don't move whilst they are being destroyed & the player can't shoot
			// until it's finished
			if (mInvaders.mDestroyedSprites.empty())
			{
				mPlayerCannon.shoot();

				mInvaders.moveAndAnimate(pDeltaTime);
				InvaderTryShoot(pDeltaTime);
				updateMissiles();
				hasInvaderMissileCollided();
				hasInvaderCollidedWithShield();

				// it's about to hit player
				Invader& invader = mInvaders.getCurrentInvader();
				if (!invader.mDestroyed && invader.mSprite.getPosition().y > 621)
				{
					if (hasSpriteCollided(invader.mSprite, mPlayerCannon.mSprite))
					{
						mPlayerCannon.mPlayerDestroyed;
						mPlayerCannon.mLives = 0;
						mGameHUD.updatePlayerLives(0);
					}
				}

				mInvaders.setNextInvaderToUpdate(mInvadersDestroyed);
			}
			else
			{
				mInvaders.updateDestroyedSprites(pDeltaTime);
			}
		}
		else
		{
			if (mPlayerCannon.updatePlayerDestroyedAnim(pDeltaTime))
			{
				if (mPlayerCannon.mLives == 0)
				{
					// game over
					mGameState = GameState::eGAMEOVER;
					mGameHUD.mDisplayGameover = true;
				}
			}	
		}
		break;
	}
	case GameState::eGAMEOVER:
	{
		if (!mGameHUD.updateGameoverText())
		{
			mGameState = GameState::eTITLE;
		}
		break;
	}
	case GameState::ePAUSE:
	{
		
		break;
	}
	default:
		break;
	}
}

// -----------------------------------------------------------------------------

void GameManager::render(sf::RenderWindow& pWindow)
{
	switch (mGameState)
	{
	case GameState::eTITLE: 
	{
		mGameHUD.renderTitleScreen(pWindow);
		break;
	}
	case GameState::eINSTRUCTIONS: 
	{


		break;
	}
	case GameState::ePLAYING: 
	{
		// ---- RENDER OBJECTS --------------------------------------------- //
		mShields.render(pWindow);
		mPlayerCannon.render(pWindow);
		mInvaders.render(pWindow);
		renderMissiles(pWindow);

		// ---- RENDER HUD ------------------------------------------------- //
		mGameHUD.render(pWindow);
		break;
	}
	case GameState::eGAMEOVER: 
	{

		break;
	}
	case GameState::ePAUSE: 
	{

		break;
	}
	default:
		break;
	}
}

// -----------------------------------------------------------------------------

void GameManager::InvaderTryShoot(const float& pDeltaTime)
{
	mInvaderMissileElapsedTime += pDeltaTime;
	if (mInvaders.canShoot())
	{
		// currently an invader will choose to shoot every second
		if (mInvaderMissileElapsedTime >= 1.0f && (int)mInvadersMissiles.size() <= mInvaderMaxShots)
		{
			mInvadersMissiles.push_back(InvaderMissile(mInvaders.getPosOfCurrentInvader()));
			mInvaderMissileElapsedTime = 0.0f;
		}
	}

	return;
}

// -----------------------------------------------------------------------------

void GameManager::updateMissiles()
{
	for (auto& missile : mInvadersMissiles)
	{
		missile.updateMissile();
	}

	cleanUpMissiles();
}

// -----------------------------------------------------------------------------

void GameManager::cleanUpMissiles()
{
	for (int i = mInvadersMissiles.size()-1; i >= 0; --i)
	{
		if (mInvadersMissiles[i].mDestroyed)
		{
			mInvadersMissiles.erase(mInvadersMissiles.begin() + i);
		}
	}
}

// -----------------------------------------------------------------------------

void GameManager::renderMissiles(sf::RenderWindow& pWindow)
{
	for (auto& missile : mInvadersMissiles)
	{
		pWindow.draw(missile.mMissile);
	}
}

// -----------------------------------------------------------------------------

void GameManager::hasPlayerCannonShotCollided()
{
	PlayerCannonShot& playerShot = mPlayerCannon.mPlayerCannonShot;

	// has collided with shield?
	for (sf::Sprite shield : mShields.mSprites)
	{
		if (hasSpriteCollided(playerShot.mRect, shield))
		{
			// check for general collision so we can go in and do per-pixel if needed
			if (perPixelCollision(false, playerShot.mRect, shield, mShields.mRenderImage))
			{
				const Vector2f& pos = playerShot.mRect.getPosition();

				// little random offsets to the shot
				int randX = GameGlobals::randint(-2, 2);
				Vector2f p(pos.x + randX, pos.y - 10);
				mShields.shieldHit(p);

				// move player shot out of the way of other invaders
				playerShot.mRect.setPosition(0, 0);
				mPlayerCannon.setCooldown();
				return;
			}
		}
	}

	// has collided with flying saucer?

	// has collided with top of screen?

	// has collided with invader?
	// ignore the collision if the alien has already been destroyed
	// we don't remove sprites from the vector - just hide them
	for (auto& row : mInvaders.mInvaders)
	{
		for (auto& invader : row)
		{
			if (!invader.mDestroyed && hasSpriteCollided(playerShot.mRect, invader.mSprite))
			{
				++mInvadersDestroyed;
				invader.mDestroyed = true;
				mInvaders.invaderDestroyedEvent(invader);

				// move player shot out of the way of other invaders
				playerShot.mRect.setPosition(0, 0);
				playerShot.mShotFired = false;

				// increase the score
				switch (invader.mType)
				{
				case InvaderType::eOCTOPUS:
					mGameHUD.updatePlayer1Score(10);
					break;
				case InvaderType::eCRAB:
					mGameHUD.updatePlayer1Score(20);
					break;
				case InvaderType::eSQUID:
					mGameHUD.updatePlayer1Score(30);
					break;
				}

				return;
			}
		}
	}
}

// -----------------------------------------------------------------------------

void GameManager::hasInvaderMissileCollided()
{
	for (InvaderMissile& missile : mInvadersMissiles)
	{
		sf::RectangleShape& m = missile.mMissile;

		// has collided with shield?
		for (sf::Sprite shield : mShields.mSprites)
		{
			// check for general collision so we can go in and do per-pixel if needed
			if (hasSpriteCollided(m, shield))
			{
				if (perPixelCollision(true, m, shield, mShields.mRenderImage))
				{
					mShields.shieldHit(m.getPosition());

					missile.mDestroyed = true;
					break;
				}
			}
		}

		// has collided with player?
		if (hasSpriteCollided(m, mPlayerCannon.mSprite))
		{
			mGameHUD.updatePlayerLives(--mPlayerCannon.mLives);

			missile.mDestroyed = true;
			mPlayerCannon.mPlayerDestroyed = true;
			break;
		}

		// has collided with player cannon shot?

		// has collided with bottom screen edge?
	}
}

// -----------------------------------------------------------------------------

void GameManager::hasInvaderCollidedWithShield()
{
	Invader& invader = mInvaders.getCurrentInvader();
	if (invader.mSprite.getPosition().y > 552)
	{
		// start destroying shields
		for (sf::Sprite shield : mShields.mSprites)
		{
			if (!invader.mDestroyed && hasSpriteCollided(invader.mSprite, shield))
			{
				mShields.shieldHit(invader.mSprite.getPosition());
				return;
			}
		}
	}
}

// -----------------------------------------------------------------------------

// this is extremely hardcoded to this specific scenario
bool GameManager::perPixelCollision(bool pIsInvaderMissile, sf::RectangleShape& pRectShape, sf::Sprite& pSprite, const sf::Image& pSpriteImage)
{
	using namespace sf;
	Vector2i laserPos;

	if (pIsInvaderMissile)
	{
		// use bottom on the rect
		Vector2i temp = (Vector2i)pRectShape.getPosition();
		laserPos = Vector2i(temp.x, temp.y + 12);
	}
	else
	{
		// returns top left of rect
		laserPos = (Vector2i)pRectShape.getPosition();
	}

	// has the laser hit a solid pixel - I'm using a few different points on the laser
	// due to multiplying all the pixels by 3 to "size" the game up
	Color pixel = pSpriteImage.getPixel(laserPos.x, laserPos.y);
	Color pixel2 = pSpriteImage.getPixel(laserPos.x + 2, laserPos.y);
	Color pixel3 = pSpriteImage.getPixel(laserPos.x, laserPos.y - 5);
	if (pixel.a == 0 && pixel2.a == 0 && pixel3.a == 0)
	{
		return false;
	}

	return true;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------


