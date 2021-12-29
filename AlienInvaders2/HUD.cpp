// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "GameConstants.h"
#include "TextureManager.h"

#include "HUD.h"

// -----------------------------------------------------------------------------

using namespace GameGlobals;
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
	init();
}

// -----------------------------------------------------------------------------

void HUD::init()
{
	using namespace HudPrivate;

	mGameover = "GAME OVER";
	mScoreP1 = 0;
	mHoldForFrames = 0;
	mIndex = 0;
	mDisplayGameover = false;

	if (!mFont.loadFromFile("Fonts/space_invaders.ttf"))
	{
		std::cout << "Error loading HUD font." << std::endl;
	}

	setTextUp(mScoreP1text, Vector2f(LEFT_EDGE, TOP), "S C O R E< 1 >");
	setTextUp(mScoreP2text, Vector2f(459.0f, TOP), "S C O R E< 2 >");
	setTextUp(mHiScoreText, Vector2f(243.0f, TOP), "H I-S C O R E");

	setTextUp(mCreditText, Vector2f(411.0f, 723.0f), "C R E D I T   0 0");

	setTextUp(mScore1, Vector2f(75.0f, 75.0f), "0000");
	mScore1.setLetterSpacing(4);

	setTextUp(mScore2, Vector2f(501.0f, 75.0f), "0 0 0 0");

	// read in HI SCORE from text file
	std::ifstream readIn{ "Scores/HiScores.txt" };
	if (!readIn)
	{
		std::cout << "Error opening hi scores file in HUD::init()";
	}
	int s;
	readIn >> s;
	std::stringstream ss;
	ss << std::setfill('0') << std::setw(4) << s;

	mHiScore.setLetterSpacing(4);
	setTextUp(mHiScore, Vector2f(267.0f, 75.0f), ss.str());

	setTextUp(mGameOverText, Vector2f(120.0f, 150.0f));
	mGameOverText.setLetterSpacing(4);

	mGreenBar.setSize(Vector2f(WIDTH, 3.0f));
	mGreenBar.setFillColor(Color(82, 252, 82));
	mGreenBar.setPosition(Vector2f(0.0f, 717.0f));

	const sf::IntRect cannonSprite = sf::IntRect(0, 0, 39, 24);

	sf::Sprite mLifeSprite1 = Sprite(TextureManager::getTexture("Graphics/playerSpritesheet.png"));
	mLifeSprite1.setTextureRect(cannonSprite);
	mLifeSprite1.setPosition(Vector2f(81.f, 720.0f));

	sf::Sprite mLifeSprite2 = Sprite(TextureManager::getTexture("Graphics/playerSpritesheet.png"));
	mLifeSprite2.setTextureRect(cannonSprite);
	mLifeSprite2.setPosition(Vector2f(126.0f, 720.f));

	mLivesSprites.push_back(mLifeSprite1);
	mLivesSprites.push_back(mLifeSprite2);
	setTextUp(mLivesText, Vector2f(LEFT_EDGE, 723.0f), "3");
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

	for (sf::Sprite life : mLivesSprites)
	{
		pWindow.draw(life);
	}
	
	if (mDisplayGameover)
	{
		pWindow.draw(mGameOverText);
	}

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

void HUD::updatePlayerLives(int pLives)
{
	if(!mLivesSprites.empty())
	{
		mLivesSprites.erase(mLivesSprites.end() - 1);
	}

	mLivesText.setString(std::to_string(pLives));
}

// -----------------------------------------------------------------------------

bool HUD::updateGameoverText()
{
	++mHoldForFrames;
	if (mHoldForFrames % 3 == 0 && mIndex <= mGameover.size())
	{
		mGameOverText.setString(mGameover.substr(0, mIndex));
		++mIndex;
	}

	if (mHoldForFrames > 120)
	{
		// write out top score to a file
		std::string s = mHiScore.getString();
		if (mScoreP1 > std::stoi(s))
		{
			std::ofstream readOut{ "Scores/HiScores.txt" };
			if (!readOut)
			{
				std::cout << "Error opening hi scores file in HUD::updateGameoverText()";
			}
			readOut << mScoreP1;
		}

		mDisplayGameover = false;
	}

	return mDisplayGameover;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------