#include "Quads.h"

#include "AppWindow.h"
#include "EngineTime.h"
#include "GameObjectManager.h"
#include "DeviceContext.h"
#include "ConstantBuffer.h"
#include "CameraHandler.h"
#include "ShaderLibrary.h"
#include "VertexBuffer.h"


Quads::Quads()
{
}

Quads::~Quads()
{
}

void Quads::initialize(std::string name)
{
	AGameObject::initialize(name);
}

void Quads::destroy()
{
	AGameObject::destroy();
}

void Quads::initBuffers()
{
	ShaderNames shader_names;
	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;
	ShaderLibrary::getInstance()->requestVertexShaderData(shader_names.BASE_VERTEX_SHADER_NAME, &shaderByteCode, &sizeShader);

	vertexAnim list_anim[] =
	{
		//X - Y - Z
		{Vector3D(-0.1f,-0.3f,0.0f),    Vector3D(-0.3f,-0.3f,0.0f),   Vector3D(1,1,0),  Vector3D(0,1,0)}, // POS1
		{Vector3D(-0.1f,0.95f,0.0f),     Vector3D(-0.3f,0.5f,0.0f),   Vector3D(1,1,0),  Vector3D(0,1,1)},// POS2
		{ Vector3D(0.1f,-0.95f,0.0f),    Vector3D(0.3f,-0.5f,0.0f),   Vector3D(0,1,1),  Vector3D(1,0,0)},// POS2
		{ Vector3D(0.1f,0.5f,0.0f),      Vector3D(0.3f,0.5f,0.0f),    Vector3D(1,1,1),  Vector3D(0,0,1)}

	};

	//SLIDE 13 CHALLENGE
	vertexAnim list_anim2[] =
	{
		//X - Y - Z
		{Vector3D(-0.78f,-0.8f,0.0f),    Vector3D(-0.32f,-0.11f,0.0f),   Vector3D(0,0,0),  Vector3D(0,1,0) }, // POS1
		{Vector3D(-0.9f,0.08f,0.0f),     Vector3D(-0.11f,0.78f,0.0f),    Vector3D(1,1,0),  Vector3D(0,1,1) }, // POS2
		{ Vector3D(0.1f,-0.2f,0.0f),     Vector3D(0.75f,-0.73f,0.0f),   Vector3D(0,0,1),  Vector3D(1,0,0) },// POS2
		{ Vector3D(-0.05f,0.15f,0.0f),      Vector3D(0.88f,0.77f,0.0f),    Vector3D(1,1,1),  Vector3D(0,0,1) }

	};

	m_vb = GraphicsEngine::getInstance()->createVertexBuffer();
	m_vb->load(list_anim, sizeof(vertex), 4, shaderByteCode, sizeShader);
}

void Quads::initAnimBuffers()
{
	ShaderNames shader_names;
	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;
	ShaderLibrary::getInstance()->requestVertexShaderData(shader_names.BASE_VERTEX_SHADER_NAME, &shaderByteCode, &sizeShader);

	vertexAnim list_anim[] =
	{
		//X - Y - Z
		{Vector3D(-0.1f,-0.3f,0.0f),   Vector3D(1,1,0),  Vector3D(0,1,0)}, // POS1
		{Vector3D(-0.1f,0.95f,0.0f),   Vector3D(1,1,0),  Vector3D(0,1,1)},// POS2
		{Vector3D(0.1f,-0.95f,0.0f),   Vector3D(0,1,1),  Vector3D(1,0,0)},// POS2
		{Vector3D(0.1f,0.5f,0.0f),    Vector3D(1,1,1),  Vector3D(0,0,1)}

	};

	//SLIDE 13 CHALLENGE
	vertexAnim list_anim2[] =
	{
		//X - Y - Z
		{Vector3D(-0.78f,-0.8f,0.0f),    Vector3D(-0.32f,-0.11f,0.0f),   Vector3D(0,0,0),  Vector3D(0,1,0) }, // POS1
		{Vector3D(-0.9f,0.08f,0.0f),     Vector3D(-0.11f,0.78f,0.0f),    Vector3D(1,1,0),  Vector3D(0,1,1) }, // POS2
		{ Vector3D(0.1f,-0.2f,0.0f),     Vector3D(0.75f,-0.73f,0.0f),   Vector3D(0,0,1),  Vector3D(1,0,0) },// POS2
		{ Vector3D(-0.05f,0.15f,0.0f),      Vector3D(0.88f,0.77f,0.0f),    Vector3D(1,1,1),  Vector3D(0,0,1) }

	};

	m_vb = GraphicsEngine::getInstance()->createVertexBuffer();
	m_vb->load(list_anim, sizeof(vertex), 4, shaderByteCode, sizeShader);
}

void Quads::initConstBuffers()
{
	cc.m_angle = 0.0f;
	m_cb = GraphicsEngine::getInstance()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));
}

void Quads::draw()
{
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

	// FINALLY DRAW THE TRIANGLE
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);
}

void Quads::releaseBuffers()
{
}

void Quads::updatePosition()
{
	//WORLD MATRIX
	cc.m_world.setIdentity();
	Matrix4x4 allMatrix; allMatrix.setIdentity();

	//Vector3D moveX = Vector3D(AppWindow::getInstance()->move_cube, 0, 0);
	//this->setPosition(moveX);

	Matrix4x4 translationMatrix; translationMatrix.setIdentity(); translationMatrix.setTranslation(this->getLocalPosition());
	Matrix4x4 scaleMatrix; scaleMatrix.setIdentity(); scaleMatrix.setScale(this->getLocalScale());
	Vector3D rotation = getLocalRotation();

	Matrix4x4 w_zMatrix; w_zMatrix.setIdentity();
	w_zMatrix.setRotationZ(rotation.m_z);
	allMatrix *= w_zMatrix;

	Matrix4x4 w_xMatrix; w_xMatrix.setIdentity();
	w_xMatrix.setRotationX(rotation.m_x);
	allMatrix *= w_xMatrix;

	Matrix4x4 w_yMatrix; w_yMatrix.setIdentity();
	w_yMatrix.setRotationY(rotation.m_y);
	allMatrix *= w_yMatrix;

	//scaleMatrix *= rotMatrix;
	allMatrix *= scaleMatrix;
	allMatrix *= translationMatrix;
	cc.m_world = allMatrix;

	//VIEW MATRIX
	cc.m_view.setIdentity();
	cc.m_view = CameraHandler::getInstance()->getCurrentCameraViewMatrix();

	//PROJ MATRIX
	int width = (AppWindow::getInstance()->getClientWindowRect().right - AppWindow::getInstance()->getClientWindowRect().left);
	int height = (AppWindow::getInstance()->getClientWindowRect().bottom - AppWindow::getInstance()->getClientWindowRect().top);

	//cc.m_proj.setOrthoLH(1.57f, ((float)width / (float)height), 0.1f, 1000.0f);
	cc.m_proj.setPerspectiveFovLH(1.57, ((float)width / (float)height), 0.1f, 1000.0f);

	m_cb->update(GraphicsEngine::getInstance()->getImmediateDeviceContext(), &cc);


}
