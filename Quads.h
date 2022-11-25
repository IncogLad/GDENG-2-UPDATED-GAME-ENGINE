#pragma once
#include <iostream>
#include "AGameObject.h"
#include "GraphicsEngine.h"
#include "VertexShader.h"
#include "PixelShader.h"

class Quads : public AGameObject
{
public:
	Quads();
	~Quads();

	void initialize(std::string name) override;
	void destroy() override;

	void initBuffers();
	void initAnimBuffers();
	void initConstBuffers();
	void draw() override;
	void releaseBuffers();

	void updatePosition();

private:
	VertexBuffer* m_vb;
	ConstantBuffer* m_cb;

	constant cc;
	double speed = 2;
	bool decrease = false;

	float m_delta_pos;
	float m_delta_scale;

	Quads(Quads const&) {}
	Quads& operator=(Quads const&) {}
	
};

