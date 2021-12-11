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

	void animate();

	sf::Sprite mSprite;
	InvaderType mType;
	bool mDestroyed;
	bool mFlipAnimation;
};

// -----------------------------------------------------------------------------

struct Invaders
{
	Invaders();

	void init();
	void moveAndAnimate(const float& pDeltaTime);
	bool canShoot();
	void checkForCollisions();
	void setNextInvaderToUpdate();

	void render(sf::RenderWindow& pWindow);

	const sf::Vector2f& getPosOfCurrentInvader() { return mInvaders[mInvaderToUpdateRow][mInvaderToUpdateColumn].mSprite.getPosition(); }

private:
	void dropInvaders();

	std::vector<std::vector<Invader>> mInvaders;

	int mInvaderToUpdateRow;
	int mInvaderToUpdateColumn;
	int mInvaderSpeed;

	bool mEdgeHitFlag;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !Invaders_H