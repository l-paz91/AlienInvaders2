// -----------------------------------------------------------------------------
#ifndef Invaders_H
#define Invaders_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <SFML/Graphics.hpp>

#include <vector>

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
	Invader();

	void init() { mDestroyed = false; mFlipAnimation = true; }
	void animate();

	sf::Sprite mSprite;
	InvaderType mType;
	bool mDestroyed;
	bool mFlipAnimation;
};

// -----------------------------------------------------------------------------

struct DestroyedEvent
{
	DestroyedEvent() : mSprite(), mElapsedTime(0.0f) {}

	sf::Sprite mSprite;
	float mElapsedTime;
};

// -----------------------------------------------------------------------------

struct Invaders
{
	Invaders();

	void init();
	void moveAndAnimate(const float& pDeltaTime);
	void updateDestroyedSprites(const float& pDeltaTime);
	bool canShoot();
	void setNextInvaderToUpdate(const int& pInvadersDestroyed);

	void render(sf::RenderWindow& pWindow);
	void invaderDestroyedEvent(const Invader& pInvader);

	Invader& getCurrentInvader() { return mInvaders[mInvaderToUpdateRow][mInvaderToUpdateColumn]; }
	const sf::Vector2f& getPosOfCurrentInvader() const { return mInvaders[mInvaderToUpdateRow][mInvaderToUpdateColumn].mSprite.getPosition(); }

	std::vector<std::vector<Invader>> mInvaders;
	std::vector<DestroyedEvent> mDestroyedSprites;
private:
	void dropInvaders();

	int mInvaderToUpdateRow;
	int mInvaderToUpdateColumn;
	int mInvaderSpeed;

	bool mEdgeHitFlag;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !Invaders_H