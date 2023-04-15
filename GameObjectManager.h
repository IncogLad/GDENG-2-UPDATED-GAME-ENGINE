#pragma once
#include <list>

#include "AGameObject.h"
#include "Quads.h"
#include "Cube.h"
#include "Mesh.h"
#include "IExecutionEvent.h"
#include "Semaphore.h"
#include "ThreadPool.h"

class GameObjectManager :public IExecutionEvent
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

	//GDPARCM METHODS
	void initialize_threading_necessities();
	void declareSceneMeshes();
	void LoadSceneMeshes(int sceneNumber, bool viewImmediate = false); // func for the buttons
	Mesh* initializeSceneMesh(std::string name, int sceneNumber);
	void LoadAllScenes();
	void viewSceneMeshes(int sceneNum);
	void unloadSceneMeshes(int sceneNum);
	std::vector<float> SceneLoadingRatio = std::vector<float>(6);
	std::vector<bool> SceneIsLoading = std::vector<bool>(6);
	void onFinishedExecution(int num, Mesh* mesh, bool viewImmediate = false) override;
	void updateLoadingBar(int num);
	void updateLoadingStatus(int num, bool status);
	std::list<Mesh*> scene1MeshList;
	std::list<Mesh*> scene2MeshList;
	std::list<Mesh*> scene3MeshList;
	std::list<Mesh*> scene4MeshList;
	std::list<Mesh*> scene5MeshList;

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

	

	std::vector<std::string> scene1MeshNames = std::vector<std::string>();
	std::vector<std::string> scene2MeshNames = std::vector<std::string>();
	std::vector<std::string> scene3MeshNames = std::vector<std::string>();
	std::vector<std::string> scene4MeshNames = std::vector<std::string>();
	std::vector<std::string> scene5MeshNames = std::vector<std::string>();

	std::list<AGameObject*> gameObjectList;
	std::unordered_map<std::string, AGameObject*> gameObjectTable;

	std::unordered_map<std::string, Quads*> quadTable;
	std::unordered_map<std::string, Cube*> cubeTable;
	std::unordered_map<std::string, Mesh*> meshTable;

	GameObjectManager(GameObjectManager const&) {};
	GameObjectManager& operator=(GameObjectManager const&) {};

	ThreadPool* thread_pool;
	//Semaphore* mutex;

};

