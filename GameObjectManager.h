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

	void initializeMesh(std::string name, int sceneNumber = 1);
	std::list<Mesh*> getMeshList();
	Mesh* getMeshByName(std::string name);

	void saveEditStates();
	void restoreEditStates();

	void deleteObject(AGameObject* gameObject);

	void updateAll();

	std::wstring string_to_wide_string(const std::string& string)
	{
		if (string.empty())
		{
			return L"";
		}

		const auto size_needed = MultiByteToWideChar(CP_UTF8, 0, &string.at(0), (int)string.size(), nullptr, 0);
		if (size_needed <= 0)
		{
			throw std::runtime_error("MultiByteToWideChar() failed: " + std::to_string(size_needed));
		}

		std::wstring result(size_needed, 0);
		MultiByteToWideChar(CP_UTF8, 0, &string.at(0), (int)string.size(), &result.at(0), size_needed);
		return result;
	}

	std::string wide_string_to_string(const std::wstring& wide_string)
	{
		if (wide_string.empty())
		{
			return "";
		}

		const auto size_needed = WideCharToMultiByte(CP_UTF8, 0, &wide_string.at(0), (int)wide_string.size(), nullptr, 0, nullptr, nullptr);
		if (size_needed <= 0)
		{
			throw std::runtime_error("WideCharToMultiByte() failed: " + std::to_string(size_needed));
		}

		std::string result(size_needed, 0);
		WideCharToMultiByte(CP_UTF8, 0, &wide_string.at(0), (int)wide_string.size(), &result.at(0), size_needed, nullptr, nullptr);
		return result;
	}
	
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

