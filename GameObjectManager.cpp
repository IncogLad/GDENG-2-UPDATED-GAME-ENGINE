#include "GameObjectManager.h"
#include "AppWindow.h"
#include "MeshManager.h"
#include "PhysicsComponent.h"
#include "CameraHandler.h"
#include "InspectorWindow.h"
#include "RenderTexture.h"
#include "UISystem.h"
#include "Mesh.h"
#include "LoadingWorkerAction.h"
#include <random>


GameObjectManager* GameObjectManager::sharedInstance = nullptr;

GameObjectManager* GameObjectManager::getInstance()
{
    return sharedInstance;
}   

void GameObjectManager::initialize()
{
    sharedInstance = new GameObjectManager();

}

void GameObjectManager::destroy()
{
	if (sharedInstance != NULL)
	{
		sharedInstance->releaseQuads();
	}
    
}



void GameObjectManager::initializeQuads(std::string name)
{
	Quads* tempQuad = new Quads();
	tempQuad->initialize(name);
	tempQuad->initBuffers();
	tempQuad->initConstBuffers();
	insertQuads(tempQuad);
	quadTable[name] = tempQuad;

	gameObjectList.push_back(tempQuad);
	gameObjectTable[tempQuad->getName()] = tempQuad;
}

void GameObjectManager::initializeQuadsAnim(std::string name)
{
	Quads* tempQuad = new Quads();
	tempQuad->initialize(name);
	tempQuad->initAnimBuffers();
	tempQuad->initConstBuffers();
	insertQuads(tempQuad);
	quadTable[name] = tempQuad;

	gameObjectList.push_back(tempQuad);
	gameObjectTable[tempQuad->getName()] = tempQuad;
}

void GameObjectManager::initializeQuadConst()
{
	for (auto const& i : sharedInstance->getQuadList()) {
		i->initConstBuffers();
	}
}

void GameObjectManager::insertQuads(Quads* quad)
{
	quadList.push_front(quad);
}

void GameObjectManager::releaseQuads()
{

}

std::list<Quads*> GameObjectManager::getQuadList()
{
	return quadList;
}

Quads* GameObjectManager::getQuadByName(std::string name)
{
	return quadTable[name];
}

Cube* GameObjectManager::getCubeByName(std::string name)
{
	return cubeTable[name];
}

void GameObjectManager::initializeSphere(std::string name)
{
	Mesh* sphere = new Mesh(*GraphicsEngine::getInstance()->getMeshManager()->createMeshFromFile(L"Assets\\Meshes\\sphere.obj"));
	
	sphere->initialize(name);
	sphere->setTag("sphere");
	meshList.push_back(sphere);
	meshTable[name] = sphere;

	gameObjectList.push_back(sphere);
	gameObjectTable[sphere->getName()] = sphere;
}

void GameObjectManager::initializeCapsule(std::string name)
{
	Mesh* capsule = new Mesh(*GraphicsEngine::getInstance()->getMeshManager()->createMeshFromFile(L"Assets\\Meshes\\capsule.obj"));
	capsule->initialize(name);
	capsule->setTag("capsule");
	meshList.push_back(capsule);
	meshTable[capsule->getName()] = capsule;

	gameObjectList.push_back(capsule);
	gameObjectTable[capsule->getName()] = capsule;
}

void GameObjectManager::initializeSphereOnLoad(std::string name, Vector3D position, Vector3D scale, Vector3D rotation,
                                               bool isRigidBody)
{
	Mesh* sphere = new Mesh(*GraphicsEngine::getInstance()->getMeshManager()->createMeshFromFile(L"Assets\\Meshes\\sphere.obj"));
	sphere->initialize(name);
	sphere->setTag("sphere");

	sphere->setPosition(position);
	sphere->setRotation(rotation);
	sphere->setScale(scale);

	if (isRigidBody)
	{
		PhysicsComponent* physics_component = new PhysicsComponent(sphere->getName(), sphere);
		physics_component->getRigidBody()->setType(BodyType::DYNAMIC);
		sphere->attachComponent(physics_component);
	}


	meshList.push_back(sphere);
	meshTable[name] = sphere;
	gameObjectList.push_back(sphere);
	gameObjectTable[sphere->getName()] = sphere;
	
}

void GameObjectManager::initializeCapsuleOnLoad(std::string name, Vector3D position, Vector3D scale, Vector3D rotation,
	bool isRigidBody)
{
	Mesh* capsule = new Mesh(*GraphicsEngine::getInstance()->getMeshManager()->createMeshFromFile(L"Assets\\Meshes\\capsule.obj"));
	capsule->initialize(name);
	capsule->setTag("capsule");

	capsule->setPosition(position);
	capsule->setRotation(rotation);
	capsule->setScale(scale);
	//std::cout << "aaaaa" << std::endl;

	if (isRigidBody)
	{
		PhysicsComponent* physics_component = new PhysicsComponent(capsule->getName(), capsule);
		physics_component->getRigidBody()->setType(BodyType::DYNAMIC);
		capsule->attachComponent(physics_component);
	}

	meshList.push_back(capsule);
	meshTable[capsule->getName()] = capsule;

	gameObjectList.push_back(capsule);
	gameObjectTable[capsule->getName()] = capsule;
}

void GameObjectManager::populateObjectList()
{
	for (auto const& i : quadList) {
		gameObjectList.push_back(i);
		gameObjectTable[i->getName()] = i;
	}

	for (auto const& i : cubeList) {
		gameObjectList.push_back(i);
		gameObjectTable[i->getName()] = i;
	}

	for (auto const& i : meshList) {
		gameObjectList.push_back(i);
		gameObjectTable[i->getName()] = i;
	}

}

std::list<AGameObject*> GameObjectManager::getGameObjectList()
{
	return this->gameObjectList;
}

std::unordered_map<std::string, AGameObject*> GameObjectManager::getGameObjectTable()
{
	return this->gameObjectTable;
}

void GameObjectManager::initializeMesh(std::string name, int sceneNumber)
{
	std::string temp_string = "Assets\\Meshes\\" + name + ".obj";
	std::wstring temp2 = std::wstring(temp_string.begin(), temp_string.end());
	const wchar_t* path = temp2.c_str();

	Mesh* mesh = GraphicsEngine::getInstance()->getMeshManager()->createMeshFromFile(path);
	mesh->initialize(name + std::to_string(sceneNumber));
	meshList.push_back(mesh);
	meshTable[name + std::to_string(sceneNumber)] = mesh;

	gameObjectList.push_back(mesh);
	gameObjectTable[mesh->getName()] = mesh;


	//if (name == "teapot")
	//{
	//	Mesh* mesh = GraphicsEngine::getInstance()->getMeshManager()->createMeshFromFile(L"Assets\\Meshes\\teapot.obj");
	//	mesh->initialize(name + std::to_string(sceneNumber));
	//	meshList.push_back(mesh);
	//	meshTable[name + std::to_string(sceneNumber)] = mesh;

	//	gameObjectList.push_back(mesh);
	//	gameObjectTable[mesh->getName()] = mesh;
	//}


	//if (name == "armadillo")
	//{
	//	Mesh* mesh1 = GraphicsEngine::getInstance()->getMeshManager()->createMeshFromFile(L"Assets\\Meshes\\armadillo.obj");
	//	mesh1->initialize(name + std::to_string(sceneNumber));
	//	meshList.push_back(mesh1);
	//	meshTable[name + std::to_string(sceneNumber)] = mesh1;

	//	gameObjectList.push_back(mesh1);
	//	gameObjectTable[mesh1->getName()] = mesh1;
	//}
	//else if (name == "bunny")
	//{
	//	Mesh* mesh2 = GraphicsEngine::getInstance()->getMeshManager()->createMeshFromFile(L"Assets\\Meshes\\bunny.obj");
	//	mesh2->initialize(name + std::to_string(sceneNumber));
	//	meshList.push_back(mesh2);
	//	meshTable[name + std::to_string(sceneNumber)] = mesh2;

	//	gameObjectList.push_back(mesh2);
	//	gameObjectTable[mesh2->getName()] = mesh2;
	//}
	//else if (name == "lucy")
	//{
	//	Mesh* mesh3 = GraphicsEngine::getInstance()->getMeshManager()->createMeshFromFile(L"Assets\\Meshes\\statue.obj");
	//	mesh3->initialize(name + std::to_string(sceneNumber));
	//	meshList.push_back(mesh3);
	//	meshTable[name + std::to_string(sceneNumber)] = mesh3;

	//	gameObjectList.push_back(mesh3);
	//	gameObjectTable[mesh3->getName()] = mesh3;
	//}

	/*PhysicsComponent* physics_component = new PhysicsComponent(mesh->getName(), mesh);
	mesh->attachComponent(physics_component);

	PhysicsComponent* physics_component2 = new PhysicsComponent(mesh2->getName(), mesh2);
	mesh2->attachComponent(physics_component);

	PhysicsComponent* physics_component3 = new PhysicsComponent(mesh1->getName(), mesh1);
	mesh1->attachComponent(physics_component);*/
}

std::list<Mesh*> GameObjectManager::getMeshList()
{
	return meshList;
}

Mesh* GameObjectManager::getMeshByName(std::string name)
{
	return meshTable[name];
}

void GameObjectManager::saveEditStates()
{
	for (auto const& gameObj : gameObjectList)
	{
		gameObj->saveEditState();
	}
}

void GameObjectManager::restoreEditStates()
{
	for (auto const& gameObj : gameObjectList)
	{
		gameObj->restoreEditState();
	}
}

void GameObjectManager::deleteObject(AGameObject* gameObject)
{
	if (gameObject->getTag() == "cube" || gameObject->getTag() == "plane")
	{
		for (auto cube : cubeList)
		{
			if (cube->getName() == gameObject->getName())
			{
				cubeList.remove(cube);
				gameObjectList.remove(cube);
				break;
			}
		}

		cubeTable.erase(gameObject->getName());
		gameObjectTable.erase(gameObject->getName());
	}
	else if (gameObject->getTag() == "sphere" || gameObject->getTag() == "capsule")
	{
		for (auto mesh : meshList)
		{
			if (mesh->getName() == gameObject->getName())
			{
				meshList.remove(mesh);
				gameObjectList.remove(mesh);
				break;
			}
		}

		meshTable.erase(gameObject->getName());
		gameObjectTable.erase(gameObject->getName());
	}
	else
	{
		for (auto mesh : meshList)
		{
			if (mesh->getName() == gameObject->getName())
			{
				meshList.remove(mesh);
				gameObjectList.remove(mesh);
				break;
			}
		}

		meshTable.erase(gameObject->getName());
		gameObjectTable.erase(gameObject->getName());
	}
}

void GameObjectManager::updateAll()
{
	for (auto const& tempRT : GraphicsEngine::getInstance()->getRenderTextureList()) {
		//std::cout << GraphicsEngine::getInstance()->getCurrentRenderedTexture()->getName() << std::endl;
		GraphicsEngine::getInstance()->setCurrentRenderTexture(tempRT);
		
		CameraHandler::getInstance()->setCurrentCamera(tempRT->getName());
		GraphicsEngine::getInstance()->RenderToTexture(AppWindow::getInstance()->getSwapChain());

		//Draw Everything
		for (auto const& i : GameObjectManager::getInstance()->getQuadList()) {
			i->draw();
		}

		for (auto const& i : GameObjectManager::getInstance()->getCubeList()) {
			//std::cout << i->getName() << std::endl;
			if (i->getActive())
			{
				//std::cout << i->getEnabled() << std::endl;
				i->draw();
			}
		}

		for (auto const& i : GameObjectManager::getInstance()->getMeshList()) {
			//std::cout<<i->getName() << std::endl;
			if (i->getActive())
			{
				i->draw();
			}
		}


		//CameraHandler::getInstance()->update();
	}
}

void GameObjectManager::initialize_threading_necessities()
{
	thread_pool = new ThreadPool("thread_pool", 5);
	thread_pool->startScheduler();
	//mutex = new Semaphore(1);
}

void GameObjectManager::declareSceneMeshes()
{
	scene1MeshNames.emplace_back("statue");
	scene1MeshNames.emplace_back("monitor");
	scene1MeshNames.emplace_back("bunny");

	scene2MeshNames.emplace_back("spaceship");
	scene2MeshNames.emplace_back("suzanne");
	scene2MeshNames.emplace_back("torus");

	scene3MeshNames.emplace_back("duck");
	scene3MeshNames.emplace_back("penguin");
	scene3MeshNames.emplace_back("scene"); //replace

	scene4MeshNames.emplace_back("asteroid");
	scene4MeshNames.emplace_back("teapot");
	scene4MeshNames.emplace_back("sphere_hq");
	scene4MeshNames.emplace_back("box");
	scene4MeshNames.emplace_back("sponza_basic");

	scene5MeshNames.emplace_back("armadillo");
	scene5MeshNames.emplace_back("scene"); //replace
	scene5MeshNames.emplace_back("scene");//replace
	scene5MeshNames.emplace_back("aris_weapon");
}

void GameObjectManager::LoadSceneMeshes(int sceneNumber, bool viewImmediate)
{
	switch (sceneNumber)
	{
		case 1:
			for (int i = 0; i < scene1MeshNames.size(); i++)
			{
				LoadingWorkerAction* loading_worker_action = new LoadingWorkerAction(scene1MeshNames[i], 1, this, viewImmediate);
				this->thread_pool->scheduleTask(loading_worker_action);
			}
		break;
		case 2:
			for (int i = 0; i < scene2MeshNames.size(); i++)
			{
				LoadingWorkerAction* loading_worker_action = new LoadingWorkerAction(scene2MeshNames[i], 2, this, viewImmediate);
				this->thread_pool->scheduleTask(loading_worker_action);
			}
		break;
		case 3:
			for (int i = 0; i < scene3MeshNames.size(); i++)
			{
				LoadingWorkerAction* loading_worker_action = new LoadingWorkerAction(scene3MeshNames[i], 3, this, viewImmediate);
				this->thread_pool->scheduleTask(loading_worker_action);
			}
		break;
		case 4:
			for (int i = 0; i < scene4MeshNames.size(); i++)
			{
				LoadingWorkerAction* loading_worker_action = new LoadingWorkerAction(scene4MeshNames[i], 4, this, viewImmediate);
				this->thread_pool->scheduleTask(loading_worker_action);
			}
		break;
		case 5:
			for (int i = 0; i < scene5MeshNames.size(); i++)
			{
				LoadingWorkerAction* loading_worker_action = new LoadingWorkerAction(scene5MeshNames[i], 5, this, viewImmediate);
				this->thread_pool->scheduleTask(loading_worker_action);
			}
		break;

		default: return;
	}

		

}

Mesh* GameObjectManager::initializeSceneMesh(std::string name, int sceneNumber)
{
	std::string temp_string = "Assets\\Meshes\\" + name + ".obj";
	std::wstring temp2 = std::wstring(temp_string.begin(), temp_string.end());
	const wchar_t* path = temp2.c_str();

	Mesh* mesh = GraphicsEngine::getInstance()->getMeshManager()->createMeshFromFile(path);
	mesh->initialize(name + std::to_string(sceneNumber));

	return mesh;

	/*meshList.push_back(mesh);
	meshTable[name + std::to_string(sceneNumber)] = mesh;

	gameObjectList.push_back(mesh);
	gameObjectTable[mesh->getName()] = mesh;*/

}

void GameObjectManager::LoadAllScenes()
{

	updateLoadingStatus(1, true);
	updateLoadingStatus(2, true);
	updateLoadingStatus(3, true);
	updateLoadingStatus(4, true);
	updateLoadingStatus(5, true);

	LoadSceneMeshes(4);
	LoadSceneMeshes(2);
	LoadSceneMeshes(5);
	LoadSceneMeshes(3);
	LoadSceneMeshes(1);

}

void GameObjectManager::viewSceneMeshes(int sceneNum)
{
	switch (sceneNum)
	{
	case 1:
		for (auto mesh : scene1MeshList)
		{
			meshList.push_back(mesh);
			meshTable[mesh->getName() + std::to_string(sceneNum)] = mesh;

			gameObjectList.push_back(mesh);
			gameObjectTable[mesh->getName()] = mesh;
		}
		break;
	case 2:
		for (auto mesh : scene2MeshList)
		{
			meshList.push_back(mesh);
			meshTable[mesh->getName() + std::to_string(sceneNum)] = mesh;

			gameObjectList.push_back(mesh);
			gameObjectTable[mesh->getName()] = mesh;
		}
		break;
	case 3:
		for (auto mesh : scene3MeshList)
		{
			meshList.push_back(mesh);
			meshTable[mesh->getName() + std::to_string(sceneNum)] = mesh;

			gameObjectList.push_back(mesh);
			gameObjectTable[mesh->getName()] = mesh;
		}
		break;
	case 4:
		for (auto mesh : scene4MeshList)
		{
			meshList.push_back(mesh);
			meshTable[mesh->getName() + std::to_string(sceneNum)] = mesh;

			gameObjectList.push_back(mesh);
			gameObjectTable[mesh->getName()] = mesh;
		}
		break;
	case 5:
		for (auto mesh : scene5MeshList)
		{
			meshList.push_back(mesh);
			meshTable[mesh->getName() + std::to_string(sceneNum)] = mesh;

			gameObjectList.push_back(mesh);
			gameObjectTable[mesh->getName()] = mesh;
		}
		break;

	default: return;
	}
	
	
}

void GameObjectManager::unloadSceneMeshes(int sceneNum)
{
	switch (sceneNum)
	{
	case 1:
		for (auto mesh : scene1MeshList)
		{
			deleteObject(mesh);
			scene1MeshList.remove(mesh);
			updateLoadingBar(sceneNum);
			updateLoadingStatus(sceneNum, false);
			break;
		}
		break;
	case 2:
		for (auto mesh : scene2MeshList)
		{
			deleteObject(mesh);
			scene2MeshList.remove(mesh);
			updateLoadingBar(sceneNum);
			updateLoadingStatus(sceneNum, false);
			break;
		}
		break;
	case 3:
		for (auto mesh : scene3MeshList)
		{
			deleteObject(mesh);
			scene3MeshList.remove(mesh);
			updateLoadingBar(sceneNum);
			updateLoadingStatus(sceneNum, false);
			break;
		}
		break;
	case 4:
		for (auto mesh : scene4MeshList)
		{
			deleteObject(mesh);
			scene4MeshList.remove(mesh);
			updateLoadingBar(sceneNum);
			updateLoadingStatus(sceneNum, false);
			break;
		}
		break;
	case 5:
		for (auto mesh : scene5MeshList)
		{
			deleteObject(mesh);
			scene5MeshList.remove(mesh);
			updateLoadingBar(sceneNum);
			updateLoadingStatus(sceneNum, false);
			break;
		}
		break;

	default: return;
	}
}

void GameObjectManager::onFinishedExecution(int sceneNum, Mesh* mesh, bool viewImmediate)
{
	switch (sceneNum)
	{
	case 1:
		scene1MeshList.push_back(mesh);
		SceneLoadingRatio[1] = static_cast<float>(scene1MeshList.size()) / scene1MeshNames.size();
		if (SceneLoadingRatio[sceneNum] == 1 && viewImmediate)
		{
			viewSceneMeshes(sceneNum);
		}
		break;
	case 2:
		scene2MeshList.push_back(mesh);
		SceneLoadingRatio[2] = static_cast<float>(scene2MeshList.size()) / scene2MeshNames.size();
		if (SceneLoadingRatio[sceneNum] == 1 && viewImmediate)
		{
			viewSceneMeshes(sceneNum);
		}
		break;
	case 3:
		scene3MeshList.push_back(mesh);
		SceneLoadingRatio[3] = static_cast<float>(scene3MeshList.size()) / scene3MeshNames.size();
		if (SceneLoadingRatio[sceneNum] == 1 && viewImmediate)
		{
			viewSceneMeshes(sceneNum);
		}
		break;
	case 4:
		scene4MeshList.push_back(mesh);
		SceneLoadingRatio[4] = static_cast<float>(scene4MeshList.size()) / scene4MeshNames.size();
		if (SceneLoadingRatio[sceneNum] == 1 && viewImmediate)
		{
			viewSceneMeshes(sceneNum);
		}
		break;
	case 5:
		scene5MeshList.push_back(mesh);
		SceneLoadingRatio[5] = static_cast<float>(scene5MeshList.size()) / scene5MeshNames.size();
		if (SceneLoadingRatio[sceneNum] == 1 && viewImmediate)
		{
			viewSceneMeshes(sceneNum);
		}
		break;

	default: return;
	
	}
}

void GameObjectManager::updateLoadingBar(int num)
{
	switch (num)
	{
	case 1:
		SceneLoadingRatio[1] = static_cast<float>(scene1MeshList.size()) / scene1MeshNames.size();
		break;
	case 2:
		SceneLoadingRatio[2] = static_cast<float>(scene2MeshList.size()) / scene2MeshNames.size();
		break;
	case 3:
		SceneLoadingRatio[3] = static_cast<float>(scene3MeshList.size()) / scene3MeshNames.size();
		break;
	case 4:
		SceneLoadingRatio[4] = static_cast<float>(scene4MeshList.size()) / scene4MeshNames.size();
		break;
	case 5:
		SceneLoadingRatio[5] = static_cast<float>(scene5MeshList.size()) / scene5MeshNames.size();
		break;

	default: return;

	}
}

void GameObjectManager::updateLoadingStatus(int num, bool status)
{
	switch (num)
	{
	case 1:
		SceneIsLoading[1] = status;
		break;
	case 2:
		SceneIsLoading[2] = status;
		break;
	case 3:
		SceneIsLoading[3] = status;
		break;
	case 4:
		SceneIsLoading[4] = status;
		break;
	case 5:
		SceneIsLoading[5] = status;
		break;

	default: return;

	}
}

void GameObjectManager::setRandomizedTransforms(Vector3D position, Vector3D scale)
{


}

void GameObjectManager::initializeCube(std::string name, int num = 0)
{
	Cube* cube = new Cube();
	cube->initialize(name);
	cube->setTag("cube");
	cube->initBuffers(num);
	cube->initConstBuffers();
	if (num == 0)
	{
		cube->attachComponent(new PhysicsComponent(cube->getName(), cube));

	}
	insertCube(cube);
	cubeTable[name] = cube;
	gameObjectList.push_back(cube);
	gameObjectTable[cube->getName()] = cube;

}

void GameObjectManager::initializeCubeOnLoad(std::string name, int num, Vector3D position, Vector3D scale,
	Vector3D rotation, bool isRigidBody)
{
	Cube* cube = new Cube();
	cube->initialize(name);
	cube->setTag("cube");
	cube->initBuffers(num);
	cube->initConstBuffers();

	//cube->setRotation(rotation);
	//cube->setScale(scale);

	if (isRigidBody)
	{
		//PhysicsComponent* physics_component = new PhysicsComponent(cube->getName(), cube);
		//physics_component->getRigidBody()->setType(BodyType::DYNAMIC);
		cube->attachComponent(new PhysicsComponent(cube->getName(), cube));

		//cube->attachComponent(physics_component);
	}
	cube->setPosition(position);

	
	insertCube(cube);
	cubeTable[name] = cube;
	gameObjectList.push_back(cube);
	gameObjectTable[cube->getName()] = cube;
}




void GameObjectManager::initializeCubeConst()
{
	int num = 0;
	/*float p_secondLevel = 0.85f;
	float p_thirdLevel = 2.45f;
	float s_secondLevel = 1.6f;
	float s_thirdLevel = 3.2f;

	float tempx = 0;
	float tempy = 0;
	float tempx2 = 1;
	float tempx3 = 2;

	Vector3D rightSlant = Vector3D(0, 0, 45);
	Vector3D leftSlant = Vector3D(0, 0, -45);*/

	for (auto const& i : sharedInstance->getCubeList()) {
		i->initConstBuffers();
		

		//no7
		/*i->setScale(1, 1, 0.75f);

		Vector3D temp = Vector3D(tempx + num, tempy, 0);
		i->setPosition(temp);

		if (num == 0 || num == 2 || num == 4 || num == 8 || num == 10 || num == 13) 
		{
			i->setRotation(rightSlant);
			if (num == 8)
			{
				Vector3D temp = Vector3D(tempx2 + 0, tempy + s_secondLevel, 0);
				i->setPosition(temp);
			}
			if (num == 10)
			{
				Vector3D temp = Vector3D(tempx2 + 2, tempy + s_secondLevel, 0);
				i->setPosition(temp);
			}
			if (num == 13)
			{
				Vector3D temp = Vector3D(tempx3 + 0, tempy + s_thirdLevel, 0);
				i->setPosition(temp);
			}
		}
		if (num == 1 || num == 3 || num == 5 || num == 9 || num == 11 || num == 14)
		{
			i->setRotation(leftSlant);
			if (num == 9)
			{
				Vector3D temp = Vector3D(tempx2 + 1, tempy + s_secondLevel, 0);
				i->setPosition(temp);
			}
			if (num == 11)
			{
				Vector3D temp = Vector3D(tempx2 + 3, tempy + s_secondLevel, 0);
				i->setPosition(temp);
			}
			if (num == 14)
			{
				Vector3D temp = Vector3D(tempx3 + 1, tempy + s_thirdLevel, 0);
				i->setPosition(temp);
			}
		}
		if (num == 6 || num == 7 || num == 12)
		{
			i->setRotation(Vector3D::zeros());
			i->setScale(1.5f, 1, 0.75f);

			if (num == 6) {
				Vector3D temp = Vector3D(tempx + 1.5f, tempy + p_secondLevel, 0);
				i->setPosition(temp);
			}
			if (num == 7)
			{
				Vector3D temp = Vector3D(tempx + 3.5f, tempy + p_secondLevel, 0);
				i->setPosition(temp);
			}
			if (num == 12)
			{
				Vector3D temp = Vector3D(tempx + 2.5f, tempy + p_thirdLevel, 0);
				i->setPosition(temp);
			}
		}*/

		num++;
	}
}

void GameObjectManager::insertCube(Cube* cube)
{
	cubeList.push_front(cube);
}

void GameObjectManager::releaseCubes()
{
}

std::list<Cube*> GameObjectManager::getCubeList()
{
	return cubeList;
}

GameObjectManager::GameObjectManager()
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 6); // distribution in range [1, 6]

	std::cout << dist6(rng) << std::endl;
	for (auto position : randomizedScene1Positions)
	{
		position = Vector3D(dist6(rng), dist6(rng), dist6(rng));
	}

	for (auto position : randomizedScene2Positions)
	{
		position = Vector3D(dist6(rng), dist6(rng), dist6(rng));
	}

	for (auto position : randomizedScene3Positions)
	{
		position = Vector3D(dist6(rng), dist6(rng), dist6(rng));
	}

	for (auto position : randomizedScene4Positions)
	{
		position = Vector3D(dist6(rng), dist6(rng), dist6(rng));
	}

	for (auto position : randomizedScene5Positions)
	{
		position = Vector3D(dist6(rng), dist6(rng), dist6(rng));
	}
}

GameObjectManager::~GameObjectManager()
{
	thread_pool->stopScheduler();
}
