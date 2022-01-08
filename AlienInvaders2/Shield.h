// -----------------------------------------------------------------------------
#ifndef Shield_H
#define Shield_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <SFML/Graphics.hpp>

// -----------------------------------------------------------------------------

struct Shields
{
	Shields();

	void init();

	void update(const float& pDeltaTime) {}
	void shieldHit(const sf::Vector2f& pPos);
	void render(sf::RenderWindow& pWindow) const;

	std::vector<sf::Sprite> mSprites;
	sf::RenderTexture mRenderTarget;
	sf::Sprite mShotMask;
	sf::Image mRenderImage;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !Shield_H