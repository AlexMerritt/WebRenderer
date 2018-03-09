#pragma once

#include "Vector3.h"

#include <cstdlib>
#include <math.h>
#include <malloc.h>
#include <cstring>

#define PI 3.14159

struct Matrix4
{
public:
	inline Matrix4() {}
	inline Matrix4(const Matrix4& matrix) { memcpy(m, matrix.m, sizeof(float) * 16); }

	// 0: m11, m12, m13, m14
	// 4: m21, m22, m23, m24
	// 8: m31, m32, m33, m34
	// 12: m41, m42, m43, m44

	inline Matrix4(const float m00, const float m01, const float m02, const float m03,
		const float m10, const float m11, const float m12, const float m13,
		const float m20, const float m21, const float m22, const float m23,
		const float m30, const float m31, const float m32, const float m33)
	{
		m[0] = m00; m[1] = m01; m[2] = m02; m[3] = m03;
		m[4] = m10; m[5] = m11; m[6] = m12; m[7] = m13;
		m[8] = m20; m[9] = m21; m[10] = m22; m[11] = m23;
		m[12] = m30; m[13] = m31; m[14] = m32; m[15] = m33;
	}

	inline Matrix4(const float m00, const float m11, const float m22) // create diagonal
	{
		MakeDiagonal(m00, m11, m22);
	}

	inline Matrix4(const Vector3& axis, float angle) // create rotation
	{
		MakeRotation(axis, angle);
	}

	inline Matrix4& operator = (const Matrix4& matrix) { memcpy(m, matrix.m, sizeof(float) * 16); return *this; }

	inline bool operator == (const Matrix4& matrix) const { return memcmp(m, matrix.m, sizeof(float) * 16) == 0; }
	inline bool operator != (const Matrix4& matrix) const { return memcmp(m, matrix.m, sizeof(float) * 16) != 0; }

	Matrix4& operator *= (const float s);
	Matrix4& operator /= (float s);
	inline Matrix4& operator += (const Matrix4& matrix)
	{
		for (int i = 0; i < 16; ++i)
			m[i] += matrix.m[i];

		return *this;
	}

	inline Matrix4& operator -= (const Matrix4& matrix)
	{
		for (int i = 0; i < 16; ++i)
			m[i] -= matrix.m[i];

		return *this;
	}

	Matrix4 operator + (const Matrix4& matrix) const
	{
		Matrix4 r;
		for (int i = 0; i < 16; ++i)
			r.m[i] = m[i] + matrix.m[i];

		return r;
	}

	Matrix4 operator - (const Matrix4& matrix) const
	{
		Matrix4 r;
		for (int i = 0; i < 16; ++i)
			r.m[i] = m[i] - matrix.m[i];

		return r;
	}

	Matrix4 operator -() const
	{
		Matrix4 r;
		for (int i = 0; i < 16; ++i)
			r.m[i] = -m[i];

		return r;
	}

	Matrix4 operator * (const float s) const
	{
		Matrix4 r;
		for (int i = 0; i < 16; ++i)
			r.m[i] = m[i] * s;

		return r;
	}

	Matrix4 operator / (float s) const;

	Matrix4 operator * (const Matrix4& matrix) const;

	inline operator float*() { return m; }
	inline operator const float*() const { return m; }

	Matrix4 Transpose() const
	{
		return Matrix4(
			m[0], m[4], m[8], m[12],
			m[1], m[5], m[9], m[13],
			m[2], m[6], m[10], m[14],
			m[3], m[7], m[11], m[15]);
	}

	// 0: m11, m12, m13, m14
	// 4: m21, m22, m23, m24
	// 8: m31, m32, m33, m34
	// 12: m41, m42, m43, m44

	// m11 0, m12 1, m13 2, m14 3
	// m21 4, m22 5, m23 6, m24 7
	// m31 8, m32 9, m33 10, m34 11
	// m41 12, m42 13, m43 14, m44 15

	Matrix4& MakeIdentity()
	{
		m[0] = 1.0f; m[1] = 0.0f; m[2] = 0.0f; m[3] = 0.0f;
		m[4] = 0.0f; m[5] = 1.0f; m[6] = 0.0f; m[7] = 0.0f;
		m[8] = 0.0f; m[9] = 0.0f; m[10] = 1.0f; m[11] = 0.0f;
		m[12] = 0.0f; m[13] = 0.0f; m[14] = 0.0f; m[15] = 1.0f;

		return *this;
	}

	Matrix4& MakeTranslation(const Vector3& v)
	{
		m[0] = 1.0f; m[1] = 0.0f; m[2] = 0.0f; m[3] = 0.0f;
		m[4] = 0.0f; m[5] = 1.0f; m[6] = 0.0f; m[7] = 0.0f;
		m[8] = 0.0f; m[9] = 0.0f; m[10] = 1.0f; m[11] = 0.0f;
		m[12] = v.x; m[13] = v.y; m[14] = v.z; m[15] = 1.0f;

		return *this;
	}

	Matrix4& MakeDiagonal(float m00, float m11, float m22)
	{
		m[0] = m00; m[1] = 0.0f; m[2] = 0.0f; m[3] = 0.0f;
		m[4] = 0.0f; m[5] = m11; m[6] = 0.0f; m[7] = 0.0f;
		m[8] = 0.0f; m[9] = 0.0f; m[10] = m22; m[11] = 0.0f;
		m[12] = 0.0f; m[13] = 0.0f; m[14] = 0.0f; m[15] = 1.0f;

		return *this;
	}

	const Matrix4& MakeRotation(const Vector3& axis, float angle);

	Matrix4& MakeScale(const Vector3& v)
	{
		m[0] = v.x; m[1] = 0.0f; m[2] = 0.0f; m[3] = 0.0f;
		m[4] = 0.0f; m[5] = v.y; m[6] = 0.0f; m[7] = 0.0f;
		m[8] = 0.0f; m[9] = 0.0f; m[10] = v.z; m[11] = 0.0f;
		m[12] = 0.0f; m[13] = 0.0f; m[14] = 0.0f; m[15] = 1.0f;
		return *this;
	}

	Matrix4& MakeOrthoOffCenter(float left, float right, float top, float bottom, float zNearPlane, float zFarPlane);

	inline void Transform(Vector3& v) const
	{
		float _x = (v.x * m[0]) + (v.y * m[4]) + (v.z * m[8]) + m[12];
		float _y = (v.x * m[1]) + (v.y * m[5]) + (v.z * m[9]) + m[13];
		float _z = (v.x * m[2]) + (v.y * m[6]) + (v.z * m[10]) + m[14];

		v.x = _x; v.y = _y; v.z = _z;
	}

	static Matrix4 CreateRotationX(float radians)
	{
		float cs = cos(radians);
		float sn = sin(radians);

		return Matrix4(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, cs, sn, 0.0f,
			0.0f, -sn, cs, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
	}

	static Matrix4 CreateRotationY(float radians)
	{
		float cs = cos(radians);
		float sn = sin(radians);

		return Matrix4(
			cs, 0.0f, -sn, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			sn, 0.0f, cs, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
	}

	static Matrix4 CreateRotationZ(float radians)
	{
		float cs = cos(radians);
		float sn = sin(radians);

		return Matrix4(
			cs, sn, 0.0f, 0.0f,
			-sn, cs, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
	}

	static Matrix4 CreateScale(float x, float y, float z)
	{
		return Matrix4(
			x, 0.0f, 0.0f, 0.0f,
			0.0f, y, 0.0f, 0.0f,
			0.0f, 0.0f, z, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
	}

	static Matrix4 CreateScale(const Vector3& v)
	{
		return Matrix4(
			v.x, 0.0f, 0.0f, 0.0f,
			0.0f, v.y, 0.0f, 0.0f,
			0.0f, 0.0f, v.z, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
	}

	static Matrix4 CreateTranslation(const Vector3& v)
	{
		return Matrix4(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			v.x, v.y, v.z, 1.0f
			);
	}

	static Matrix4 CreateTranslation(float x, float y, float z = 0)
	{
		return Matrix4(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			x, y, z, 1.0f
			);
	}

	static Matrix4 CreateOrtho(float left, float top, float right, float bottom, float nearClipPlane, float farClipPlane);
	static Matrix4 CreateOrtho(float screenWidth, float screenHeight, float nearClipPlane, float farClipPlane)
	{
		return Matrix4::CreateOrtho(0, 0, screenWidth, screenHeight, nearClipPlane, farClipPlane);
	}

	static Matrix4 CreateProjection(float fov, float aspectRatio, float nearClipPlane, float farClipPlane);
	static Matrix4 CreateLookAt(const Vector3& eye, const Vector3& lookAt, const Vector3& up);

	void Invert(Matrix4& result);

	static const Matrix4 Identity;

private:
	float m[16];
};