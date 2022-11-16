#include "MeshVertexBuffer.h"
#include "GraphicsEngine.h"


MeshVertexBuffer::MeshVertexBuffer() :m_layout(0), m_buffer(0)
{
}

bool MeshVertexBuffer::load(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, size_t size_byte_shader)
{
	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = size_vertex * size_list;
	buff_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = list_vertices;

	m_size_vertex = size_vertex;
	m_size_list = size_list;

	if (FAILED(GraphicsEngine::getInstance()->m_d3d_device->CreateBuffer(&buff_desc, &init_data, &m_buffer)))
	{
		return false;
	}

	D3D11_INPUT_ELEMENT_DESC layout_mesh[] =
	{
		//SEMANTIC NAME - SEMANTIC INDEX - FORMAT - INPUT SLOT - ALIGNED BYTE OFFSET - INPUT SLOT CLASS - INSTANCE DATA STEP RATE
		{"POSITION", 0,  DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,D3D11_INPUT_PER_VERTEX_DATA ,0},
		{"TEXCOORD", 0,  DXGI_FORMAT_R32G32_FLOAT, 0, 12,D3D11_INPUT_PER_VERTEX_DATA ,0 }
	};

	UINT size_layout = ARRAYSIZE(layout_mesh);


	if (FAILED(GraphicsEngine::getInstance()->m_d3d_device->CreateInputLayout(layout_mesh, size_layout, shader_byte_code, size_byte_shader, &m_layout)))
	{
		return false;	
	}

	return true;
}

UINT MeshVertexBuffer::getSizeVertexList()
{
	return this->m_size_list;
}

bool MeshVertexBuffer::release()
{
	m_layout->Release();
	m_buffer->Release();
	delete this;
	return true;
}


MeshVertexBuffer::~MeshVertexBuffer()
{
}