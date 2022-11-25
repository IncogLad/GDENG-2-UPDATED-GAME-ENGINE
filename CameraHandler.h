#pragma once
#include "Camera.h"
#include <list>
#include <unordered_map>

typedef std::string String;
typedef std::list<Camera*> CameraList;
typedef std::unordered_map<String, Camera*> CameraTable;

class CameraTypes
{
public:
	const String topdown_camera = "TOPDOWN_CAMERA";
	const String scene_camera = "SCENE_CAMERA";
	const String perspective_camera = "PERSPECTIVE_CAMERA";
	const String wireframe_camera = "WIREFRAME_CAMERA";
};


class CameraHandler
{
public:
	static CameraHandler* getInstance();
	static void initialize();
	static void destroy();
	void update();

	void setInitCamera();
	Camera* getCurrentCamera();
	void setCurrentCamera(String cameraType);

	Matrix4x4 getCurrentCameraViewMatrix();
	
	Camera* getCameraOfType(String cameratype);

private:
	CameraHandler();
	~CameraHandler();

	static CameraHandler* sharedInstance;
	CameraTypes camera_types_;

	CameraHandler(CameraHandler const&) {};
	CameraHandler& operator=(CameraHandler const&) {};

	Camera* currentCamera;
	
	CameraList camera_list_;
	CameraTable camera_table_;
};

