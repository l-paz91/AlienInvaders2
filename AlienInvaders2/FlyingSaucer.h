// -----------------------------------------------------------------------------
#ifndef FlyingSaucer_H
#define FlyingSaucer_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <SFML/Graphics.hpp>

// -----------------------------------------------------------------------------

struct FlyingSaucer
{
	FlyingSaucer();

	void init();
	void update(const float& pDeltaTime, bool pDirection);
	void render(sf::RenderWindow& pWindow);

	void setUfoScore(int pScore, const sf::Vector2f& pPos);

	sf::Sprite mSprite;
	sf::Font mFont;
	sf::Text mScore;

	float mTimeUntilSaucer;
	float mSpeed;
	bool mDestroyed;
	bool mDisplaySaucer;
	bool mShowText;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !FlyingSaucer_H