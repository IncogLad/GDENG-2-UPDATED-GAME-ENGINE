#pragma once
#include "AGameObject.h"
#include "ConstantBuffer.h"
#include "Resource.h"

#include "IndexBuffer.h"
#include "MeshVertexBuffer.h"



class Mesh : public Resource
{
public:
	Mesh(const wchar_t* full_path);
	~Mesh();
	MeshVertexBuffer* getVertexBuffer();
	IndexBuffer* getIndexBuffer();
	ConstantBuffer* getConstantBuffer();
	
private:
	constant cc;
	ConstantBuffer* m_constant_buffer;
	MeshVertexBuffer* m_vertex_buffer;
	IndexBuffer* m_index_buffer;

private:
	friend class DeviceContext;
};

