#pragma once
#include "AGameObject.h"
#include "ConstantBuffer.h"
#include "Resource.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture.h"


class Mesh : public Resource, public AGameObject
{
public:
	Mesh(const wchar_t* full_path);
	~Mesh();

	void initialize(std::string name) override;
	void destroy() override;

	void draw() override;
	void updateTransforms();

	const VertexBuffer* getVertexBuffer();
	const IndexBuffer* getIndexBuffer();

private:
	VertexBuffer* m_vertex_buffer;
	IndexBuffer* m_index_buffer;
	ConstantBuffer* m_cb;

	constant cc;

	Vector3D rotation;
	Vector3D translation;
	Vector3D scaling;

	Texture* brick_tex;
private:
	friend class DeviceContext;
};

