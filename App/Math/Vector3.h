#pragma once

#include <float.h>
#include <cmath>

struct Vector3
{
	Vector3() {}
	inline Vector3(const float x, const float y, const float z) : x(x), y(y), z(z) {}
	inline Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
	inline explicit Vector3(const float f[3]) : x(f[0]), y(f[1]), z(f[2]) {}

	inline Vector3& operator = (const Vector3& v) { x = v.x; y = v.y; z = v.z; return *this; }

	inline Vector3 operator -() const { return Vector3(-x, -y, -z); }
	inline Vector3& operator += (const Vector3& v) { x += v.x; y += v.y; z += v.z; return *this; };
	inline Vector3& operator -= (const Vector3& v) { x -= v.x; y -= v.y; z -= v.z; return *this; };
	inline Vector3& operator *= (const float s) { x *= s; y *= s; z *= s; return *this; }
	inline Vector3& operator /= (float s) { s = 1.0f / s; x *= s; y *= s; z *= s; return *this; }
	inline const bool operator == (const Vector3& v) const { return Compare(v); }
	inline const bool operator != (const Vector3& v) const { return !Compare(v); }

	inline operator float*() { return &x; }
	inline operator const float*() const { return &x; }

	inline void Set(const float x_, const float y_, const float z_) { x = x_; y = y_; z = z_; }
	inline void Set(const Vector3& v) { x = v.x; y = v.y; z = v.z; }

	inline float Length() const { return sqrt(x * x + y * y + z * z); }

	inline float LengthSquared() const { return x * x + y * y + z * z; }

	inline float Dot(const Vector3& v) const { return x * v.x + y * v.y + z * v.z; }

	// Convert this vector into a unit vector. Returns the Length.
	inline float Normalize()
	{
		float length = Length();
		if (length < FLT_EPSILON) return 0.0f;

		float inv = 1.0f / length;
		x *= inv;
		y *= inv;
		z *= inv;

		return length;
	}

	inline Vector3& Scale(float sx, float sy, float sz = 1.f) { x *= sx; y *= sy; z *= sz; return *this; }

	float x, y, z;

	static const Vector3 Zero;
	static const Vector3 One;
	static const Vector3 UnitX;
	static const Vector3 UnitY;
	static const Vector3 UnitZ;

	static const Vector3 UnitXY;
	static const Vector3 UnitXZ;
	static const Vector3 UnitYZ;

	static const Vector3 Forward;
	static const Vector3 Up;

private:
	inline bool Compare(const Vector3& v) const { return x == v.x && y == v.y && z == v.z; }
};

inline Vector3 CrossP(const Vector3& a, const Vector3& b)
{
	return Vector3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

inline Vector3 operator + (const Vector3& a, const Vector3& b)
{
	return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
}

inline Vector3 operator - (const Vector3& a, const Vector3& b)
{
	return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
}

inline Vector3 operator * (const float s, const Vector3& v)
{
	return Vector3(v.x * s, v.y * s, v.z * s);
}

inline float Distance(const Vector3& a, const Vector3& b)
{
	Vector3 c = a - b;
	return c.Length();
}

inline float DistanceSquared(const Vector3& a, const Vector3& b)
{
	Vector3 c = a - b;
	return c.LengthSquared();
}