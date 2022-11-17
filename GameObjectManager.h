#pragma once
#include <list>

#include "Quads.h"
#include "Cube.h"
#include "Mesh.h"

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();

	static GameObjectManager* getInstance();
	static void initialize();
	static void destroy();

	void initializeQuads(std::string name);
	void initializeQuadsAnim(std::string name);
	void initializeQuadConst();
	void insertQuads(class Quads* quad);
	void releaseQuads();
	std::list<class Quads*> getQuadList();
	Quads* getQuadByName(std::string name);

	void initializeCube(std::string name, int num);
	void initializeCubeConst();
	void insertCube(class Cube* cube);
	void releaseCubes();
	std::list<class Cube*> getCubeList();
	Cube* getCubeByName(std::string name);


	void initializeMesh();
	std::list<Mesh*> getMeshList();
	Mesh* getMeshByName(std::string name);

	
private:
	static GameObjectManager* sharedInstance;
	std::list<Quads*> quadList;
	std::list<Cube*> cubeList;
	std::list<Mesh*> meshList;

	std::unordered_map<std::string, Quads*> quadTable;
	std::unordered_map<std::string, Cube*> cubeTable;
	std::unordered_map<std::string, Mesh*> meshTable;

	GameObjectManager(GameObjectManager const&) {};
	GameObjectManager& operator=(GameObjectManager const&) {};
	

};

