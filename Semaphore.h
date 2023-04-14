#pragma once
#include <mutex>
#include <semaphore>


class Semaphore
{
public:
	Semaphore(int available);
	~Semaphore();

	void acquire() const;
	void acquire(int permits) const;
	void release() const;
	void release(int permits) const;

private:

	const static int GLOBAL_MAX_PERMIT = 50;
	typedef std::counting_semaphore<GLOBAL_MAX_PERMIT> semaphore;
	semaphore* semaphore_;

};
