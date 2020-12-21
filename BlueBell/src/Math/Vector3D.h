#pragma once

#include <cmath>

namespace BlueBell
{	
	class Vector3D
	{
	public:

		Vector3D() : x(0), y(0), z(0) {}
		Vector3D(float x, float y, float z);

		void operator*= (const Vector3D& rVector);
		Vector3D operator* (const Vector3D& rVector) const;

		void operator*= (const float& rScalar);
		Vector3D operator* (const float& rScalar) const;

		void operator/= (const float& rScalar);

		void operator-= (const Vector3D& rVector);
		Vector3D operator- (const Vector3D& rVector) const;

		void operator+= (const Vector3D& rVector);
		Vector3D operator+ (const Vector3D& rVector) const;

		void operator= (const float& rScalar);

		void Set(float _x, float _y, float _z);

		void Normilize();
		float Length() const;
		Vector3D CrossProduct(const Vector3D& rOther) const;
		float DotProduct(const Vector3D& rOther) const;

		float x;
		float y;
		float z;

		static const Vector3D& Zero;

		static Vector3D CrossProduct(const Vector3D& v1, const Vector3D& v2);
		static float DotProduct(const Vector3D& v1, const Vector3D& v2);
	};
}