#include "Cube.h"

#include <random>

#include "AppWindow.h"
#include "GameObjectManager.h"
#include "DeviceContext.h"
#include "ConstantBuffer.h"
#include "EngineTime.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "CameraHandler.h"
#include "PhysicsComponent.h"
#include "ShaderLibrary.h"


Cube::Cube()
{
}

Cube::~Cube()
{
}

void Cube::initialize(std::string name)
{
	AGameObject::initialize(name);
	
	rotation = getLocalRotation();
	translation = getLocalPosition();
	scaling = getLocalScale();
	i_scale = false;
	i_trans = false;

	
	
}

void Cube::destroy()
{
	AGameObject::destroy();
}

void Cube::initBuffers(int num = 0)
{
	if (num == 0)
	{
		this->tag = "cube";
	}
	else if (num == 1)
	{
		this->tag = "plane";
	}

	ShaderNames shader_names;
	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;
	ShaderLibrary::getInstance()->requestVertexShaderData(shader_names.BASE_VERTEX_SHADER_NAME, &shaderByteCode, &sizeShader);

	this->num = num;
	vertexCube vertex_list[] =
	{
		//X - Y - Z
		//FRONT FACE
		{Vector3D(-1.0f,-1.0f,-1.0f),    Vector3D(1,0,1),  Vector3D(0.2f,0,1) },
		{Vector3D(-1.0f,1.0f,-1.0f),    Vector3D(1,1,0), Vector3D(0,0.2f,0) },
		{ Vector3D(1.0f,1.0f,-1.0f),   Vector3D(1,1,0),  Vector3D(0.2f,1,0) },
		{ Vector3D(1.0f,-1.0f,-1.0f),     Vector3D(0,0,1), Vector3D(0.2f,0,0) },

		//BACK FACE
		{ Vector3D(1.0f,-1.0f,1.0f),    Vector3D(1,0,0), Vector3D(0,0.2f,0) },
		{ Vector3D(1.0f,1.0f,1.0f),    Vector3D(0,1,1), Vector3D(0,0.2f,0.2f) },
		{ Vector3D(-1.0f,1.0f,1.0f),   Vector3D(0,0,1),  Vector3D(0,0.2f,0.2f) },
		{ Vector3D(-1.0f,-1.0f,1.0f),     Vector3D(0,1,0), Vector3D(1,0,0) }

	};

	vertexCube vertex_list_white_cube[] =
	{
		//X - Y - Z
		//FRONT FACE
		{Vector3D(-1.0f,-1.0f,-1.0f),    Vector3D(1,1,1),  Vector3D(1,1,1) },
		{Vector3D(-1.0f,1.0f,-1.0f),    Vector3D(1,1,1),  Vector3D(1,1,1) },
		{ Vector3D(1.0f,1.0f,-1.0f),   Vector3D(1,1,1),  Vector3D(1,1,1) },
		{ Vector3D(1.0f,-1.0f,-1.0f),     Vector3D(1,1,1),  Vector3D(1,1,1) },

		//BACK FACE
		{ Vector3D(1.0f,-1.0f,1.0f),    Vector3D(1,1,1),  Vector3D(1,1,1) },
		{ Vector3D(1.0f,1.0f,1.0f),    Vector3D(1,1,1),  Vector3D(1,1,1)},
		{ Vector3D(-1.0f,1.0f,1.0f),   Vector3D(1,1,1),  Vector3D(1,1,1)},
		{ Vector3D(-1.0f,-1.0f,1.0f),     Vector3D(1,1,1),  Vector3D(1,1,1)}

	};

	vertexCube plane_vertex_list[] =
	{
		//X - Y - Z
		//FRONT FACE
		{Vector3D(-5.0f,0.0f,-5.0f),    Vector3D(1,1,1),  Vector3D(1,1,1) },
		{Vector3D(-5.0f,0.0f,-5.0f),    Vector3D(1,1,1), Vector3D(1,1,1) },
		{ Vector3D(5.0f,0.0f,-5.0f),   Vector3D(1,1,1),  Vector3D(1,1,1) },
		{ Vector3D(5.0f,0.0f,-5.0f),     Vector3D(1,1,1), Vector3D(1,1,1) },

		//BACK FACE
		{ Vector3D(5.0f,0.0f,5.0f),    Vector3D(1,1,1), Vector3D(1,1,1) },
		{ Vector3D(5.0f,0.0f,5.0f),    Vector3D(1,1,1), Vector3D(1,1,1) },
		{ Vector3D(-5.0f,0.0f,5.0f),   Vector3D(1,1,1),  Vector3D(1,1,1) },
		{ Vector3D(-5.0f,0.0f,5.0f),     Vector3D(1,1,1), Vector3D(1,1,1) }

	};

	m_vb = GraphicsEngine::getInstance()->createVertexBuffer();
	if (this->num == 0) {
		UINT size_list = ARRAYSIZE(vertex_list_white_cube);
		//std::cout << list->position.m_x << std::endl;
		m_vb->load(vertex_list_white_cube, sizeof(vertexCube), size_list, shaderByteCode, sizeShader);
	}
	else {
		UINT size_list = ARRAYSIZE(plane_vertex_list);
		//std::cout << list->position.m_x << std::endl;
		m_vb->load(plane_vertex_list, sizeof(vertexCube), size_list, shaderByteCode, sizeShader);
	}

	unsigned int index_list[] =
	{
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		1,6,5,
		5,2,1,
		//BOTTOM SIDE
		7,0,3,
		3,4,7,
		//RIGHT SIDE
		3,2,5,
		5,4,3,
		//LEFT SIDE
		7,6,1,
		1,0,7
	};

	m_ib = GraphicsEngine::getInstance()->createIndexBuffer();
	UINT size_index_list = ARRAYSIZE(index_list);
	m_ib->load(index_list, size_index_list);

}

void Cube::initConstBuffers()
{
	cc.m_angle = 0.0f;
	m_cb = GraphicsEngine::getInstance()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));
}

void Cube::draw()
{
	//std::cout << "Component " << component_list_[0]->getName() << std::endl;
	ShaderNames shader_names;
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setRenderConfig
	(
		ShaderLibrary::getInstance()->getVertexShader(shader_names.BASE_VERTEX_SHADER_NAME), 
		ShaderLibrary::getInstance()->getPixelShader(shader_names.BASE_PIXEL_SHADER_NAME)
	);

	updatePosition();


	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexShader(ShaderLibrary::getInstance()->getVertexShader(shader_names.BASE_VERTEX_SHADER_NAME));
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setPixelShader(ShaderLibrary::getInstance()->getPixelShader(shader_names.BASE_PIXEL_SHADER_NAME));


	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(ShaderLibrary::getInstance()->getVertexShader(shader_names.BASE_VERTEX_SHADER_NAME), m_cb);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(ShaderLibrary::getInstance()->getPixelShader(shader_names.BASE_PIXEL_SHADER_NAME), m_cb);

	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexBuffer(m_vb);

	//SET THE INDECES OF THE TRIANGLE TO DRAW
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setIndexBuffer(m_ib);	

	// FINALLY DRAW THE TRIANGLE
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(),0, 0);

}

void Cube::releaseBuffers()
{

}

bool Cube::getEnabled()
{
	return isEnabled;
}

void Cube::setEnabled(bool enable)
{
	isEnabled = enable;
}

void Cube::updatePosition()
{
	float speed = 1.5f / 5;

	//WORLD MATRIX
	cc.m_world.setIdentity();
	Matrix4x4 allMatrix; allMatrix.setIdentity();
	
	Matrix4x4 translationMatrix; translationMatrix.setIdentity(); translationMatrix.setTranslation(this->getLocalPosition());
	Matrix4x4 scaleMatrix; scaleMatrix.setIdentity(); scaleMatrix.setScale(this->getLocalScale());
	
	//std::cout << this->name << ": " << localPosition.m_x << ", " << localPosition.m_y << ", " << localPosition.m_z << std::endl;
	

	Matrix4x4 w_xMatrix; w_xMatrix.setIdentity();
	w_xMatrix.setRotationX(localRotation.m_x);
	
	Matrix4x4 w_yMatrix; w_yMatrix.setIdentity();
	w_yMatrix.setRotationY(localRotation.m_y);

	Matrix4x4 w_zMatrix; w_zMatrix.setIdentity();
	w_zMatrix.setRotationZ(localRotation.m_z);
	
	allMatrix *= w_xMatrix;
	allMatrix *= w_yMatrix;
	allMatrix *= w_zMatrix;

	allMatrix *= scaleMatrix;
	allMatrix *= translationMatrix;
	
	cc.m_world = allMatrix;

	//VIEW MATRIX
	cc.m_view.setIdentity();
	cc.m_view = CameraHandler::getInstance()->getCurrentCameraViewMatrix();
	//std::cout << CameraHandler::getInstance()->getCurrentCamera()->getName() << std::endl;
	
	//PROJ MATRIX
	int width = (AppWindow::getInstance()->getClientWindowRect().right - AppWindow::getInstance()->getClientWindowRect().left);
	int height = (AppWindow::getInstance()->getClientWindowRect().bottom - AppWindow::getInstance()->getClientWindowRect().top);

	if (CameraHandler::getInstance()->getCurrentCamera()->perspectiveMode)
	{
		cc.m_proj.setPerspectiveFovLH(1.57, ((float)width / (float)height), 0.1f, 1000.0f);
	}
	else
	{
		cc.m_proj.setOrthoLH(1.57f, ((float)width / (float)height), 0.1f, 1000.0f);
	}

	//std::cout << getLocalPosition().m_x << ", " << getLocalPosition().m_y << ", " << getLocalPosition().m_z << std::endl;

	m_cb->update(GraphicsEngine::getInstance()->getImmediateDeviceContext(), &cc);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setRasterizerState(CameraHandler::getInstance()->getCurrentCamera()->m_rs);
}
