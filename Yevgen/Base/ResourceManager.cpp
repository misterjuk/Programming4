#include <stdexcept>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "ResourceManager.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"


namespace yev 
{
	void ResourceManager::Init(const std::string& dataPath)
	{
		m_dataPath = dataPath;

		if (TTF_Init() != 0)
		{
			throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
		}
	}

	std::unique_ptr<SoundEffect> yev::ResourceManager::LoadSoundEffect(const std::string& file) const
	{
		const auto fullPath = m_dataPath + file;
		return std::make_unique<SoundEffect>(fullPath);
	}

	std::shared_ptr<yev::Texture2D> yev::ResourceManager::LoadTexture(const std::string& file) const
	{
		const auto fullPath = m_dataPath + file;
		auto texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
		}
		return std::make_shared<Texture2D>(texture);
	}

	std::shared_ptr<yev::Font> yev::ResourceManager::LoadFont(const std::string& file, unsigned int size) const
	{
		return std::make_shared<Font>(m_dataPath + file, size);
	}

}
