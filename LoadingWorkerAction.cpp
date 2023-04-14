#include "LoadingWorkerAction.h"
#include <iostream>

#include "GameObjectManager.h"
#include "TextureManager.h"
#include "Mesh.h"
#include "UISystem.h"


LoadingWorkerAction::LoadingWorkerAction(std::string name, int sceneNum, IExecutionEvent* EE)
{
	this->name = name;
	this->sceneNum = sceneNum;
	this->execution_event_ = EE;
}

LoadingWorkerAction::~LoadingWorkerAction()
{
	UISystem::getInstance()->UpdateDebugWindow("Destroying LoadingWorkerAction.");
}

void LoadingWorkerAction::onStartTask()
{
	IETThread::sleep(500);
	
	GameObjectManager::getInstance()->initializeMesh(this->name, this->sceneNum);
	
	UISystem::getInstance()->UpdateDebugWindow("[GameObjectManager] Loaded " + this->name + " model!");

	this->execution_event_->onFinishedExecution(sceneNum);
	delete this;

}
