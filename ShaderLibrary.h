#pragma once
#include <string>
#include <unordered_map>

#include "CameraHandler.h"

class PixelShader;
class VertexShader;



class ShaderNames
{
	typedef std::wstring String;
public:
	const String BASE_VERTEX_SHADER_NAME = L"VertexShaderAnim.hlsl";
	const String TEXTURED_VERTEX_SHADER_NAME = L"VertexShaderTex.hlsl";
	const String TEXTURED_MESH_VERTEX_SHADER_NAME = L"VertexMeshLayoutShader.hlsl";

	const String BASE_PIXEL_SHADER_NAME = L"PixelShaderAnim.hlsl";
	const String TEXTURED_PIXEL_SHADER_NAME = L"PixelShaderTex.hlsl";
};

class ShaderLibrary
{
public:
	class ShaderData
	{
	public:
		void* shaderByteCode = nullptr;
		size_t sizeShader = 0;

	};
	typedef std::wstring String;
	typedef std::unordered_map<String, VertexShader*> VertexShaderTable;
	typedef std::unordered_map<String, PixelShader*> PixelShaderTable;

	static ShaderLibrary* getInstance();
	static void initialize();
	static void destroy();

	void requestVertexShaderData(String vertexShaderName, void** shaderByteCode, size_t* sizeShader);
	VertexShader* getVertexShader(String vertexShaderName);
	PixelShader* getPixelShader(String pixelShaderName);

private:
	ShaderLibrary();
	~ShaderLibrary();
	ShaderLibrary(ShaderLibrary const&) {};
	ShaderLibrary& operator=(ShaderLibrary const&) {};

	static ShaderLibrary* sharedInstance;

	VertexShaderTable activeVertexShaders;
	PixelShaderTable activePixelShaders;

};

