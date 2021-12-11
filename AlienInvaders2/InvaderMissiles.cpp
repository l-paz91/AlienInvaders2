// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "GameConstants.h"


#include "InvaderMissiles.h"

// -----------------------------------------------------------------------------

InvaderMissile::InvaderMissile(const sf::Vector2f& pPos)
	: mMissile()
	, mDestroyed(false)
{
	mMissile.setSize(sf::Vector2f(3.0f, 12.0f));
	mMissile.setFillColor(sf::Color::White);
	mMissile.setPosition(pPos.x + 16, pPos.y);
}

// -----------------------------------------------------------------------------

void InvaderMissile::moveMissile()
{
	mMissile.move(0, 4.0f);
}

// -----------------------------------------------------------------------------

void InvaderMissile::checkForCollisions()
{
	// did it hit the bottom banner?
	if (mMissile.getPosition().y >= (GameGlobals::HEIGHT - GameGlobals::BOT_BANNER))
	{
		mDestroyed = true;
		return;
	}

	// did it hit a barrier?

	// did it hit the player?

	// did it hit a player shot?
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------


