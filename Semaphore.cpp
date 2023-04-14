#include "Semaphore.h"

Semaphore::Semaphore(int available)
{
	this->semaphore_ = new semaphore(available);
}

Semaphore::~Semaphore()
{
	delete this->semaphore_;
}

void Semaphore::acquire() const
{
	this->semaphore_->acquire();

}

void Semaphore::acquire(int permits) const
{
	for (int i = 0; i < permits; i++)
	{
		this->semaphore_->acquire();
	}
}

void Semaphore::release() const
{
	this->semaphore_->release();
}

void Semaphore::release(int permits) const
{
	this->semaphore_->release(permits);
}