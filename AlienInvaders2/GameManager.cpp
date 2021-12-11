// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "GameManager.h"

// -----------------------------------------------------------------------------

GameManager::GameManager()
	: mGameHUD()
	, mInvaders()
	, mInvadersMissiles()
	, mInvaderMaxShots(3)
	, mInvaderMissileElapsedTime(0.0f)
{

}

// -----------------------------------------------------------------------------

void GameManager::InvaderTryShoot(const float& pDeltaTime)
{
	mInvaderMissileElapsedTime += pDeltaTime;
	if (mInvaders.canShoot())
	{
		// currently a random invader will choose to shoot every second
		if (mInvaderMissileElapsedTime >= 1 && (int)mInvadersMissiles.size() < mInvaderMaxShots)
		{
			mInvadersMissiles.push_back(InvaderMissile(mInvaders.getPosOfCurrentInvader()));
			mInvaderMissileElapsedTime = 0.0f;
		}
	}

	return;
}

// -----------------------------------------------------------------------------

void GameManager::moveMissiles()
{
	for (auto& missile : mInvadersMissiles)
	{
		missile.moveMissile();
	}
}

// -----------------------------------------------------------------------------

void GameManager::missileCollisionCheck()
{
	for (int i = mInvadersMissiles.size()-1; i >= 0; --i)
	{
		mInvadersMissiles[i].checkForCollisions();
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
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------


