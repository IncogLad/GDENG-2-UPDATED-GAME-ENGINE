#pragma once
#include <stdexcept>

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

	std::wstring string_to_wide_string(const std::string& string)
	{
		if (string.empty())
		{
			return L"";
		}

		const auto size_needed = MultiByteToWideChar(CP_UTF8, 0, &string.at(0), (int)string.size(), nullptr, 0);
		if (size_needed <= 0)
		{
			throw std::runtime_error("MultiByteToWideChar() failed: " + std::to_string(size_needed));
		}

		std::wstring result(size_needed, 0);
		MultiByteToWideChar(CP_UTF8, 0, &string.at(0), (int)string.size(), &result.at(0), size_needed);
		return result;
	}

	std::string wide_string_to_string(const std::wstring& wide_string)
	{
		if (wide_string.empty())
		{
			return "";
		}

		const auto size_needed = WideCharToMultiByte(CP_UTF8, 0, &wide_string.at(0), (int)wide_string.size(), nullptr, 0, nullptr, nullptr);
		if (size_needed <= 0)
		{
			throw std::runtime_error("WideCharToMultiByte() failed: " + std::to_string(size_needed));
		}

		std::string result(size_needed, 0);
		WideCharToMultiByte(CP_UTF8, 0, &wide_string.at(0), (int)wide_string.size(), &result.at(0), size_needed, nullptr, nullptr);
		return result;
	}

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


private:
	friend class DeviceContext;
};

