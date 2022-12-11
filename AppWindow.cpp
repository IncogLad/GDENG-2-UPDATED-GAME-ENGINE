#include "AppWindow.h"
#include <Windows.h>

#include "BaseComponentSystem.h"
#include "InputSystem.h"
#include "DeviceContext.h"
#include "EngineTime.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "CameraHandler.h"
#include "PhysicsComponent.h"
#include "PhysicsSystem.h"
#include "RenderTexture.h"
#include "ShaderLibrary.h"
#include "TextureManager.h"
#include "UISystem.h"
#include "JsonParser.h"

AppWindow* AppWindow::sharedInstance = nullptr;

AppWindow* AppWindow::getInstance()
{
	return sharedInstance;
}

void AppWindow::initialize()
{
	sharedInstance = new AppWindow();
	sharedInstance->init();
}

void AppWindow::destroy()
{
	if(sharedInstance != NULL)
	{
		sharedInstance->onDestroy();
	}
}

AppWindow::AppWindow()
{
}


AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	Window::onCreate();
	InputSystem::get()->addListener(this);
	BaseComponentSystem::initialize();
	GraphicsEngine::getInstance()->initialize();
	
	CameraHandler::initialize();
	
	UISystem::initialize();

	UISystem::getInstance()->initImGUI(this->m_hwnd);

	m_swap_chain = GraphicsEngine::getInstance()->createSwapChain();
	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);
	//ShaderLibrary::initialize();
	
	GameObjectManager::initialize();
	ShaderLibrary::initialize();

	GraphicsEngine::getInstance()->createRenderTexture(rc.right - rc.left, rc.bottom - rc.top);
	
	GameObjectManager::getInstance()->initializeCube("cube0", 0);
	GameObjectManager::getInstance()->initializeCube("cube1", 0);
	GameObjectManager::getInstance()->initializeCube("cube2", 0);

	GameObjectManager::getInstance()->initializeCube("plane", 1);
	GameObjectManager::getInstance()->initializeMesh();

	GameObjectManager::getInstance()->populateObjectList();
	
	GameObjectManager::getInstance()->initializeQuadConst();
	GameObjectManager::getInstance()->initializeCubeConst();

	JsonParser::initialize();
	

}

void AppWindow::onUpdate()
{
	Window::onUpdate();

	InputSystem::get()->update();
	BaseComponentSystem::getInstance()->getPhysicsSystem()->updateAllComponents();
	//////////////RENDER EVERY VIEW TO TEXTURE///////////////////
	for (auto const& tempRT : GraphicsEngine::getInstance()->getRenderTextureList()) {
		//std::cout << GraphicsEngine::getInstance()->getCurrentRenderedTexture()->getName() << std::endl;
		GraphicsEngine::getInstance()->setCurrentRenderTexture(tempRT);
		
		CameraHandler::getInstance()->setCurrentCamera(tempRT->getName());
		GraphicsEngine::getInstance()->RenderToTexture(this->m_swap_chain);

		//Draw Everything
		for (auto const& i : GameObjectManager::getInstance()->getQuadList()) {
			i->draw();
		}

		for (auto const& i : GameObjectManager::getInstance()->getCubeList()) {
			//std::cout << i->getName() << std::endl;
			i->draw();
		}

		for (auto const& i : GameObjectManager::getInstance()->getMeshList()) {
			//std::cout<<i->getName() << std::endl;
			i->draw();
		}


		//CameraHandler::getInstance()->update();
	}
	
	GraphicsEngine::getInstance()->SetBackBufferRenderTarget(this->m_swap_chain);
	////////////////////////////////////////////////

	//CLEAR THE RENDER TARGET 
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,0.3, 0.3, 0.3, 1);

	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = getClientWindowRect();
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	UISystem::getInstance()->updateNewFrame();

	UISystem::getInstance()->update();

	m_swap_chain->present(true);

}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_swap_chain->release();
	ShaderLibrary::destroy();
	GraphicsEngine::getInstance()->release();
	UISystem::getInstance()->destroy();

}

void AppWindow::onFocus()
{
	InputSystem::get()->addListener(this);
}

void AppWindow::onKillFocus()
{
	InputSystem::get()->removeListener(this);
}

void AppWindow::onKeyDown(int key)
{
	if (key == 'W')
	{
		//m_rot_x += 3.14f*m_delta_time;
		//m_forward = 1.0f;
	}
	else if (key == 'S')
	{
		//m_rot_x -= 3.14f*m_delta_time;
		//m_forward = -1.0f;
	}
	else if (key == 'A')
	{
		//m_rot_y += 3.14f*m_delta_time;
		//m_rightward = -1.0f;
	}
	else if (key == 'D')
	{
		//m_rot_y -= 3.14f*m_delta_time;
		//m_rightward = 1.0f;
	}
}

void AppWindow::onKeyUp(int key)
{
	//m_forward = 0.0f;
	//m_rightward = 0.0f;
}

void AppWindow::onMouseMove(const Point& mouse_pos)
{
	/*int width = (this->getClientWindowRect().right - this->getClientWindowRect().left);
	int height = (this->getClientWindowRect().bottom - this->getClientWindowRect().top);



	m_rot_x += (mouse_pos.m_y - (height / 2.0f)) * EngineTime::getDeltaTime() * 0.5f;
	m_rot_y += (mouse_pos.m_x - (width / 2.0f)) * EngineTime::getDeltaTime() * 0.5f;



	InputSystem::get()->setCursorPosition(Point((int)(width / 2.0f), (int)(height / 2.0f)));*/


}

void AppWindow::onLeftMouseDown(const Point& mouse_pos)
{
}

void AppWindow::onLeftMouseUp(const Point& mouse_pos)
{
}

void AppWindow::onRightMouseDown(const Point& mouse_pos)
{
}

void AppWindow::onRightMouseUp(const Point& mouse_pos)
{
}