// -----------------------------------------------------------------------------
#ifndef TextureManager_H
#define TextureManager_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <SFML/Graphics/Texture.hpp>

#include <iostream>
#include <map>
#include <string>

using namespace sf;

// -----------------------------------------------------------------------------

class TextureManager
{
public:
	TextureManager(const TextureManager&) = delete;
	void operator=(const TextureManager&) = delete;

	static Texture& getTexture(const std::string& filename)
	{
		std::map<std::string, Texture>& ref = getInstance().mTextures;
		auto it = ref.find(filename);
		if (it != ref.end())
		{
			return it->second;
		}
		else
		{
			Texture& t = ref[filename];
			if (!t.loadFromFile(filename))
			{
				std::cout << "Error loading: " << filename << std::endl;
			}
			return t;
		}
	}

private:
	TextureManager() {}

	static TextureManager& getInstance()
	{
		static TextureManager instance;	// guaranteed to be destroyed properly
		return instance;
	}

	std::map<std::string, Texture> mTextures;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !TextureManager_H
