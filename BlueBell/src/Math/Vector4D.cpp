#include  "Vector4D.h"

#include <functional>

namespace BlueBell
{
	Vector4D::Vector4D(float _x, float _y, float _z, float _w)
		: x(_x)
		, y(_y)
		, z(_z)
		, w(_w)
	{
	}

	void Vector4D::operator*=(Vector4D& rVector)
	{
		x *= rVector.x;
		y *= rVector.y;
		z *= rVector.z;
		w *= rVector.w;
	}

	Vector4D Vector4D::operator*(Vector4D& rVector) const
	{
		Vector4D newVector;

		newVector.x = x * rVector.x;
		newVector.y = y * rVector.y;
		newVector.z = z * rVector.z;
		newVector.w = w * rVector.w;

		return std::move(newVector);
	}

	void Vector4D::operator-=(Vector4D& rVector)
	{
		x -= rVector.x;
		y -= rVector.y;
		z -= rVector.z;
		w -= rVector.w;
	}

	Vector4D Vector4D::operator-(Vector4D& rVector) const
	{
		Vector4D newVector;

		newVector.x = x - rVector.x;
		newVector.y = y - rVector.y;
		newVector.z = z - rVector.z;
		newVector.w = w - rVector.w;

		return std::move(newVector);
	}

	void Vector4D::operator+=(Vector4D& rVector)
	{
		x += rVector.x;
		y += rVector.y;
		z += rVector.z;
		w += rVector.w;
	}

	Vector4D Vector4D::operator+(Vector4D& rVector) const
	{
		Vector4D newVector;

		newVector.x = x + rVector.x;
		newVector.y = y + rVector.y;
		newVector.z = z + rVector.z;
		newVector.w = w + rVector.w;

		return std::move(newVector);
	}
}