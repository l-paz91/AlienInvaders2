// -----------------------------------------------------------------------------
#ifndef HUD_H
#define HUD_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <vector>
#include <SFML/Graphics.hpp>

// -----------------------------------------------------------------------------

struct DisplayTextWithFrameDelay
{
	DisplayTextWithFrameDelay(const std::string& pString, const int& pFrameDelay)
		: mDisplayText()
		, mString(pString)
		, mElapsedFrames(0)
		, mFrameDelay(pFrameDelay)
		, mIndex(0)
		, mDisplay(false)
	{}

	bool update()
	{
		++mElapsedFrames;
		if (mElapsedFrames % mFrameDelay == 0 && mIndex <= mString.size())
		{
			mDisplayText.setString(mString.substr(0, mIndex++));
			return false;
		}

		if (mElapsedFrames >= (mFrameDelay * (mString.size()+10)))
		{
			//we've finished displaying the message
			return true;
		}

		return false;
	}

	bool showTextForFrames()
	{
		++mElapsedFrames;
		if (mElapsedFrames > mFrameDelay)
		{
			//we've finished displaying the message
			reset();
			return true;
		}

		return false;
	}

	void reset()
	{
		mDisplayText.setString("");
		mElapsedFrames = 0;
		mIndex = 0;
		mDisplay = false;
	}

	sf::Text mDisplayText;
	std::string mString;
	int mElapsedFrames;
	int mFrameDelay;
	uint16_t mIndex;
	bool mDisplay;
};

// -----------------------------------------------------------------------------

struct ScoreAdvanceTable
{
	ScoreAdvanceTable();

	void render(sf::RenderWindow& pWindow);

	sf::Text mScoreAdvanceTableText;
	sf::Sprite mFlyingSaucer;
	sf::Sprite mSquid;
	sf::Sprite mCrab;
	sf::Sprite mOctopus;
};

// -----------------------------------------------------------------------------

struct HUD
{
	HUD();

	void init();

	void render(sf::RenderWindow& pWindow);
	void renderTitleScreen(sf::RenderWindow& pWindow);

	void updateTitleScreenMessages(const float& pDeltaTime);

	void updatePlayer1Score(int pScore);
	void updatePlayerLives(int pLives);

	bool updateGameoverText();

	sf::View mView;
	sf::Font mFont;

	sf::Text mScoreP1text;
	sf::Text mScoreP2text;
	sf::Text mHiScoreText;
	sf::Text mLivesText;
	sf::Text mCreditText;
	sf::Text mGameOverText;
	sf::Text mDisplayText;

	sf::Text mScore1;
	sf::Text mScore2;
	sf::Text mHiScore;

	sf::RectangleShape mGreenBar;
	std::vector<sf::Sprite> mLivesSprites;	

	ScoreAdvanceTable mScoreAdvanceTable;

	DisplayTextWithFrameDelay mInsertCoin;
	DisplayTextWithFrameDelay mPlaySpaceInvaders;
	DisplayTextWithFrameDelay mScores;

	std::string mGameover;
	int mScoreP1;
	int mHoldForFrames;
	size_t mIndex;
	bool mDisplayGameover;
	bool mFlipTitleScreenMessages;
	bool mStartScoreTable;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !HUD_H