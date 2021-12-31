// -----------------------------------------------------------------------------
#ifndef GameManager_H
#define GameManager_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "HUD.h"
#include "InvaderMissiles.h"
#include "Invaders.h"
#include "Player.h"

// -----------------------------------------------------------------------------

enum class GameState
{
	eTITLE,
	eINSTRUCTIONS,
	ePLAYING,
	eGAMEOVER,
	ePAUSE
};

// -----------------------------------------------------------------------------

struct GameManager
{
	GameManager();

	void init();
	void update(const float& pDeltaTime);
	void render(sf::RenderWindow& pWindow);

	void InvaderTryShoot(const float& pDeltaTime);
	void updateMissiles();
	void cleanUpMissiles();
	void renderMissiles(sf::RenderWindow& pWindow);

	void hasPlayerCannonShotCollided();
	void hasInvaderMissileCollided();

	HUD mGameHUD;
	Invaders mInvaders;
	PlayerCannon mPlayerCannon;
	std::vector<InvaderMissile> mInvadersMissiles;

	int mInvadersDestroyed;

private:
	template<typename T1, typename T2>
	bool hasSpriteCollided(const T1& pType1, const T2& pType2)
	{
		return pType1.getGlobalBounds().intersects(pType2.getGlobalBounds());
	}

	int mInvaderMaxShots;
	float mInvaderMissileElapsedTime;
	float mPauseElapsedTime;
	GameState mGameState;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !GameManager_H