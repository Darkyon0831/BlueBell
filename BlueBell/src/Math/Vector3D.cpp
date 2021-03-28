#include  "Vector3D.h"

#include <functional>

namespace BlueBell
{
	const Vector3D& Vector3D::Zero { 0.0f, 0.0f, 0.0f };

	Vector3D::Vector3D(float _x, float _y, float _z)
		: x(_x)
		, y(_y)
		, z(_z)	
	{
	}

	void Vector3D::operator*=(const Vector3D& rVector)
	{
		x *= rVector.x;
		y *= rVector.y;
		z *= rVector.z;
	}

	Vector3D Vector3D::operator*(const Vector3D& rVector) const
	{
		Vector3D newVector;

		newVector.x = x * rVector.x;
		newVector.y = y * rVector.y;
		newVector.z = z * rVector.z;

		return std::move(newVector);
	}

	void Vector3D::operator*=(const float& rScalar)
	{
		x *= rScalar;
		y *= rScalar;
		z *= rScalar;
	}

	Vector3D Vector3D::operator*(const float& rScalar) const
	{
		Vector3D vector = Vector3D::Zero;

		vector.x = x * rScalar;
		vector.y = y * rScalar;
		vector.z = z * rScalar;

		return std::move(vector);
	}

	void Vector3D::operator/=(const float& rScalar)
	{
		x /= rScalar;
		y /= rScalar;
		z /= rScalar;
	}

	void Vector3D::operator-=(const Vector3D& rVector)
	{
		x -= rVector.x;
		y -= rVector.y;
		z -= rVector.z;
	}

	Vector3D Vector3D::operator-(const Vector3D& rVector) const
	{
		Vector3D newVector;

		newVector.x = x - rVector.x;
		newVector.y = y - rVector.y;
		newVector.z = z - rVector.z;

		return std::move(newVector);
	}

	void Vector3D::operator+=(const Vector3D& rVector)
	{
		x += rVector.x;
		y += rVector.y;
		z += rVector.z;
	}

	Vector3D Vector3D::operator+(const Vector3D& rVector) const
	{
		Vector3D newVector;

		newVector.x = x + rVector.x;
		newVector.y = y + rVector.y;
		newVector.z = z + rVector.z;

		return std::move(newVector);
	}

	void Vector3D::operator=(const float& rScalar)
	{
		x = rScalar;
		y = rScalar;
		z = rScalar;
	}

	bool Vector3D::operator==(const Vector3D& rVector)
	{
		if (x == rVector.x && y == rVector.y && z == rVector.z)
			return true;
		else
			return false;
	}

	bool Vector3D::operator!=(const Vector3D & rVector)
	{
		if (x != rVector.x && y != rVector.y && z != rVector.z)
			return true;
		else
			return false;
	}

	void Vector3D::Set(const float _x, const float _y, const float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	void Vector3D::Normilize()
	{
		*this /= this->Length();
	}

	float Vector3D::Length() const
	{
		return sqrt(x * x + y * y + z * z);
	}

	Vector3D Vector3D::CrossProduct(const Vector3D& rOther) const
	{
		Vector3D newVector;

		newVector.x = y * rOther.z - z * rOther.y;
		newVector.y = z * rOther.x - x * rOther.z;
		newVector.z = x * rOther.y - y * rOther.x;

		return std::move(newVector);
	}

	float Vector3D::DotProduct(const Vector3D& rOther) const
	{
		return x * rOther.x + y * rOther.y + z * rOther.z;
	}

	Vector3D Vector3D::CrossProduct(const Vector3D& v1, const Vector3D& v2)
	{
		Vector3D newVector;

		newVector.x = v1.y * v2.z - v1.z * v2.y;
		newVector.y = v1.z * v2.x - v1.x * v2.z;
		newVector.z = v1.x * v2.y - v1.y * v2.x;

		return std::move(newVector);
	}

	float Vector3D::DotProduct(const Vector3D& v1, const Vector3D& v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}
}
