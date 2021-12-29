// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "GameManager.h"

// -----------------------------------------------------------------------------

GameManager::GameManager()
	: mGameHUD()
	, mInvaders()
	, mPlayerCannon()
	, mInvadersMissiles()
	, mInvadersDestroyed(0)
	, mInvaderMaxShots(3)
	, mInvaderMissileElapsedTime(0.0f)
{

}

// -----------------------------------------------------------------------------

void GameManager::update(const float& pDeltaTime)
{
	// ---- UPDATE OBJECTS ----------------------------------------------------- //

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

			mInvaders.setNextInvaderToUpdate(mInvadersDestroyed);
		}
		else
		{
			mInvaders.updateDestroyedSprites(pDeltaTime);
		}
	}
	else
	{
		mPlayerCannon.updatePlayerDestroyedAnim(pDeltaTime);
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

	// has collided with barrier?

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
		// has collided with barrier?

		// has collided with player?
		if (hasSpriteCollided(missile.mMissile, mPlayerCannon.mSprite))
		{
			mGameHUD.updatePlayerLives();

			missile.mDestroyed = true;
			mPlayerCannon.mPlayerDestroyed = true;
		}

		// has collided with player cannon shot?

		// has collided with bottom screen edge?
	}
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------


