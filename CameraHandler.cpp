#include "CameraHandler.h"
#include "EngineTime.h"

CameraHandler* CameraHandler::sharedInstance = nullptr;

CameraHandler* CameraHandler::getInstance()
{
	return sharedInstance;
}

void CameraHandler::initialize()
{

	sharedInstance = new CameraHandler();
	
	
	Camera* scene_camera = new Camera();
	scene_camera->initialize(sharedInstance->camera_types_.scene_camera);
	sharedInstance->camera_table_[sharedInstance->camera_types_.scene_camera] = scene_camera;
	sharedInstance->camera_list_.push_back(scene_camera);

	Camera* topdown_camera = new Camera();
	topdown_camera->initialize(sharedInstance->camera_types_.topdown_camera);
	sharedInstance->camera_table_[sharedInstance->camera_types_.topdown_camera] = topdown_camera;
	sharedInstance->camera_list_.push_back(topdown_camera);

	Camera* perspective_camera = new Camera();
	perspective_camera->initialize(sharedInstance->camera_types_.perspective_camera);
	sharedInstance->camera_table_[sharedInstance->camera_types_.perspective_camera] = perspective_camera;
	sharedInstance->camera_list_.push_back(perspective_camera);

	Camera* wireframe_camera = new Camera();
	wireframe_camera->initialize(sharedInstance->camera_types_.wireframe_camera);
	sharedInstance->camera_table_[sharedInstance->camera_types_.wireframe_camera] = wireframe_camera;
	sharedInstance->camera_list_.push_back(wireframe_camera);

	//set initial cam to scene cam
	sharedInstance->setInitCamera();
}

void CameraHandler::destroy()
{
	delete sharedInstance;
}

void CameraHandler::update()
{
	this->currentCamera->update(EngineTime::getDeltaTime());
}

void CameraHandler::setInitCamera()
{
	this->currentCamera = camera_table_[camera_types_.topdown_camera];
}

Camera* CameraHandler::getCurrentCamera()
{
	return this->currentCamera;
}

void CameraHandler::setCurrentCamera(String cameraType)
{
	currentCamera = camera_table_[cameraType];
}

Matrix4x4 CameraHandler::getCurrentCameraViewMatrix()
{
	return this->currentCamera->getViewMatrix();

}

Camera* CameraHandler::getCameraOfType(String cameratype)
{
	return camera_table_[cameratype];

}

CameraHandler::CameraHandler()
{
}

CameraHandler::~CameraHandler()
{
}
