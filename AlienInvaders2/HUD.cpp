// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "GameConstants.h"
#include "TextureManager.h"

#include "HUD.h"

// -----------------------------------------------------------------------------

using namespace GameConstants;
using namespace sf;

// -----------------------------------------------------------------------------

namespace
{
	namespace HudPrivate
	{
		constexpr float TOP = 27.0f;
		constexpr float BOTTOM = HEIGHT - 24.0f;
	}
}

// -----------------------------------------------------------------------------

HUD::HUD()
	: mView(View(FloatRect(0.0f, 0.0f, WIDTH, HEIGHT)))
{
	using namespace HudPrivate;

	if (!mFont.loadFromFile("Fonts/space_invaders.ttf"))
	{
		std::cout << "Error loading HUD font." << std::endl;
	}

	setTextUp(mScoreP1text, Vector2f(LEFT_EDGE, TOP), "S C O R E< 1 >");
	setTextUp(mScoreP2text, Vector2f(459.0f, TOP), "S C O R E< 2 >");
	setTextUp(mHiScoreText, Vector2f(243.0f, TOP), "H I-S C O R E");
	setTextUp(mLivesText, Vector2f(LEFT_EDGE, 723.0f), "3");
	setTextUp(mCreditText, Vector2f(411.0f, 723.0f), "C R E D I T   0 0");

	setTextUp(mScore1, Vector2f(75.0f, 75.0f), "0000");
	mScore1.setLetterSpacing(4);

	setTextUp(mScore2, Vector2f(501.0f, 75.0f), "0 0 0 0");
	setTextUp(mHiScore, Vector2f(267.0f, 75.0f), "0 0 0 0");

	mGreenBar.setSize(Vector2f(WIDTH, 3.0f));
	mGreenBar.setFillColor(Color(82, 252, 82));
	mGreenBar.setPosition(Vector2f(0.0f, 717.0f));

	mLifeSprite1 = Sprite(TextureManager::getTexture("Graphics/player.png"));
	mLifeSprite1.setPosition(Vector2f(81.f, 720.0f));

	mLifeSprite2 = Sprite(TextureManager::getTexture("Graphics/player.png"));
	mLifeSprite2.setPosition(Vector2f(126.0f, 720.f));

	mScoreP1 = 0;
}

// -----------------------------------------------------------------------------

void HUD::update()
{
	// do stuff
}

// -----------------------------------------------------------------------------

void HUD::render(sf::RenderWindow& pWindow)
{
	// get the current view so we can set it back after
	View currentView = pWindow.getView();

	// set the view to the debug HUD
	pWindow.setView(mView);

	// now draw to the window
	pWindow.draw(mScoreP1text);
	pWindow.draw(mScoreP2text);
	pWindow.draw(mHiScoreText);
	pWindow.draw(mLivesText);
	pWindow.draw(mCreditText);

	pWindow.draw(mScore1);
	pWindow.draw(mScore2);
	pWindow.draw(mHiScore);

	pWindow.draw(mGreenBar);
	pWindow.draw(mLifeSprite1);
	pWindow.draw(mLifeSprite2);

	// set it back to the previous view
	pWindow.setView(currentView);
}

// -----------------------------------------------------------------------------

void HUD::setTextUp(Text& pText, const Vector2f& pPos, const std::string& pMsg /*=""*/)
{
	pText.setPosition(pPos);
	pText.setFont(mFont);
	pText.setCharacterSize(21);
	pText.setFillColor(Color::White);
	pText.setString(pMsg);
}

// -----------------------------------------------------------------------------

void HUD::updatePlayer1Score(int pScore)
{
	mScoreP1 += pScore;
	std::stringstream ss;
	ss << std::setfill('0') << std::setw(4) << mScoreP1;

	mScore1.setString(ss.str());
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------