#include "GameObjectManager.h"
#include "AppWindow.h"
#include "MeshManager.h"
#include "PhysicsComponent.h"
#include "SwapChain.h"


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
	insertQuads(tempQuad);
	quadTable[name] = tempQuad;
}

void GameObjectManager::initializeQuadsAnim(std::string name)
{
	Quads* tempQuad = new Quads();
	tempQuad->initialize(name);
	tempQuad->initAnimBuffers();
	insertQuads(tempQuad);
	quadTable[name] = tempQuad;
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

void GameObjectManager::initializeMesh()
{
	Mesh* mesh = GraphicsEngine::getInstance()->getMeshManager()->createMeshFromFile(L"Assets\\Meshes\\teapot.obj");
	mesh->initialize("teapot");
	meshList.push_back(mesh);
	meshTable["teapot"] = mesh;

	Mesh* mesh1 = GraphicsEngine::getInstance()->getMeshManager()->createMeshFromFile(L"Assets\\Meshes\\armadillo.obj");
	mesh1->initialize("armadillo");
	meshList.push_back(mesh1);
	meshTable["armadillo"] = mesh1;
	
	Mesh* mesh2 = GraphicsEngine::getInstance()->getMeshManager()->createMeshFromFile(L"Assets\\Meshes\\bunny.obj");
	mesh2->initialize("bunny");
	meshList.push_back(mesh2);
	meshTable["bunny"] = mesh2;

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

void GameObjectManager::initializeCube(std::string name, int num = 0)
{
	Cube* cube = new Cube();
	cube->initialize(name);
	cube->initBuffers(num);
	PhysicsComponent* physics_component = new PhysicsComponent(cube->getName(), cube);
	if (num == 1)
	{
		physics_component->getRigidBody()->setType(BodyType::KINEMATIC);
		
	}
	cube->attachComponent(physics_component);
	insertCube(cube);
	cubeTable[name] = cube;
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
