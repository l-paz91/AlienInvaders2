// -----------------------------------------------------------------------------
#ifndef Player_H
#define Player_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <SFML/Graphics.hpp>

// -----------------------------------------------------------------------------

struct PlayerCannonShot
{
	PlayerCannonShot();

	void render(sf::RenderWindow& pWindow);

	sf::RectangleShape mRect;
	bool mShotFired;
};

// -----------------------------------------------------------------------------

struct PlayerCannon
{
	PlayerCannon();

	void moveFromInput(const float& pDeltaTime);
	void render(sf::RenderWindow& pWindow);

	const sf::Vector2f& getPos() const { mSprite.getPosition(); }

	void shoot();
	void updateCannonShot(const float& pDeltaTime);
	void updatePlayerDestroyedAnim(const float& pDeltaTime);

	sf::Sprite mSprite;
	PlayerCannonShot mPlayerCannonShot;

	int mLives;
	int mHoldForFrames;
	float mTimeElapsedForDestroyedSprite;
	bool mPlayerDestroyed;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !Player_H