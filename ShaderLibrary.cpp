#include "ShaderLibrary.h"

#include "GraphicsEngine.h"
#include "PixelShader.h"
#include "VertexShader.h"

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

void ShaderLibrary::requestVertexShaderData(String vertexShaderName, void** shaderByteCode, size_t* sizeShader)
{
	GraphicsEngine* ge = GraphicsEngine::getInstance();
	ge->compileVertexShader(vertexShaderName.c_str(), "vsmain", shaderByteCode, sizeShader);
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
	ShaderData shader_data;
	ShaderNames shader_names;

	GraphicsEngine::getInstance()->compileVertexShader(shader_names.BASE_VERTEX_SHADER_NAME.c_str(), "vsmain", &shader_data.shaderByteCode, &shader_data.sizeShader);
	this->activeVertexShaders[shader_names.BASE_VERTEX_SHADER_NAME] = GraphicsEngine::getInstance()->createVertexShader(shader_data.shaderByteCode, shader_data.sizeShader);

	GraphicsEngine::getInstance()->compilePixelShader(shader_names.BASE_PIXEL_SHADER_NAME.c_str(), "psmain", &shader_data.shaderByteCode, &shader_data.sizeShader);
	this->activePixelShaders[shader_names.BASE_PIXEL_SHADER_NAME] = GraphicsEngine::getInstance()->createPixelShader(shader_data.shaderByteCode, shader_data.sizeShader);

	GraphicsEngine::getInstance()->compileVertexShader(shader_names.TEXTURED_VERTEX_SHADER_NAME.c_str(), "vsmain", &shader_data.shaderByteCode, &shader_data.sizeShader);
	this->activeVertexShaders[shader_names.TEXTURED_VERTEX_SHADER_NAME] = GraphicsEngine::getInstance()->createVertexShader(shader_data.shaderByteCode, shader_data.sizeShader); 

	GraphicsEngine::getInstance()->compilePixelShader(shader_names.TEXTURED_PIXEL_SHADER_NAME.c_str(), "psmain", &shader_data.shaderByteCode, &shader_data.sizeShader);
	this->activePixelShaders[shader_names.TEXTURED_PIXEL_SHADER_NAME] = GraphicsEngine::getInstance()->createPixelShader(shader_data.shaderByteCode, shader_data.sizeShader);


}

ShaderLibrary::~ShaderLibrary()
{
	ShaderNames shader_names;
	this->activeVertexShaders[shader_names.BASE_VERTEX_SHADER_NAME]->release();
	this->activePixelShaders[shader_names.BASE_PIXEL_SHADER_NAME]->release();
	this->activeVertexShaders[shader_names.TEXTURED_VERTEX_SHADER_NAME]->release();
	this->activePixelShaders[shader_names.TEXTURED_PIXEL_SHADER_NAME]->release();

	this->activeVertexShaders.clear();
	this->activePixelShaders.clear();
	

}
