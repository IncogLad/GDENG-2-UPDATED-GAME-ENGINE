#include "MonitorSharedLoader.h"

#include <iostream>

MonitorSharedLoader::MonitorSharedLoader()
{
	//this->mesh = new Mesh();
	this->guard = new Mutex();
	this->condition = new Condition();

}

MonitorSharedLoader::~MonitorSharedLoader()
{
	delete this->guard;
	delete this->condition;

}

void MonitorSharedLoader::loadMesh(Mesh* mesh)
{
	this->tryDisplay();
	this->reportLoadDone();

}

void MonitorSharedLoader::tryDisplay()
{
	UniqueLock unique_lock(*this->guard);
	while (this->loadingDone == false)
	{
		this->condition->wait(unique_lock);
	}

	//critical section
	//TODO: do something: maybe display mesh on the scene?
	std::cout << "Displayed Mesh X from Scene Y" <<std::endl;
	unique_lock.unlock();

}

void MonitorSharedLoader::reportLoadDone()
{
	UniqueLock unique_lock(*this->guard);
	this->loadingDone = true;
	this->condition->notify_one();
	unique_lock.unlock();
} 
