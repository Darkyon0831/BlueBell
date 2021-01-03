#ifndef __BB_VECTOR2D_H__
#define __BB_VECTOR2D_H__

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

#endif // !__BB_VECTOR2D_H__