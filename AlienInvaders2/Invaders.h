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
	void move(float x, float y);

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
	void update(const float& pDeltaTime);
	void render(sf::RenderWindow& pWindow);

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