// -----------------------------------------------------------------------------
#ifndef InvaderMissiles_H
#define InvaderMissiles_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <SFML/Graphics.hpp>

// -----------------------------------------------------------------------------

enum InvaderMissileType
{
	eROLLING,	// slowest, least powerful - targets player
	ePLUNGER,	// faster, more powerful   - disabled when only 1 invader left
	eZIGZAG		// most powerful		   - disabled when flying saucer is on screen
};

// -----------------------------------------------------------------------------

struct InvaderMissile
{
	InvaderMissile(const sf::Vector2f& pPos);

	void moveMissile();
	void checkForCollisions();

	sf::RectangleShape mMissile;
	bool mDestroyed;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !InvaderMissiles_H