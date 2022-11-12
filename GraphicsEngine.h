#pragma once
#include <d3d11.h>
#include <list>
#include <unordered_map>

typedef std::string String;

class SwapChain;
class DeviceContext;
class VertexBuffer;
class ConstantBuffer;
class VertexShader;
class PixelShader;
class IndexBuffer;
class UISystem;
class RenderTexture;
class Texture;
class TextureManager;
class RasterizerState;

class GraphicsEngine
{
public:
	GraphicsEngine();
	void initialize();
	void destroy();
	//Initialize the GraphicsEngine and DirectX 11 Device
	bool init();
	//Release all the resources loaded
	bool release();
	~GraphicsEngine();
public:
	SwapChain* createSwapChain();
	DeviceContext* getImmediateDeviceContext();
	VertexBuffer* createVertexBuffer();
	ConstantBuffer* createConstantBuffer();
	IndexBuffer* createIndexBuffer();
	VertexShader* createVertexShader(const void* shader_byte_code, size_t byte_code_size);
	PixelShader* createPixelShader(const void* shader_byte_code, size_t byte_code_size);
	bool createRenderTexture(int textureWidth, int textureHeight);
	RasterizerState* createRasterizer_state(bool wireframe);

	
public:
	bool compileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
	bool compilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);

	void releaseCompiledShader();

	void RenderToTexture(SwapChain* swap_chain);
	void SetBackBufferRenderTarget(SwapChain* swap_chain);

	RenderTexture* getCurrentRenderedTexture();
	RenderTexture* getRenderTextureOfType(String type);
	void setCurrentRenderTexture(RenderTexture* rt);
	std::list<RenderTexture*> getRenderTextureList();
	std::unordered_map<String, RenderTexture*> getRenderTextureTable();

	TextureManager* getTextureManager();
public:
	static GraphicsEngine* getInstance();

private:
	static GraphicsEngine* sharedInstance;
	DeviceContext* m_imm_device_context;

	RenderTexture* m_currentRenderTexture;
	std::list<RenderTexture*> renderTextureList;
	std::unordered_map<String, RenderTexture*> renderTextureTable;
private:
	ID3D11Device* m_d3d_device;
	D3D_FEATURE_LEVEL m_feature_level;
private:
	IDXGIDevice* m_dxgi_device;
	IDXGIAdapter* m_dxgi_adapter;
	IDXGIFactory* m_dxgi_factory;
	ID3D11DeviceContext* m_imm_context;

private:
	ID3DBlob* m_blob = nullptr;

	ID3DBlob* m_vsblob = nullptr;
	ID3DBlob* m_psblob = nullptr;
	ID3D11VertexShader* m_vs = nullptr;
	ID3D11PixelShader* m_ps = nullptr;

	TextureManager* m_tex_manager = nullptr;
private:
	friend class SwapChain;
	friend class VertexBuffer;
	friend class ConstantBuffer;
	friend class VertexShader;
	friend class PixelShader;
	friend class IndexBuffer;
	friend class UISystem;
	friend class RenderTexture;
	friend class Texture;
	friend class TextureManager;
	friend class RasterizerState;

};