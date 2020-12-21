#pragma once

namespace BlueBell
{
	class Vector2D
	{
	public:

		Vector2D() : x(0), y(0) {};
		Vector2D(float x, float y);

		float Length() const;
		void Normalize();

		void operator*= (Vector2D& rVector);
		Vector2D operator* (Vector2D& rVector) const;

		void operator-= (Vector2D& rVector);
		Vector2D operator- (Vector2D& rVector) const;

		void operator+= (Vector2D& rVector);
		Vector2D operator+ (Vector2D& rVector) const;

		static const Vector2D& Zero;

		float x;
		float y;
	};
}