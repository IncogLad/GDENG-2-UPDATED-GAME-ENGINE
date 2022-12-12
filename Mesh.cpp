#include "Mesh.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include <locale>
#include <codecvt>

#include "AppWindow.h"
#include "CameraHandler.h"
#include "GraphicsEngine.h"
#include "VertexMesh.h"
#include "DeviceContext.h"
#include "EngineTime.h"
#include "ShaderLibrary.h"
#include "TextureManager.h"

Mesh::Mesh(const wchar_t* full_path) : Resource(full_path)
{
	tinyobj::attrib_t attribs;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string warn;
	std::string err;

	std::string inputfile = std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(full_path);

	bool res = tinyobj::LoadObj(&attribs, &shapes, &materials, &warn, &err, inputfile.c_str());

	if (!err.empty()) throw std::exception("Mesh not created successfully");

	if (!res) throw std::exception("Mesh not created successfully");

	if (shapes.size() > 1) throw std::exception("Mesh not created successfully");


	std::vector<VertexMesh> list_vertices;
	std::vector<unsigned int> list_indices;

	size_t vertex_buffer_size = 0;


	for (size_t s = 0; s < shapes.size(); s++)
	{
		vertex_buffer_size += shapes[s].mesh.indices.size();
	}

	list_vertices.reserve(vertex_buffer_size);
	list_indices.reserve(vertex_buffer_size);

	size_t index_global_offset = 0;

	for (size_t s = 0; s < shapes.size(); s++)
	{
		size_t index_offset = 0;

		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
		{
			unsigned char num_face_verts = shapes[s].mesh.num_face_vertices[f];

			Vector3D vertices_face[3];
			Vector2D texcoords_face[3];

			for (unsigned char v = 0; v < num_face_verts; v++)
			{
				tinyobj::index_t index = shapes[s].mesh.indices[index_offset + v];

				tinyobj::real_t vx = attribs.vertices[(int)index.vertex_index * 3 + 0];
				tinyobj::real_t vy = attribs.vertices[(int)index.vertex_index * 3 + 1];
				tinyobj::real_t vz = attribs.vertices[(int)index.vertex_index * 3 + 2];

				tinyobj::real_t tx = 0;
				tinyobj::real_t ty = 0;
				if (attribs.texcoords.size())
				{
					tx = attribs.texcoords[(int)index.texcoord_index * 2 + 0];
					ty = attribs.texcoords[(int)index.texcoord_index * 2 + 1];
				}
				vertices_face[v] = Vector3D(vx, vy, vz);
				texcoords_face[v] = Vector2D(tx, ty);

				VertexMesh vertex(Vector3D(vx, vy, vz), Vector2D(tx, ty));
				list_vertices.push_back(vertex);

				list_indices.push_back((unsigned int)index_global_offset + v);
			}


			index_offset += num_face_verts;
			index_global_offset += num_face_verts;
		}
	}

	ShaderNames shader_names;
	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;
	ShaderLibrary::getInstance()->requestVertexShaderData(shader_names.TEXTURED_VERTEX_SHADER_NAME, &shaderByteCode, &sizeShader);

	GraphicsEngine::getInstance()->getVertexMeshLayoutShaderByteCodeAndSize(&shaderByteCode, &sizeShader);
	m_vertex_buffer = GraphicsEngine::getInstance()->createMeshVertexBuffer();
	m_vertex_buffer->load(&list_vertices[0], sizeof(VertexMesh),list_vertices.size(), shaderByteCode, sizeShader);

	m_index_buffer = GraphicsEngine::getInstance()->createIndexBuffer();
	m_index_buffer->load(&list_indices[0], (UINT)list_indices.size());

	m_cb = GraphicsEngine::getInstance()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));

	brick_tex = GraphicsEngine::getInstance()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\brick.png");
}


Mesh::~Mesh()
{
}

void Mesh::initialize(std::string name)
{
	AGameObject::initialize(name);
	this->name = name;
	this->tag = "mesh";
	translation = getLocalPosition();
	scaling = getLocalScale();
	if (name == "bunny")
	{
		setPosition(Vector3D(5, 0, 0));
		setScale( Vector3D(10, 10, 10));
	}
	if (name == "armadillo")
	{
		setPosition(Vector3D(-5, 0, 0));
	}
	if (name == "teapot") {
		setScale(Vector3D(2, 2, 2));
	}
	
	
}

void Mesh::destroy()
{
	AGameObject::destroy();
}

void Mesh::draw()
{
	ShaderNames shader_names;
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setRenderConfig
	(
		ShaderLibrary::getInstance()->getVertexShader(shader_names.TEXTURED_VERTEX_SHADER_NAME),
		ShaderLibrary::getInstance()->getPixelShader(shader_names.TEXTURED_PIXEL_SHADER_NAME)
	);

	updateTransforms();

	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexShader(ShaderLibrary::getInstance()->getVertexShader(shader_names.TEXTURED_VERTEX_SHADER_NAME));
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setPixelShader(ShaderLibrary::getInstance()->getPixelShader(shader_names.TEXTURED_PIXEL_SHADER_NAME));


	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(ShaderLibrary::getInstance()->getVertexShader(shader_names.TEXTURED_VERTEX_SHADER_NAME), m_cb);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(ShaderLibrary::getInstance()->getPixelShader(shader_names.TEXTURED_PIXEL_SHADER_NAME), m_cb);
	if (this->tag == "capsule" || this->tag == "sphere")
	{
		GraphicsEngine::getInstance()->getImmediateDeviceContext()->setPixelShader(ShaderLibrary::getInstance()->getPixelShader(shader_names.BASE_PIXEL_SHADER_NAME));
	}
	else
	{
		GraphicsEngine::getInstance()->getImmediateDeviceContext()->setPSTexture(ShaderLibrary::getInstance()->getPixelShader(shader_names.TEXTURED_PIXEL_SHADER_NAME), brick_tex);
	}
	

	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexBuffer(m_vertex_buffer);

	//SET THE INDECES OF THE TRIANGLE TO DRAW
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setIndexBuffer(m_index_buffer);

	// FINALLY DRAW THE TRIANGLE
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->drawIndexedTriangleList(m_index_buffer->getSizeIndexList(), 0, 0);

}

void Mesh::updateTransforms()
{
	//WORLD MATRIX
	cc.m_world.setIdentity();
	Matrix4x4 allMatrix; allMatrix.setIdentity();
	float speed = 1.0f;

	Matrix4x4 translationMatrix; translationMatrix.setIdentity(); translationMatrix.setTranslation(this->getLocalPosition());
	Matrix4x4 scaleMatrix; scaleMatrix.setIdentity(); scaleMatrix.setScale(this->getLocalScale());
	
	//std::cout << localRotation.m_z << std::endl;

	Matrix4x4 w_zMatrix; w_zMatrix.setIdentity();
	w_zMatrix.setRotationZ(getLocalRotation().m_z);
	allMatrix *= w_zMatrix;

	Matrix4x4 w_xMatrix; w_xMatrix.setIdentity();
	w_xMatrix.setRotationX(getLocalRotation().m_x);
	allMatrix *= w_xMatrix;

	Matrix4x4 w_yMatrix; w_yMatrix.setIdentity();
	w_yMatrix.setRotationY(getLocalRotation().m_y);
	allMatrix *= w_yMatrix;

	//scaleMatrix *= rotMatrix;
	allMatrix *= scaleMatrix;
	allMatrix *= translationMatrix;
	//allMatrix *= localMatrix;
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

MeshVertexBuffer* Mesh::getVertexBuffer()
{
	return m_vertex_buffer;
}

IndexBuffer* Mesh::getIndexBuffer()
{
	return m_index_buffer;
}