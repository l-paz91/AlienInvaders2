// -----------------------------------------------------------------------------
#ifndef SoundManager_H
#define SoundManager_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <SFML/Audio.hpp>

// -----------------------------------------------------------------------------

enum class SoundEvent
{
	eALIEN_HIT,
	eFLYING_SAUCER,
	ePLAYER_FIRE,
	ePLAYER_LIFE_LOST
};

// -----------------------------------------------------------------------------

class SoundManager
{
	// seeing as how the game only has 4 sounds and the background music I think
	// having a global static class is fine
public:
	SoundManager(const SoundManager&) = delete;
	void operator=(const SoundManager&) = delete;

	static void playSound(SoundEvent pSoundEvent)
	{
		switch (pSoundEvent)
		{
		case SoundEvent::eALIEN_HIT:
			getInstance().mAlienHit.play();
			break;
		case SoundEvent::eFLYING_SAUCER:
			getInstance().mFlyingSaucer.play();
			break;
		case SoundEvent::ePLAYER_FIRE:
			getInstance().mPlayerFire.play();
			break;
		case SoundEvent::ePLAYER_LIFE_LOST:
			getInstance().mPlayerLifeLost.play();
			break;
		default:
			break;
		}
	}

	static void stopSound(SoundEvent pSoundEvent)
	{
		switch (pSoundEvent)
		{
		case SoundEvent::eALIEN_HIT:
			getInstance().mAlienHit.stop();
			break;
		case SoundEvent::eFLYING_SAUCER:
			getInstance().mFlyingSaucer.stop();
			break;
		case SoundEvent::ePLAYER_FIRE:
			getInstance().mPlayerFire.stop();
			break;
		case SoundEvent::ePLAYER_LIFE_LOST:
			getInstance().mPlayerLifeLost.stop();
			break;
		default:
			break;
		}
	}

private:
	SoundManager()
	{
		mPlayerFireBuffer.loadFromFile("Sounds/playerFire.wav");
		mFlyingSaucerBuffer.loadFromFile("Sounds/flyingSaucer.wav");
		mPlayerLifeLostBuffer.loadFromFile("Sounds/playerLifeLost.wav");
		mAlienHitBuffer.loadFromFile("Sounds/alienHit.wav");

		mPlayerFire.setBuffer(mPlayerFireBuffer);
		mFlyingSaucer.setBuffer(mFlyingSaucerBuffer);
		mPlayerLifeLost.setBuffer(mPlayerLifeLostBuffer);
		mAlienHit.setBuffer(mAlienHitBuffer);

		mFlyingSaucer.setLoop(true);
	}

	static SoundManager& getInstance()
	{
		static SoundManager instance;
		return instance;
	}

	sf::Sound mPlayerFire;
	sf::Sound mFlyingSaucer;
	sf::Sound mPlayerLifeLost;
	sf::Sound mAlienHit;

	sf::SoundBuffer mPlayerFireBuffer;
	sf::SoundBuffer mFlyingSaucerBuffer;
	sf::SoundBuffer mPlayerLifeLostBuffer;
	sf::SoundBuffer mAlienHitBuffer;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !SoundManager_H