// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "GameConstants.h"
#include "TextureManager.h"

#include "FlyingSaucer.h"

// -----------------------------------------------------------------------------

namespace
{
	namespace UFOPrivate
	{
		const sf::IntRect ufoOffset = sf::IntRect(0, 48, 48, 20);
		const sf::IntRect ufoDestroyedOffset = sf::IntRect(0, 72, 66, 20);
		const float timeToWait = 5.0f;
		constexpr int ufoLevelY = 130;
	}
}

FlyingSaucer::FlyingSaucer()
	: mSprite(TextureManager::getTexture("Graphics/Shield&SaucerSpriteSheet.png"), UFOPrivate::ufoOffset)
	, mTimeUntilSaucer(0.0f)
	, mSpeed(120.0f)
	, mDestroyed(false)
	, mDisplaySaucer(false)
	, mShowText(false)
{
	if (!mFont.loadFromFile("Fonts/space_invaders.ttf"))
	{
		std::cout << "Error loading HUD font." << std::endl;
	}

	mScore.setPosition(0,0);
	mScore.setFont(mFont);
	mScore.setCharacterSize(21);
	mScore.setFillColor(Color::White);
	mScore.setString("");
}

// -----------------------------------------------------------------------------

void FlyingSaucer::init()
{
	mTimeUntilSaucer = 0.0f;
	mDestroyed = false;
	mDisplaySaucer = false;
	mShowText = false;

	mSprite.setPosition(-40, -40);
}

// -----------------------------------------------------------------------------

void FlyingSaucer::update(const float& pDeltaTime, bool pDirection)
{
	// if it's not on the screen, update time to display
	if (!mDisplaySaucer)
	{
		mTimeUntilSaucer += pDeltaTime;

		if (mTimeUntilSaucer >= UFOPrivate::timeToWait)
		{
			mTimeUntilSaucer = 0.0f;
			mDisplaySaucer = true;

			// the saucers direction is determined by the last bit of the number of
			// shots by the player. So if 1 or 0 (odd or even)
			if (pDirection)
			{
				// start from right and go left
				mSprite.setPosition(GameGlobals::RIGHT_EDGE-49, UFOPrivate::ufoLevelY);
				mSpeed = -120;
			}
			else
			{
				// start from left and go right
				mSprite.setPosition(GameGlobals::LEFT_EDGE, UFOPrivate::ufoLevelY);
				mSpeed = 120;
			}
		}
	}
	// it's on the screen, move it or update destroyed sequence
	else
	{
		// has saucer been hit?
		if (mDestroyed)
		{
			// switch sprites and display for 2 seconds
			mSprite.setTextureRect(UFOPrivate::ufoDestroyedOffset);
			mTimeUntilSaucer += pDeltaTime;
			if (mTimeUntilSaucer > 1.0f)
			{
				mDestroyed = false;
				mShowText = true;
				mTimeUntilSaucer = 0.0f;
			}

			return;
		}
		
		if (mShowText)
		{
			mTimeUntilSaucer += pDeltaTime;
			if (mTimeUntilSaucer > 1.5f)
			{
				mShowText = false;
				mDisplaySaucer = false;
				mSprite.setPosition(-40, -40);
				mTimeUntilSaucer = 0.0f;
				mSprite.setTextureRect(UFOPrivate::ufoOffset);
			}

			return;
		}

		mSprite.move(mSpeed*pDeltaTime, 0);	

		// reached edge of screen?
		if (mSprite.getPosition().x > GameGlobals::RIGHT_EDGE - 48
			|| mSprite.getPosition().x < GameGlobals::LEFT_EDGE)
		{
			mDisplaySaucer = false;
			mSprite.setPosition(-40, -40);
		}
	}
}

// -----------------------------------------------------------------------------

void FlyingSaucer::render(sf::RenderWindow& pWindow)
{
	if (mDisplaySaucer && !mShowText)
	{
		pWindow.draw(mSprite);
	}
	
	if (mShowText)
	{
		pWindow.draw(mScore);
	}
}

// -----------------------------------------------------------------------------

void FlyingSaucer::setUfoScore(int pScore, const sf::Vector2f& pPos)
{
	mScore.setString(std::to_string(pScore));
	mScore.setPosition(pPos);
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------


