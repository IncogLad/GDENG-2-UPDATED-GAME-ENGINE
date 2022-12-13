#pragma once
#include "AGameObject.h"
#include "ConstantBuffer.h"
#include "Resource.h"

#include "IndexBuffer.h"
#include "MeshVertexBuffer.h"
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

	MeshVertexBuffer* getVertexBuffer();
	IndexBuffer* getIndexBuffer();

	bool getEnabled();
	void setEnabled(bool enable);

private:
	MeshVertexBuffer* m_vertex_buffer;
	IndexBuffer* m_index_buffer;
	ConstantBuffer* m_cb;

	constant cc;

	Vector3D rotation;
	Vector3D translation;
	Vector3D scaling;
	bool i_trans;
	bool i_scale;

	bool isEnabled = true;

	Texture* brick_tex;
private:
	friend class DeviceContext;
};

