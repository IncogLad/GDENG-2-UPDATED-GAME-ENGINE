#pragma once
#include <list>

#include "AGameObject.h"
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
	void initializeCubeOnLoad(std::string name, int num, Vector3D position, Vector3D scale, Vector3D rotation, bool isRigidBody);
	void initializeCubeConst();
	void insertCube(class Cube* cube);
	void releaseCubes();
	std::list<class Cube*> getCubeList();
	Cube* getCubeByName(std::string name);

	void initializeSphere(std::string name);
	void initializeSphereOnLoad(std::string name, Vector3D position, Vector3D scale, Vector3D rotation, bool isRigidBody);

	void initializeCapsule(std::string name);
	void initializeCapsuleOnLoad(std::string name, Vector3D position, Vector3D scale, Vector3D rotation, bool isRigidBody);

	void populateObjectList();
	std::list<AGameObject*> getGameObjectList();
	std::unordered_map<std::string, AGameObject*> getGameObjectTable();

	void initializeMesh();
	std::list<Mesh*> getMeshList();
	Mesh* getMeshByName(std::string name);

	void saveEditStates();
	void restoreEditStates();

	void deleteObject(AGameObject* gameObject);

	void updateAll();
	
private:
	static GameObjectManager* sharedInstance;
	std::list<Quads*> quadList;
	std::list<Cube*> cubeList;
	std::list<Mesh*> meshList;

	std::list<AGameObject*> gameObjectList;
	std::unordered_map<std::string, AGameObject*> gameObjectTable;

	std::unordered_map<std::string, Quads*> quadTable;
	std::unordered_map<std::string, Cube*> cubeTable;
	std::unordered_map<std::string, Mesh*> meshTable;

	GameObjectManager(GameObjectManager const&) {};
	GameObjectManager& operator=(GameObjectManager const&) {};
	

};

