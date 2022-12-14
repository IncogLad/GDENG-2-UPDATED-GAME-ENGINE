#include "GameObjectManager.h"
#include "AppWindow.h"
#include "MeshManager.h"
#include "PhysicsComponent.h"
#include "CameraHandler.h"
#include "RenderTexture.h"

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

void GameObjectManager::initializeMesh()
{
	Mesh* mesh = GraphicsEngine::getInstance()->getMeshManager()->createMeshFromFile(L"Assets\\Meshes\\teapot.obj");
	mesh->initialize("teapot");
	meshList.push_back(mesh);
	meshTable["teapot"] = mesh;

	gameObjectList.push_back(mesh);
	gameObjectTable[mesh->getName()] = mesh;

	Mesh* mesh1 = GraphicsEngine::getInstance()->getMeshManager()->createMeshFromFile(L"Assets\\Meshes\\armadillo.obj");
	mesh1->initialize("armadillo");
	meshList.push_back(mesh1);
	meshTable["armadillo"] = mesh1;

	gameObjectList.push_back(mesh1);
	gameObjectTable[mesh1->getName()] = mesh1;
	
	Mesh* mesh2 = GraphicsEngine::getInstance()->getMeshManager()->createMeshFromFile(L"Assets\\Meshes\\bunny.obj");
	mesh2->initialize("bunny");
	meshList.push_back(mesh2);
	meshTable["bunny"] = mesh2;

	gameObjectList.push_back(mesh2);
	gameObjectTable[mesh2->getName()] = mesh2;

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

void GameObjectManager::enableCubes(std::string name)
{
	for (auto cube : cubeList)
	{
		if (cube->getName() == name)
		{
			cube->setEnabled(true);
		}
	}
}

void GameObjectManager::enableMeshes(std::string name)
{
		for (auto mesh : meshList)
	{
		if (mesh->getName() == name)
		{
			mesh->setEnabled(true);
		}
	}
}

void GameObjectManager::disableCubes(std::string name)
{
	for (auto cube : cubeList)
	{
		if (cube->getName() == name)
		{
			cube->setEnabled(false);
		}
	}
}

void GameObjectManager::disableMesh(std::string name)
{
	for (auto mesh : meshList)
	{
		if (mesh->getName() == name)
		{
			mesh->setEnabled(false);
		}
	}
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
			if (i->getEnabled())
			{
				//std::cout << i->getEnabled() << std::endl;
				i->draw();
			}
		}

		for (auto const& i : GameObjectManager::getInstance()->getMeshList()) {
			//std::cout<<i->getName() << std::endl;
			if (i->getEnabled())
			{
				i->draw();
			}
		}


		//CameraHandler::getInstance()->update();
	}
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

}

GameObjectManager::~GameObjectManager()
{

}
