#include <stdexcept>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "ResourceManager.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"
#include <fstream>
#include <sstream>

void bdnE::ResourceManager::Init(const std::string& dataPath)
{
	m_dataPath = dataPath;

	if (TTF_Init() != 0)
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

std::shared_ptr<bdnE::Texture2D> bdnE::ResourceManager::LoadTexture(const std::string& file) const
{
	const auto fullPath = m_dataPath + file;
	auto texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}
	return std::make_shared<Texture2D>(texture);
}

std::shared_ptr<bdnE::Font> bdnE::ResourceManager::LoadFont(const std::string& file, unsigned int size) const
{
	return std::make_shared<Font>(m_dataPath + file, size);
}



std::string bdnE::ResourceManager::LoadText(const std::string& file) const
{
	const auto fullPath = m_dataPath + file;
	const std::ifstream inputFile(fullPath);
	if (!inputFile.is_open())
	{
		throw std::runtime_error(std::string("Failed to load text file: ") + fullPath);
	}

	std::stringstream buffer;
	buffer << inputFile.rdbuf();
	return buffer.str();
}

