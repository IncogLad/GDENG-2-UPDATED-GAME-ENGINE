#include "AppWindow.h"
#include <Windows.h>
#include "InputSystem.h"
#include "DeviceContext.h"
#include "EngineTime.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "CameraHandler.h"
#include "RenderTexture.h"
#include "MeshManager.h"
#include "TextureManager.h"
#include "UISystem.h"

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
	GraphicsEngine::getInstance()->initialize();
	CameraHandler::initialize();
	//ShaderLibrary::getInstance()->initialize();
	
	UISystem::initialize();
	UISystem::getInstance()->initImGUI(this->m_hwnd);

	m_brick_tex = GraphicsEngine::getInstance()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\brick.png");
	m_mesh = GraphicsEngine::getInstance()->getMeshManager()->createMeshFromFile(L"Assets\\Meshes\\teapot.obj");

	m_swap_chain = GraphicsEngine::getInstance()->createSwapChain();
	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	
	Renderer::initialize();

	GraphicsEngine::getInstance()->createRenderTexture(rc.right - rc.left, rc.bottom - rc.top);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	//GraphicsEngine::getInstance()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	GraphicsEngine::getInstance()->compileVertexShader(L"VertexShaderAnim.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = GraphicsEngine::getInstance()->createVertexShader(shader_byte_code, size_shader);

	//Renderer::getInstance()->initializeQuadsAnim("1", shader_byte_code, size_shader);
	//Renderer::getInstance()->initializeQuadsAnim(list_anim2, shader_byte_code, size_shader);
	//Renderer::getInstance()->initializeQuadsAnim(list_anim3, shader_byte_code, size_shader);
	//Renderer::getInstance()->initializeQuads(list2, shader_byte_code, size_shader);
	//Renderer::getInstance()->initializeQuads(list3, shader_byte_code, size_shader);
	Renderer::getInstance()->initializeCube("cube0", shader_byte_code, size_shader, 0);
	Renderer::getInstance()->initializeCube("cube1", shader_byte_code, size_shader, 0);
	Renderer::getInstance()->initializeCube("cube2", shader_byte_code, size_shader, 0);

	Renderer::getInstance()->initializeCube("plane", shader_byte_code, size_shader, 1);

	

	/*for (int i = 0; i < 15; i++)
	{
		Renderer::getInstance()->initializeCube("card" + i, shader_byte_code, size_shader, 1);
	}*/

	/*for (int i = 0; i < 50; i++)
	{
		Renderer::getInstance()->initializeCube("0", shader_byte_code, size_shader, 0);
	}*/

	GraphicsEngine::getInstance()->releaseCompiledShader();

	//GraphicsEngine::getInstance()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	GraphicsEngine::getInstance()->compilePixelShader(L"PixelShaderAnim.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::getInstance()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::getInstance()->releaseCompiledShader();

	Renderer::getInstance()->initializeQuadConst();
	Renderer::getInstance()->initializeCubeConst();
	

}

void AppWindow::onUpdate()
{
	Window::onUpdate();

	InputSystem::get()->update();
	
	//////////////RENDER EVERY VIEW TO TEXTURE///////////////////
	for (auto const& tempRT : GraphicsEngine::getInstance()->getRenderTextureList()) {
		//std::cout << GraphicsEngine::getInstance()->getCurrentRenderedTexture()->getName() << std::endl;
		GraphicsEngine::getInstance()->setCurrentRenderTexture(tempRT);
		
		CameraHandler::getInstance()->setCurrentCamera(tempRT->getName());
		GraphicsEngine::getInstance()->RenderToTexture(this->m_swap_chain);

		//Draw Everything
		for (auto const& i : Renderer::getInstance()->getQuadList()) {
			i->draw();
		}

		for (auto const& i : Renderer::getInstance()->getCubeList()) {
			i->draw();
		}


		//MESH EXPERIMENT///////////////////////////
		//GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_mesh->getConstantBuffer());
		//GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_mesh->getConstantBuffer());

		//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
		GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexShader(m_vs);
		GraphicsEngine::getInstance()->getImmediateDeviceContext()->setPixelShader(m_ps);
		GraphicsEngine::getInstance()->getImmediateDeviceContext()->setTexture(m_ps, m_brick_tex);
		//SET THE VERTICES OF THE TRIANGLE TO DRAW
		GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexBuffer(m_mesh->getVertexBuffer());
		//SET THE INDICES OF THE TRIANGLE TO DRAW
		GraphicsEngine::getInstance()->getImmediateDeviceContext()->setIndexBuffer(m_mesh->getIndexBuffer());


		// FINALLY DRAW THE TRIANGLE
		GraphicsEngine::getInstance()->getImmediateDeviceContext()->drawIndexedTriangleList(m_mesh->getIndexBuffer()->getSizeIndexList(), 0, 0);
		/// ////////////////////////////////////

		CameraHandler::getInstance()->update();
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
	m_vs->release();
	m_ps->release();
	GraphicsEngine::getInstance()->release();
	//ShaderLibrary::getInstance()->destroy();
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
	move_cube = 1.0f;
}

void AppWindow::onLeftMouseUp(const Point& mouse_pos)
{
	move_cube = 0.0f;
}

void AppWindow::onRightMouseDown(const Point& mouse_pos)
{
	move_cube = -1.0f;
}

void AppWindow::onRightMouseUp(const Point& mouse_pos)
{
	move_cube = 0.0f;
}