#include "Polygon.h"

namespace BlueFBX
{
	Polygon::Polygon(size_t memberCount, BlueBell::IAllocator* pParentAllocator)
		: m_memberCount(memberCount)
		, m_indicies(nullptr)
		, m_normals(nullptr)
		, m_colors(nullptr)
		, m_tangents(nullptr)
		, m_binormals(nullptr)
	{
		m_linearAllocator.SetParentAllocator(pParentAllocator);
		m_linearAllocator.AllocateBlock(memberCount * sizeof(Polygon), alignof(Polygon));

		m_indicies = reinterpret_cast<int*>(m_linearAllocator.Allocate(memberCount * sizeof(int), alignof(int)));
		m_normals = reinterpret_cast<Vector3D*>(m_linearAllocator.Allocate(memberCount * sizeof(Vector3D), alignof(Vector3D)));
		m_colors = reinterpret_cast<Vector4D*>(m_linearAllocator.Allocate(memberCount * sizeof(Vector4D), alignof(Vector4D)));
		m_tangents = reinterpret_cast<Vector3D*>(m_linearAllocator.Allocate(memberCount * sizeof(Vector3D), alignof(Vector3D)));
		m_binormals = reinterpret_cast<Vector3D*>(m_linearAllocator.Allocate(memberCount * sizeof(Vector3D), alignof(Vector3D)));

		for (int i = 0; i < memberCount; i++)
		{
			m_indicies[i] = 0;
			m_normals[i] = Vector3D { 0.0f, 0.0f, 0.0f };
			m_colors[i] = Vector4D { 1.0f, 1.0f, 1.0f, 1.0f };
			m_tangents[i] = Vector3D { 0.0f, 0.0f, 0.0f };
			m_binormals[i] = Vector3D { 0.0f, 0.0f, 0.0f };
		}
	}

	void Polygon::SetIndex(const int& id, const int& index)
	{
		if (id < m_memberCount)
			m_indicies[id] = index;
	}

	void Polygon::SetNormal(const int& id, const Vector3D& normal)
	{
		if (id < m_memberCount)
			m_normals[id] = normal;
	}

	void Polygon::SetColor(const int& id, const Vector4D& color)
	{
		if (id < m_memberCount)
			m_colors[id] = color;
	}

	void Polygon::SetTangent(const int& id, const Vector3D& tangent)
	{
		if (id < m_memberCount)
			m_tangents[id] = tangent;
	}

	void Polygon::SetBinormal(const int& id, const Vector3D& binormal)
	{
		if (id < m_memberCount)
			m_binormals[id] = binormal;
	}

	const int& Polygon::GetIndex(const int& id)
	{
		if (id < m_memberCount)
			return m_indicies[id];
		else
			return -1;
	}

	const Vector3D& Polygon::GetNormal(const int& id)
	{
		if (id < m_memberCount)
			return m_normals[id];
		else
			return Vector3D { 0.0f, 0.0f, 0.0f };
	}

	const Vector4D& Polygon::GetColor(const int& id)
	{
		if (id < m_memberCount && m_colors)
			return m_colors[id];
		else
			return Vector4D { 0.0f, 0.0f, 0.0f, 0.0f };
	}

	const Vector3D& Polygon::GetTanget(const int& id)
	{
		if (id < m_memberCount)
			return m_tangents[id];
		else
			return Vector3D { 0.0f, 0.0f, 0.0f };
	}

	const Vector3D& Polygon::GetBinormal(const int& id)
	{
		if (id < m_memberCount)
			return m_binormals[id];
		else
			return Vector3D { 0.0f, 0.0f, 0.0f };
	}
}
