#include  "Vector2D.h"

#include <functional>

namespace BlueBell
{
	const Vector2D& Vector2D::Zero { 0.0f, 0.0f };

	Vector2D::Vector2D(float _x, float _y)
		: x(_x)
		, y(_y)
	{
	}

	float Vector2D::Length() const
	{
		return sqrt(x * x + y * y);
	}

	void Vector2D::Normalize()
	{
		float length = Length();

		x /= length;
		y /= length;
	}

	void Vector2D::operator*=(Vector2D& rVector)
	{
		x *= rVector.x;
		y *= rVector.y;
	}

	Vector2D Vector2D::operator*(Vector2D& rVector) const
	{
		Vector2D newVector;

		newVector.x = x * rVector.x;
		newVector.y = y * rVector.y;

		return std::move(newVector);
	}

	void Vector2D::operator-=(Vector2D& rVector)
	{
		x -= rVector.x;
		y -= rVector.y;
	}

	Vector2D Vector2D::operator-(Vector2D& rVector) const
	{
		Vector2D newVector;

		newVector.x = x - rVector.x;
		newVector.y = y - rVector.y;

		return std::move(newVector);
	}

	void Vector2D::operator+=(Vector2D& rVector)
	{
		x += rVector.x;
		y += rVector.y;
	}

	Vector2D Vector2D::operator+(Vector2D& rVector) const
	{
		Vector2D newVector;

		newVector.x = x + rVector.x;
		newVector.y = y + rVector.y;

		return std::move(newVector);
	}
}