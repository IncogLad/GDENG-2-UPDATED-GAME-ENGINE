#include "ShaderLibrary.h"

ShaderLibrary* ShaderLibrary::sharedInstance = nullptr;

ShaderLibrary* ShaderLibrary::getInstance()
{
	return sharedInstance;
}

void ShaderLibrary::initialize()
{
	sharedInstance = new ShaderLibrary();
}

void ShaderLibrary::destroy()
{
	delete sharedInstance;
}

void ShaderLibrary::requestVertexShaderData(String vertexShaderName, void** shaderByteCode, size_t sizeShader)
{
}

VertexShader* ShaderLibrary::getVertexShader(String vertexShaderName)
{
	return activeVertexShaders[vertexShaderName];
}

PixelShader* ShaderLibrary::getPixelShader(String pixelShaderName)
{
	return activePixelShaders[pixelShaderName];
}

ShaderLibrary::ShaderLibrary()
{
}

ShaderLibrary::~ShaderLibrary()
{
}
