#include "TextureLibrary.h"

#include "GraphicsEngine.h"
#include "TextureManager.h"


TextureLibrary* TextureLibrary::sharedInstance = nullptr;

TextureLibrary* TextureLibrary::getInstance()
{
	return sharedInstance;
}

 void TextureLibrary::initialize()
{
	sharedInstance = new TextureLibrary();

	Texture* brick_tex = GraphicsEngine::getInstance()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\brick.png");
	sharedInstance->textureTable["brick"] = brick_tex;

	Texture* wood_tex = GraphicsEngine::getInstance()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\wood.jpg");
	sharedInstance->textureTable["wood"] = wood_tex;

	Texture* grass_tex = GraphicsEngine::getInstance()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\grass.jpg");
	sharedInstance->textureTable["grass"] = grass_tex;

	Texture* wall_tex = GraphicsEngine::getInstance()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\wall.jpg");
	sharedInstance->textureTable["wall"] = wall_tex;

	Texture* asteroid_tex = GraphicsEngine::getInstance()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\asteroid.jpg");
	sharedInstance->textureTable["asteroid"] = asteroid_tex;

	Texture* sand_tex = GraphicsEngine::getInstance()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\sand.jpg");
	sharedInstance->textureTable["sand"] = sand_tex;
}

void TextureLibrary::destroy()
{
	delete sharedInstance;

}

Texture* TextureLibrary::getTextureByName(std::string name)
{
	
	return textureTable[name];
}

TextureLibrary::TextureLibrary()
{
}

TextureLibrary::~TextureLibrary()
{
}
