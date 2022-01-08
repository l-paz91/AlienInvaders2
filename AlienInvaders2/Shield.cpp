// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "GameConstants.h"
#include "TextureManager.h"

#include "Shield.h"
// -----------------------------------------------------------------------------

Shields::Shields()
	: mShotMask(Sprite(TextureManager::getTexture("Graphics/InvaderSpritesheet.png")))
{
	mRenderTarget.create(GameGlobals::WIDTH, GameGlobals::HEIGHT);

	init();
}

// -----------------------------------------------------------------------------

void Shields::init()
{
	using namespace sf;

	const std::string textureFilename = "Graphics/Shield&SaucerSpriteSheet.png";

	// offset for texture in sprite sheet
	const IntRect shield = IntRect(0, 0, 66, 48);

	// I don't really need to use sprites for this as the shields aren't going anywhere...
	// but for such a small game, I like being able to think about them individually
	Sprite shield1(Sprite(TextureManager::getTexture(textureFilename)));
	shield1.setPosition(Vector2f(96, 576));
	shield1.setTextureRect(shield);

	Sprite shield2(Sprite(TextureManager::getTexture(textureFilename)));
	shield2.setPosition(Vector2f(231, 576));
	shield2.setTextureRect(shield);

	Sprite shield3(Sprite(TextureManager::getTexture(textureFilename)));
	shield3.setPosition(Vector2f(366, 576));
	shield3.setTextureRect(shield);

	Sprite shield4(Sprite(TextureManager::getTexture(textureFilename)));
	shield4.setPosition(Vector2f(501, 576));
	shield4.setTextureRect(shield);

	if (!mSprites.empty())
	{
		mSprites.clear();
	}

	mSprites.push_back(shield1);
	mSprites.push_back(shield2);
	mSprites.push_back(shield3);
	mSprites.push_back(shield4);

	// set up the render texture - this will be used to hold the modified sprite textures
	mRenderTarget.clear(Color(0, 0, 0, 0));
	for (const sf::Sprite& shield : mSprites)
	{
		mRenderTarget.draw(shield);
	}
	mRenderTarget.display();

	// now the initial sprites have been drawn to the render target, we need to
	// set the sprites textures to the render target
	const Texture& t = mRenderTarget.getTexture();

	mSprites[0].setTexture(t);
	mSprites[0].setTextureRect(IntRect(96, 576, 66, 48));

	mSprites[1].setTexture(t);
	mSprites[1].setTextureRect(IntRect(231, 576, 66, 48));

	mSprites[2].setTexture(t);
	mSprites[2].setTextureRect(IntRect(366, 576, 66, 48));

	mSprites[3].setTexture(t);
	mSprites[3].setTextureRect(IntRect(501, 576, 66, 48));

	// set up the renderImage - this will be used to grab and change individual pixels
	// to send back to the RenderTarget
	// copyToImage() is very slow, but this is a small game, so it doesn't really matter
	mRenderImage = t.copyToImage();

	// set up the shot mask - this will be used to create the "disintegration" effect
	mShotMask.setTextureRect(IntRect(42, 72, 18, 24));
}

// -----------------------------------------------------------------------------

void Shields::shieldHit(const sf::Vector2f& pPos)
{
	using namespace sf;

	mShotMask.setPosition(pPos);

	mRenderTarget.draw(mShotMask, BlendMultiply);
	mRenderTarget.display();

	// update the render image for future per-pixel collisions
	mRenderImage = mRenderTarget.getTexture().copyToImage();
}

// -----------------------------------------------------------------------------

void Shields::render(sf::RenderWindow& pWindow) const
{
	for (const sf::Sprite& shield : mSprites)
	{
		pWindow.draw(shield);
	}
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------


