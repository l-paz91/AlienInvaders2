// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "GameConstants.h"
#include "Invaders.h"
#include "TextureManager.h"

#include "Player.h"

// -----------------------------------------------------------------------------

namespace
{
	namespace PlayerPrivate
	{
		constexpr int PLAYER_Y = 648;
		constexpr int PLAYER_OFFSET = 20;
		constexpr int PLAYER_MINX = GameGlobals::LEFT_EDGE + PLAYER_OFFSET;
		constexpr int PLAYER_MAXX = GameGlobals::RIGHT_EDGE - PLAYER_OFFSET;
		constexpr int PLAYER_SPEED = 180;
	}
}

// -----------------------------------------------------------------------------

PlayerCannonShot::PlayerCannonShot()
	: mRect()
	, mShotFired(false)
{
	mRect.setSize(Vector2f(3.0f, 12.0f));
	mRect.setFillColor(Color::White);
}

// -----------------------------------------------------------------------------

void PlayerCannonShot::render(sf::RenderWindow& pWindow)
{
	if (mShotFired)
	{
		pWindow.draw(mRect);
	}
}

// -----------------------------------------------------------------------------

PlayerCannon::PlayerCannon()
	: mSprite(sf::Sprite(TextureManager::getTexture("Graphics/player.png")))
	, mPlayerCannonShot()
{
	mSprite.setOrigin(PlayerPrivate::PLAYER_OFFSET, 0);
	mSprite.setPosition(GameGlobals::HALFW, PlayerPrivate::PLAYER_Y);
}

// -----------------------------------------------------------------------------

void PlayerCannon::moveFromInput(const float& pDeltaTime)
{
	using namespace sf;
	using namespace PlayerPrivate;

	// player can only move on X axis
	const Vector2f& pos = mSprite.getPosition();

	const bool left = Keyboard::isKeyPressed(Keyboard::Left);
	const bool a = Keyboard::isKeyPressed(Keyboard::A);
	if (left || a)
	{
		if (!(pos.x <= PLAYER_MINX))
		{
			mSprite.move(-PLAYER_SPEED * pDeltaTime, 0);
		}
	}

	const bool right = Keyboard::isKeyPressed(Keyboard::Right);
	const bool d = Keyboard::isKeyPressed(Keyboard::D);
	if (right || d)
	{
		if (!(pos.x >= PLAYER_MAXX))
		{
			mSprite.move(PLAYER_SPEED * pDeltaTime, 0);
		}
	}
}

// -----------------------------------------------------------------------------

void PlayerCannon::render(sf::RenderWindow& pWindow)
{
	pWindow.draw(mSprite);
	mPlayerCannonShot.render(pWindow);
}

// -----------------------------------------------------------------------------

void PlayerCannon::shoot()
{
	using namespace sf;
	using namespace PlayerPrivate;

	const bool s = Keyboard::isKeyPressed(Keyboard::S);
	if (s && !mPlayerCannonShot.mShotFired)
	{
		// ensure shot always spawns direct top-centre of the player
		mPlayerCannonShot.mRect.setPosition(mSprite.getPosition().x - 2, PLAYER_Y - 12);
		mPlayerCannonShot.mShotFired = true;
	}

	// top hit?
	if (mPlayerCannonShot.mRect.getPosition().y <= GameGlobals::TOP_BANNER)
	{
		mPlayerCannonShot.mRect.setPosition(0, 0);	// move it out of the way of invaders
		mPlayerCannonShot.mShotFired = false;
	}
}

// -----------------------------------------------------------------------------

void PlayerCannon::updateCannonShot(const float& pDeltaTime)
{
	if (mPlayerCannonShot.mShotFired)
	{
		mPlayerCannonShot.mRect.move(0, -(720 * pDeltaTime));
	}
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------



