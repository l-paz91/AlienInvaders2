// -----------------------------------------------------------------------------
#ifndef GameManager_H
#define GameManager_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "HUD.h"
#include "InvaderMissiles.h"
#include "Invaders.h"

// -----------------------------------------------------------------------------

struct GameManager
{
	GameManager();

	void InvaderTryShoot(const float& pDeltaTime);
	void moveMissiles();
	void missileCollisionCheck();
	void renderMissiles(sf::RenderWindow& pWindow);

	HUD mGameHUD;
	Invaders mInvaders;
	std::vector<InvaderMissile> mInvadersMissiles;

private:
	int mInvaderMaxShots;
	float mInvaderMissileElapsedTime;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !GameManager_H