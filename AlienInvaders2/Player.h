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

	void init();
	void moveFromInput(const float& pDeltaTime);
	void render(sf::RenderWindow& pWindow);

	const sf::Vector2f& getPos() const { mSprite.getPosition(); }

	bool shoot();
	void updateCannonShot(const float& pDeltaTime);
	bool updatePlayerDestroyedAnim(const float& pDeltaTime);
	void setCooldown();

	sf::Sprite mSprite;
	PlayerCannonShot mPlayerCannonShot;

	int mLives;
	int mHoldForFrames;
	int mCooldown;
	float mTimeElapsedForDestroyedSprite;
	bool mPlayerDestroyed;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !Player_H