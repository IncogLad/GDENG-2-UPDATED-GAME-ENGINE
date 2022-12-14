#pragma once
#include <unordered_map>
#include <list>
#include "Texture.h"


class TextureLibrary
{
public:
	static TextureLibrary* getInstance();
	static void initialize();
	static void destroy();
	
	Texture* getTextureByName(std::string name);
	


private:
	TextureLibrary();
	~TextureLibrary();

	static TextureLibrary* sharedInstance;

	std::list<Texture*> textureList;
	std::unordered_map<std::string, Texture*> textureTable;
};