#include "Camera.h"
#include "AppWindow.h"
#include "DeviceContext.h"
#include "EngineTime.h"
#include "InputSystem.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::initialize(std::string name)
{
	AGameObject::initialize(name);
	InputSystem::get()->addListener(this);
	m_rs = GraphicsEngine::getInstance()->createRasterizer_state(false);

	this->worldCam.setTranslation(Vector3D(0, 0, 0));

	//init base on camera type
	if (this->name == "TOPDOWN_CAMERA")
	{
		this->m_rot_y = 0.f;
		this->m_rot_x = 1.57f;
		this->worldCam.setTranslation(Vector3D(0, 10, 0));
	}
	else if (this->name == "PERSPECTIVE_CAMERA")
	{
		this->m_rot_y = 0.79f;
		this->m_rot_x = 0.79f;
		this->worldCam.setTranslation(Vector3D(-3, 5, -2));
	}
	else if (this->name == "SCENE_CAMERA")
	{
		this->worldCam.setTranslation(Vector3D(0, 2, -8));
	}
	else if (this->name == "WIREFRAME_CAMERA")
	{
		m_rs = GraphicsEngine::getInstance()->createRasterizer_state(true);
		this->worldCam.setTranslation(Vector3D(0, 2, -8));
	}

	//this->worldCam.setIdentity();
	
	//this->worldCam.setRotationX(90);
	//camPos.zeros();
}

void Camera::destroy()
{
	AGameObject::destroy();
}

void Camera::draw(VertexShader* m_vs, PixelShader* m_ps)
{

}

void Camera::update(float deltaTime)
{
	Matrix4x4 temp; temp.setIdentity();

	temp.setIdentity();

	
	Matrix4x4 xMatrix; xMatrix.setIdentity();
	xMatrix.setRotationX(m_rot_x);
	temp *= xMatrix;

	Matrix4x4 yMatrix; yMatrix.setIdentity();
	yMatrix.setRotationY(m_rot_y);
	temp *= yMatrix;


	Vector3D new_pos = worldCam.getTranslation() + temp.getZDirection() * (m_forward * deltaTime * 1.5f);
	new_pos = new_pos + temp.getYDirection() * (m_upward * deltaTime * 1.5f);
	new_pos = new_pos + temp.getXDirection() * (m_rightward * deltaTime * 1.5f);
	temp.setTranslation(new_pos);

	worldCam = temp;

	temp.inverse();
	this->localMatrix = temp;
	
}

std::string Camera::getName()
{
	return this->name;
}

Matrix4x4 Camera::getViewMatrix()
{
	return this->localMatrix;
}


void Camera::onKeyDown(int key)
{
	if (key == 'W')
	{
		this->m_forward = 1.0f;
		std::cout << "W pressed" << std::endl;
		
	}
	else if (key == 'S')
	{
		this->m_forward = -1.0f;
		std::cout << "S pressed" << std::endl;
	}
	else if (key == 'A')
	{
		this->m_rightward = -1.0f;
		std::cout << "A pressed" << std::endl;
	}
	else if (key == 'D')
	{
		this->m_rightward = 1.0f;
		std::cout << "D pressed" << std::endl;
	}
	else if (key == 'Q')
	{
		this->m_upward = 1.0f;
		std::cout << "Q pressed" << std::endl;
	}
	else if (key == 'E')
	{
		this->m_upward = -1.0f;
		std::cout << "E pressed" << std::endl;
	}
	else if (key == '1')
	{
		if (name == "PERSPECTIVE_CAMERA")
			perspectiveMode = true;
	}
	else if (key == '2')
	{
		if (name == "PERSPECTIVE_CAMERA")
			perspectiveMode = false;
	}
}

void Camera::onKeyUp(int key)
{
	this->m_forward = 0.0f;
	this->m_rightward = 0.0f;
	this->m_upward = 0.0f;
}

void Camera::onMouseMove(const Point& mouse_pos)
{

	int width = (AppWindow::getInstance()->getClientWindowRect().right - AppWindow::getInstance()->getClientWindowRect().left);
	int height = (AppWindow::getInstance()->getClientWindowRect().bottom - AppWindow::getInstance()->getClientWindowRect().top);

	if (name != "TOPDOWN_CAMERA")
	{
		m_rot_x += (mouse_pos.m_y - (height / 2.0f)) * EngineTime::getDeltaTime() * 0.5f;
		m_rot_y += (mouse_pos.m_x - (width / 2.0f)) * EngineTime::getDeltaTime() * 0.5f;
	}

	InputSystem::get()->setCursorPosition(Point((int)(width / 2.0f), (int)(height / 2.0f)));

}

void Camera::onLeftMouseDown(const Point& mouse_pos)
{

}

void Camera::onLeftMouseUp(const Point& mouse_pos)
{
}

void Camera::onRightMouseDown(const Point& mouse_pos)
{
}

void Camera::onRightMouseUp(const Point& mouse_pos)
{
}
