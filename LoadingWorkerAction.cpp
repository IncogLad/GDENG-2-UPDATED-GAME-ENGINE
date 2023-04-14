#include "LoadingWorkerAction.h"
#include <iostream>
#include "TextureManager.h"



LoadingWorkerAction::LoadingWorkerAction(std::string SPath , IExecutionEvent* EE)
{
	this->path = SPath;
	this->execution_event_ = EE;
}

LoadingWorkerAction::~LoadingWorkerAction()
{
	std::cout << "Destroying LoadingWorkerAction." << std::endl;
}

void LoadingWorkerAction::onStartTask()
{
	IETThread::sleep(500);
	//TextureManager::getInstance()->instantiateAsTexture(this->path, this->path, true);
	
	std::cout << "[TextureManager] Loaded streaming texture: " << this->path << std::endl;

	this->execution_event_->onFinishedExecution();
	delete this;

}
