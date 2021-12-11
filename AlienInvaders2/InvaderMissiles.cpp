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

void InvaderMissile::updateMissile()
{
	mMissile.move(0, 4.0f);

	// did it hit the bottom banner?
	if (mMissile.getPosition().y >= (GameGlobals::HEIGHT - GameGlobals::BOT_BANNER))
	{
		mDestroyed = true;
	}
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------


