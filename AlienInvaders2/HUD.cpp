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

		void setTextUp(sf::Text& pText, const sf::Vector2f& pPos, const sf::Font& pFont, const std::string& pMsg = "")
		{
			pText.setPosition(pPos);
			pText.setFont(pFont);
			pText.setCharacterSize(21);
			pText.setFillColor(Color::White);
			pText.setString(pMsg);
		}
	}
}

// -----------------------------------------------------------------------------

ScoreAdvanceTable::ScoreAdvanceTable()
	: mScoreAdvanceTableText()
	, mFlyingSaucer(Sprite(TextureManager::getTexture("Graphics/Shield&SaucerSpriteSheet.png")))
	, mSquid(Sprite(TextureManager::getTexture("Graphics/invaderSpritesheet.png")))
	, mCrab(Sprite(TextureManager::getTexture("Graphics/invaderSpritesheet.png")))
	, mOctopus(Sprite(TextureManager::getTexture("Graphics/invaderSpritesheet.png")))
{
	mFlyingSaucer.setTextureRect(sf::IntRect(0, 48, 48, 20));
	mFlyingSaucer.setPosition(Vector2f(190, 420));

	mSquid.setTextureRect(sf::IntRect(0, 48, 24, 24));
	mSquid.setPosition(Vector2f(200, 470));

	mCrab.setTextureRect(sf::IntRect(0, 24, 32, 24));
	mCrab.setPosition(Vector2f(195, 530));

	mOctopus.setTextureRect(sf::IntRect(36, 0, 36, 24));
	mOctopus.setPosition(Vector2f(193, 585));
}

// -----------------------------------------------------------------------------

void ScoreAdvanceTable::render(sf::RenderWindow& pWindow)
{
	pWindow.draw(mScoreAdvanceTableText);
	pWindow.draw(mFlyingSaucer);
	pWindow.draw(mSquid);
	pWindow.draw(mCrab);
	pWindow.draw(mOctopus);
}

// -----------------------------------------------------------------------------

HUD::HUD()
	: mView(View(FloatRect(0.0f, 0.0f, WIDTH, HEIGHT)))
	, mInsertCoin("    INSERT     COIN\n\n\n\n<1   OR   2 PLAYERS>\n\n\n*1   1 PLAYER    1  COIN\n\n\n*2  2 PLAYERS  2  COINS", 5)
	, mPlaySpaceInvaders("         PLAY\n\n\nSPACE INVADERS", 5)
	, mScores(" = ?  MYSTERY\n\n = 30  POINTS\n\n = 20  POINTS\n\n = 10  POINTS", 5)
{
	init();

	HudPrivate::setTextUp(mScoreAdvanceTable.mScoreAdvanceTableText, Vector2f(110, 370), mFont, "*SCORE  ADVANCE  TABLE*");
	mScoreAdvanceTable.mScoreAdvanceTableText.setLetterSpacing(4);

	HudPrivate::setTextUp(mInsertCoin.mDisplayText, Vector2f(160, 300), mFont);
	mInsertCoin.mDisplayText.setLetterSpacing(4);

	HudPrivate::setTextUp(mPlaySpaceInvaders.mDisplayText, Vector2f(190, 200), mFont);
	mPlaySpaceInvaders.mDisplayText.setLetterSpacing(4);

	HudPrivate::setTextUp(mScores.mDisplayText, Vector2f(250, 415), mFont);
	mScores.mDisplayText.setLetterSpacing(4);
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

	setTextUp(mScoreP1text, Vector2f(LEFT_EDGE, TOP), mFont, "S C O R E< 1 >");
	setTextUp(mScoreP2text, Vector2f(459.0f, TOP), mFont, "S C O R E< 2 >");
	setTextUp(mHiScoreText, Vector2f(243.0f, TOP), mFont, "H I-S C O R E");

	setTextUp(mCreditText, Vector2f(411.0f, 723.0f), mFont, "C R E D I T   0 0");

	setTextUp(mScore1, Vector2f(75.0f, 75.0f), mFont, "0000");
	mScore1.setLetterSpacing(4);

	setTextUp(mScore2, Vector2f(501.0f, 75.0f), mFont, "0 0 0 0");

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
	setTextUp(mHiScore, Vector2f(267.0f, 75.0f), mFont, ss.str());

	setTextUp(mGameOverText, Vector2f(120.0f, 150.0f), mFont);
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
	setTextUp(mLivesText, Vector2f(LEFT_EDGE, 723.0f), mFont, "3");

	setTextUp(mDisplayText, Vector2f(-10, 10), mFont);
	mDisplayText.setLetterSpacing(4);

	mFlipTitleScreenMessages = false;
	mStartScoreTable = false;
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
	//pWindow.draw(mScore2);
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

void HUD::renderTitleScreen(sf::RenderWindow& pWindow)
{
	// get the current view so we can set it back after
	View currentView = pWindow.getView();

	// set the view to the HUD
	pWindow.setView(mView);

	// now draw to the window
	pWindow.draw(mScoreP1text);
	pWindow.draw(mScore1);
	pWindow.draw(mScoreP2text);
	pWindow.draw(mHiScoreText);
	pWindow.draw(mHiScore);
	//pWindow.draw(mLivesText);
	pWindow.draw(mCreditText);

	if (!mFlipTitleScreenMessages)
	{
		if (mStartScoreTable)
		{
			mScoreAdvanceTable.render(pWindow);
			pWindow.draw(mScores.mDisplayText);
		}

		pWindow.draw(mPlaySpaceInvaders.mDisplayText);
	}
	else
	{
		pWindow.draw(mInsertCoin.mDisplayText);
	}

	// set it back to the previous view
	pWindow.setView(currentView);
}

// -----------------------------------------------------------------------------

void HUD::updateTitleScreenMessages(const float& pDeltaTime)
{
	if (!mFlipTitleScreenMessages)
	{
		if (mPlaySpaceInvaders.update())
		{
			mStartScoreTable = true;
		}

		if (mStartScoreTable)
		{
			if (mScores.update())
			{
				mStartScoreTable = false;
				mFlipTitleScreenMessages = !mFlipTitleScreenMessages;
				mPlaySpaceInvaders.reset();
				mScores.reset();
			}
		}
	}
	else
	{
		if (mInsertCoin.update())
		{
			mFlipTitleScreenMessages = !mFlipTitleScreenMessages;
			mInsertCoin.reset();
		}
	}
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