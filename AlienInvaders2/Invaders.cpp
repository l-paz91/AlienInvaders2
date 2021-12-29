// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <string>

#include "GameConstants.h"
#include "TextureManager.h"

#include "Invaders.h"

// -----------------------------------------------------------------------------

namespace
{
	namespace InvadersPrivate
	{
		const std::string textureFilename = "Graphics/InvaderSpritesheet.png";

		constexpr int ROWS = 5;
		constexpr int COLUMNS = 11;
		constexpr int INVADER_XSTART = 75;
		constexpr int INVADER_YSTART = 384;
		constexpr int INVADER_MAX_SHOTS = 3;
		constexpr int INVADER_SIZE = 48;

		// offsets for textures in sprite sheet
		const sf::IntRect octopus1 = sf::IntRect(0, 0, 36, 24);
		const sf::IntRect octopus2 = sf::IntRect(36, 0, 36, 24);

		const sf::IntRect crab1 = sf::IntRect(0, 24, 32, 24);
		const sf::IntRect crab2 = sf::IntRect(36, 24, 32, 24);

		const sf::IntRect squid1 = sf::IntRect(0, 48, 24, 24);
		const sf::IntRect squid2 = sf::IntRect(36, 48, 24, 24);

		const sf::IntRect destroyed = sf::IntRect(0, 72, 32, 24);
	}
}

// -----------------------------------------------------------------------------

Invader::Invader()
	: mSprite(sf::Sprite(TextureManager::getTexture(InvadersPrivate::textureFilename)))
	, mType(InvaderType::eOCTOPUS)
	, mDestroyed(false)
	, mFlipAnimation(true)
{}

// -----------------------------------------------------------------------------

void Invader::animate()
{
	using namespace InvadersPrivate;

	switch (mType)
	{
	case InvaderType::eOCTOPUS:
		if (mFlipAnimation)
			mSprite.setTextureRect(octopus2);
		else
			mSprite.setTextureRect(octopus1);
		break;
	case InvaderType::eCRAB:
		if (mFlipAnimation)
			mSprite.setTextureRect(crab2);
		else
			mSprite.setTextureRect(crab1);
		break;
	case InvaderType::eSQUID:
		if (mFlipAnimation)
			mSprite.setTextureRect(squid2);
		else
			mSprite.setTextureRect(squid1);
		break;
	default:
		break;
	}

	mFlipAnimation = !mFlipAnimation;
}

// -----------------------------------------------------------------------------

Invaders::Invaders()
	: mInvaders(InvadersPrivate::ROWS, std::vector<Invader>(InvadersPrivate::COLUMNS))
	, mInvaderToUpdateRow(0)
	, mInvaderToUpdateColumn(0)
	, mInvaderSpeed(6)
	, mEdgeHitFlag(false)
{

	init();
}

// -----------------------------------------------------------------------------

void Invaders::init()
{
	using namespace InvadersPrivate;

	float x = INVADER_XSTART;
	float y = INVADER_YSTART;

	// as the bottom left invader is the "reference" that all other invaders follow
	// this array is "upside down" with row 0 being the bottom row of invaders and
	// row 4 being the top row of invaders to make iteration through the array easier

	// rows 5 & 4 - octopus
	for (int r = 0; r < 2; ++r)
	{
		for (int c = 0; c < COLUMNS; ++c)
		{
			mInvaders[r][c].mSprite.setTextureRect(octopus2);
			mInvaders[r][c].mSprite.setPosition(Vector2f(x, y));
			x += INVADER_SIZE;
		}

		y -= INVADER_SIZE;
		x = INVADER_XSTART;
	}

	// rows 3 & 2 - crab
	for (int r = 2; r < 4; ++r)
	{
		for (int c = 0; c < COLUMNS; ++c)
		{
			mInvaders[r][c].mType = InvaderType::eCRAB;
			mInvaders[r][c].mSprite.setTextureRect(crab2);
			mInvaders[r][c].mSprite.setPosition(Vector2f(x, y));
			x += INVADER_SIZE;
		}

		y -= INVADER_SIZE;
		x = INVADER_XSTART;
	}

	// row 5 - squid
	for (int c = 0; c < COLUMNS; ++c)
	{
		mInvaders[4][c].mType = InvaderType::eSQUID;
		mInvaders[4][c].mSprite.setTextureRect(squid2);
		mInvaders[4][c].mSprite.setPosition(Vector2f(x, y));
		x += INVADER_SIZE;
	}
}

// -----------------------------------------------------------------------------

void Invaders::moveAndAnimate(const float& pDeltaTime)
{
	// invaders move in time from the bottom left-hand invader up to the top 
	// right-hand invader

	// all invaders must have moved in 55 frames (1 each)
	// this is why the invaders speed up as they are destroyed
	// as each invader can be updated more times in 1 second

	Invader& invader = mInvaders[mInvaderToUpdateRow][mInvaderToUpdateColumn];

	// move it over
	invader.mSprite.move((float)mInvaderSpeed, 0);

	invader.animate();

	// check to see if an invader has hit an edge
	const float x = invader.mSprite.getPosition().x;
	if (x <= GameGlobals::LEFT_EDGE || x >= GameGlobals::RIGHT_EDGE - InvadersPrivate::INVADER_SIZE)
	{
		mEdgeHitFlag = true;
	}
}

// -----------------------------------------------------------------------------

bool Invaders::canShoot()
{
	Invader& invader = mInvaders[mInvaderToUpdateRow][mInvaderToUpdateColumn];

	if (invader.mDestroyed)
	{
		return false;
	}

	if (mInvaderToUpdateRow == 0)
	{
		return true;
	}

	bool invaderCanShoot = true;

	// an invader can only shoot if there is nothing below it
	for (int row = mInvaderToUpdateRow - 1; row >= 0; --row)
	{
		// as this is a loop, if it becomes false, &= won't change it back to true again
		invaderCanShoot &= mInvaders[row][mInvaderToUpdateColumn].mDestroyed;
	}

	return invaderCanShoot;
}

// -----------------------------------------------------------------------------

void Invaders::setNextInvaderToUpdate(const int& pInvadersDestroyed)
{
	do
	{
		// move to the next invader
		++mInvaderToUpdateColumn;
		if (mInvaderToUpdateColumn == 11)
		{
			mInvaderToUpdateColumn = 0;
			++mInvaderToUpdateRow;

			if (mInvaderToUpdateRow == 5)
			{
				// now all invaders have been updated, drop a row if needed
				if (mEdgeHitFlag)
				{
					dropInvaders();
					mEdgeHitFlag = false;
				}

				mInvaderToUpdateRow = 0;
			}
		}	
	} while (getCurrentInvader().mDestroyed && pInvadersDestroyed < 55);
}

// -----------------------------------------------------------------------------

void Invaders::render(sf::RenderWindow& pWindow)
{
	for (const auto& row : mInvaders)
	{
		for (const auto& invader : row)
		{
			if (!invader.mDestroyed)
			{
				pWindow.draw(invader.mSprite);
			}
		}
	}
}

// -----------------------------------------------------------------------------

void Invaders::dropInvaders()
{
	// we need to wait until all the invaders have been updated before dropping
	// them down a row to keep them in sync

	for (auto& row : mInvaders)
	{
		for (auto& i : row)
		{
			i.mSprite.move(0, 24);
		}
	}

	// set reverse speed
	mInvaderSpeed *= -1;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------



