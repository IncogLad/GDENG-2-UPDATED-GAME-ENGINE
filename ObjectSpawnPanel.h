#pragma once
#include "AUIScreen.h"

class ObjectSpawnPanel :public AUIScreen
{
	enum ObjectType { cube = 0, plane = 1, sphere = 2, capsule = 3};
	typedef std::string String;
public:
	ObjectSpawnPanel();
	~ObjectSpawnPanel() override;

	void drawUI() override;

	//get object list

private:
	ObjectType objectType;
	String ObjectName;
	int objectCount = 0;

	int latestCubeCount = 0;
	int latestPlaneCount = 0;
	int latestSphereCount = 0;
	int latestCapsuleCount = 0;

	bool planeCheckBox = false;
	bool cubeCheckBox = false;
	bool sphereCheckBox = false;
	bool capsuleCheckBox = false;
	
};

