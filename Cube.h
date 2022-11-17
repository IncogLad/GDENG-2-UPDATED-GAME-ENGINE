#pragma once
#include <iostream>
#include "AGameObject.h"
#include "GraphicsEngine.h"
#include "VertexShader.h"
#include "PixelShader.h"

class Cube : public AGameObject
{
public:
	Cube();
	~Cube();

	void initialize(std::string name) override;
	void destroy() override;

	void initBuffers(void* shader_byte_code, size_t size_shader, int num );
	void initConstBuffers();
	void draw() override;
	void releaseBuffers();

	void updatePosition();

private:
	VertexBuffer* m_vb;
	ConstantBuffer* m_cb;
	IndexBuffer* m_ib;

	constant cc;

	VertexShader* m_vs;
	PixelShader* m_ps;


	Vector3D rotation;
	Vector3D translation;
	Vector3D scaling;
	bool i_trans;
	bool i_scale;

	int num = 0;

	Cube(Cube const&) {}
	Cube& operator=(Cube const&) {}

};
