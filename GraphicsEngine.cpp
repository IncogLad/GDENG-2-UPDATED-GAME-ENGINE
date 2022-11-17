#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "MeshVertexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "IndexBuffer.h"

#include <d3dcompiler.h>

#include "RenderTexture.h"
#include "TextureManager.h"
#include "RasterizerState.h"
#include "MeshManager.h"

GraphicsEngine* GraphicsEngine::sharedInstance = nullptr;

GraphicsEngine::GraphicsEngine()
{
}

void GraphicsEngine::initialize()
{
	sharedInstance = new GraphicsEngine();
	sharedInstance->init();
}

void GraphicsEngine::destroy()
{
	if (sharedInstance != NULL)
	{
		sharedInstance->release();
	}
}

GraphicsEngine* GraphicsEngine::getInstance()
{
	return sharedInstance;
}

bool GraphicsEngine::init()
{
	D3D_DRIVER_TYPE driver_types[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};
	UINT num_driver_types = ARRAYSIZE(driver_types);

	D3D_FEATURE_LEVEL feature_levels[] =
	{
		D3D_FEATURE_LEVEL_11_0
	};
	UINT num_feature_levels = ARRAYSIZE(feature_levels);

	HRESULT res = 0;

	for (UINT driver_type_index = 0; driver_type_index < num_driver_types;)
	{
		res = D3D11CreateDevice(NULL, driver_types[driver_type_index], NULL, NULL, feature_levels,
		                        num_feature_levels, D3D11_SDK_VERSION, &m_d3d_device, &m_feature_level, &m_imm_context);
		if (SUCCEEDED(res))
			break;
		++driver_type_index;
	}
	if (FAILED(res))
	{
		return false;
	}

	m_imm_device_context = new DeviceContext(m_imm_context);

	m_d3d_device->QueryInterface(__uuidof(IDXGIDevice), (void**)&m_dxgi_device);
	m_dxgi_device->GetParent(__uuidof(IDXGIAdapter), (void**)&m_dxgi_adapter);
	m_dxgi_adapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_dxgi_factory);

	m_tex_manager = new TextureManager();


	m_mesh_manager = new MeshManager();

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	compileVertexShader(L"VertexMeshLayoutShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	::memcpy(m_mesh_layout_byte_code, shader_byte_code, size_shader);
	m_mesh_layout_size = size_shader;
	releaseCompiledShader();

	return true;
}


bool GraphicsEngine::release()
{
	if (m_vs)m_vs->Release();
	if (m_ps)m_ps->Release();

	if (m_vsblob)m_vsblob->Release();
	if (m_psblob)m_psblob->Release();

	m_dxgi_device->Release();
	m_dxgi_adapter->Release();
	m_dxgi_factory->Release();

	m_imm_device_context->release();
	delete m_tex_manager;
	delete m_mesh_manager;
	m_d3d_device->Release();

	
	m_currentRenderTexture->Shutdown();
	
	return true;
}

GraphicsEngine::~GraphicsEngine()
{
}

SwapChain* GraphicsEngine::createSwapChain()
{
	return new SwapChain();
}


DeviceContext* GraphicsEngine::getImmediateDeviceContext()
{
	return this->m_imm_device_context;
}

VertexBuffer* GraphicsEngine::createVertexBuffer()
{
	return new VertexBuffer();
}

MeshVertexBuffer* GraphicsEngine::createMeshVertexBuffer()
{
	return new MeshVertexBuffer();
}

ConstantBuffer* GraphicsEngine::createConstantBuffer()
{
	return new ConstantBuffer();
}

IndexBuffer* GraphicsEngine::createIndexBuffer()
{
	return new IndexBuffer();
}

VertexShader* GraphicsEngine::createVertexShader(const void* shader_byte_code, size_t byte_code_size)
{
	VertexShader* vs = new VertexShader();

	if (!vs->init(shader_byte_code, byte_code_size))
	{
		vs->release();
		return nullptr;
	}

	return vs;
}

PixelShader* GraphicsEngine::createPixelShader(const void* shader_byte_code, size_t byte_code_size)
{
	PixelShader* ps = new PixelShader();

	if (!ps->init(shader_byte_code, byte_code_size))
	{
		ps->release();
		return nullptr;
	}

	return ps;
}

bool GraphicsEngine::createRenderTexture(int textureWidth, int textureHeight)
{
	bool result;
	RenderTexture* topdown_view = new RenderTexture();
	result = topdown_view->Initialize("TOPDOWN_CAMERA", this->m_d3d_device, textureWidth, textureHeight);
	if (!result)
	{
		return false;
	}
	renderTextureList.push_back(topdown_view);
	renderTextureTable["TOPDOWN_CAMERA"] = topdown_view;

	RenderTexture* scene_view = new RenderTexture();
	result = scene_view->Initialize("SCENE_CAMERA", this->m_d3d_device, textureWidth, textureHeight);
	if (!result)
	{
		return false;
	}
	renderTextureList.push_back(scene_view);
	renderTextureTable["SCENE_CAMERA"] = scene_view;

	RenderTexture* perspective_view = new RenderTexture();
	result = perspective_view->Initialize("PERSPECTIVE_CAMERA",this->m_d3d_device, textureWidth, textureHeight);
	if (!result)
	{
		return false;
	}
	renderTextureList.push_back(perspective_view);
	renderTextureTable["PERSPECTIVE_CAMERA"] = perspective_view;

	
	RenderTexture* wireframe_view = new RenderTexture();
	result = wireframe_view->Initialize("WIREFRAME_CAMERA", this->m_d3d_device, textureWidth, textureHeight);
	if (!result)
	{
		return false;
	}
	renderTextureList.push_back(wireframe_view);
	renderTextureTable["WIREFRAME_CAMERA"] = wireframe_view;

	this->m_currentRenderTexture = topdown_view;
	
	return result;
}

RasterizerState* GraphicsEngine::createRasterizer_state(bool wireframe)
{
	RasterizerState* rs = new RasterizerState();

	if (!rs->init(wireframe))
	{
		rs->release();
		return nullptr;

	}
	return rs;
}


bool GraphicsEngine::compileVertexShader(const wchar_t* file_name, const char* entry_point_name,
                                         void** shader_byte_code, size_t* byte_code_size)
{
	ID3DBlob* error_blob = nullptr;
	if (!SUCCEEDED(
		D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "vs_5_0", 0, 0, &m_blob, &error_blob)))
	{
		if (error_blob) error_blob->Release();
		return false;
	}

	*shader_byte_code = m_blob->GetBufferPointer();
	*byte_code_size = m_blob->GetBufferSize();

	return true;
}

bool GraphicsEngine::compilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code,
                                        size_t* byte_code_size)
{
	ID3DBlob* error_blob = nullptr;
	if (!SUCCEEDED(
		D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "ps_5_0", 0, 0, &m_blob, &error_blob)))
	{
		if (error_blob) error_blob->Release();
		return false;
	}

	*shader_byte_code = m_blob->GetBufferPointer();
	*byte_code_size = m_blob->GetBufferSize();

	return true;
}

void GraphicsEngine::releaseCompiledShader()
{
	if (m_blob)m_blob->Release();
}

void GraphicsEngine::RenderToTexture(SwapChain* swap_chain)
{
	// Set the render target to be the render to texture.
	m_currentRenderTexture->SetRenderTarget(sharedInstance->m_imm_context, swap_chain->getDepthStencilView());

	// Clear the render to texture.
	m_currentRenderTexture->ClearRenderTarget(sharedInstance->m_imm_context, swap_chain->getDepthStencilView(), 0.0f, 1.0f, 0.0f, 1.0f);
}

void GraphicsEngine::SetBackBufferRenderTarget(SwapChain* swap_chain)
{
	// Set render target back to the swap chain's
	sharedInstance->m_imm_context->OMSetRenderTargets(1, &swap_chain->m_rtv, swap_chain->getDepthStencilView());
}

RenderTexture* GraphicsEngine::getCurrentRenderedTexture()
{
	return this->m_currentRenderTexture;
}

RenderTexture* GraphicsEngine::getRenderTextureOfType(String type)
{
	return this->renderTextureTable[type];
}

void GraphicsEngine::setCurrentRenderTexture(RenderTexture* rt)
{
	this->m_currentRenderTexture = rt;
}

std::list<RenderTexture*> GraphicsEngine::getRenderTextureList()
{
	return this->renderTextureList;
}

std::unordered_map<String, RenderTexture*> GraphicsEngine::getRenderTextureTable()
{
	return this->renderTextureTable;
}

TextureManager* GraphicsEngine::getTextureManager()
{
	return this->m_tex_manager;
}

MeshManager* GraphicsEngine::getMeshManager()
{
	return m_mesh_manager;
}

void GraphicsEngine::getVertexMeshLayoutShaderByteCodeAndSize(void** byte_code, size_t* size)
{
	*byte_code = m_mesh_layout_byte_code;
	*size = m_mesh_layout_size;
}
