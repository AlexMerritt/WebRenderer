#include "Matrix.h"

const Matrix4 Matrix4::Identity(
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1);

Matrix4& Matrix4::operator *= (const float s)
{
	m[0] *= s; m[1] *= s; m[2] *= s; m[3] *= s;
	m[4] *= s; m[5] *= s; m[6] *= s; m[7] *= s;
	m[8] *= s; m[9] *= s; m[10] *= s; m[11] *= s;
	m[12] *= s; m[13] *= s; m[14] *= s; m[15] *= s;
	return *this;
}

Matrix4& Matrix4::operator /= (float s)
{
	if (s < FLT_EPSILON)
	{
		m[0] = FLT_MAX; m[1] = FLT_MAX; m[2] = FLT_MAX; m[3] = FLT_MAX;
		m[4] = FLT_MAX; m[5] = FLT_MAX; m[6] = FLT_MAX; m[7] = FLT_MAX;
		m[8] = FLT_MAX; m[9] = FLT_MAX; m[10] = FLT_MAX; m[11] = FLT_MAX;
		m[12] = FLT_MAX; m[13] = FLT_MAX; m[14] = FLT_MAX; m[15] = FLT_MAX;
	}
	else
	{
		s = 1.0f / s;
		m[0] *= s; m[1] *= s; m[2] *= s; m[3] *= s;
		m[4] *= s; m[5] *= s; m[6] *= s; m[7] *= s;
		m[8] *= s; m[9] *= s; m[10] *= s; m[11] *= s;
		m[12] *= s; m[13] *= s; m[14] *= s; m[15] *= s;
	}

	return *this;
}

Matrix4 Matrix4::operator / (float s) const
{
	Matrix4 r;

	if (s < FLT_EPSILON)
	{
		for (int i = 0; i < 16; ++i)
			r.m[i] = FLT_MAX;
	}
	else
	{
		s = 1.0f / s;
		for (int i = 0; i < 16; ++i)
			r.m[i] = m[i] * s;
	}

	return r;
}

Matrix4 Matrix4::operator * (const Matrix4& matrix) const
{
	return Matrix4(
		m[0] * matrix.m[0] + m[1] * matrix.m[4] + m[2] * matrix.m[8] + m[3] * matrix.m[12],
		m[0] * matrix.m[1] + m[1] * matrix.m[5] + m[2] * matrix.m[9] + m[3] * matrix.m[13],
		m[0] * matrix.m[2] + m[1] * matrix.m[6] + m[2] * matrix.m[10] + m[3] * matrix.m[14],
		m[0] * matrix.m[3] + m[1] * matrix.m[7] + m[2] * matrix.m[11] + m[3] * matrix.m[15],

		m[4] * matrix.m[0] + m[5] * matrix.m[4] + m[6] * matrix.m[8] + m[7] * matrix.m[12],
		m[4] * matrix.m[1] + m[5] * matrix.m[5] + m[6] * matrix.m[9] + m[7] * matrix.m[13],
		m[4] * matrix.m[2] + m[5] * matrix.m[6] + m[6] * matrix.m[10] + m[7] * matrix.m[14],
		m[4] * matrix.m[3] + m[5] * matrix.m[7] + m[6] * matrix.m[11] + m[7] * matrix.m[15],

		m[8] * matrix.m[0] + m[9] * matrix.m[4] + m[10] * matrix.m[8] + m[11] * matrix.m[12],
		m[8] * matrix.m[1] + m[9] * matrix.m[5] + m[10] * matrix.m[9] + m[11] * matrix.m[13],
		m[8] * matrix.m[2] + m[9] * matrix.m[6] + m[10] * matrix.m[10] + m[11] * matrix.m[14],
		m[8] * matrix.m[3] + m[9] * matrix.m[7] + m[10] * matrix.m[11] + m[11] * matrix.m[15],

		m[12] * matrix.m[0] + m[13] * matrix.m[4] + m[14] * matrix.m[8] + m[15] * matrix.m[12],
		m[12] * matrix.m[1] + m[13] * matrix.m[5] + m[14] * matrix.m[9] + m[15] * matrix.m[13],
		m[12] * matrix.m[2] + m[13] * matrix.m[6] + m[14] * matrix.m[10] + m[15] * matrix.m[14],
		m[12] * matrix.m[3] + m[13] * matrix.m[7] + m[14] * matrix.m[11] + m[15] * matrix.m[15]
		);
}

const Matrix4& Matrix4::MakeRotation(const Vector3& axis, float angle)
{
	float cs = cos(angle);
	float sn = sin(angle);
	float onecos = 1.0f - cs;
	float x = axis.x;
	float y = axis.y;
	float z = axis.z;
	float xx = x * x;
	float yy = y * y;
	float zz = z * z;
	float xym = x * y * onecos;
	float xzm = x * z * onecos;
	float yzm = y * z * onecos;
	float xs = x * sn;
	float ys = y * sn;
	float zs = z * sn;

	m[0] = xx * onecos + cs;
	m[1] = xym - zs;
	m[2] = xzm + ys;
	m[3] = 0.0f;

	m[4] = xym + zs;
	m[5] = yy * onecos + cs;
	m[6] = yzm - xs;
	m[7] = 0.0f;

	m[8] = xzm - ys;
	m[9] = yzm + xs;
	m[10] = zz * onecos + cs;
	m[11] = 0.0f;

	m[12] = 0.0f;
	m[13] = 0.0f;
	m[14] = 0.0f;
	m[15] = 1.0f;

	return *this;
}

Matrix4& Matrix4::MakeOrthoOffCenter(float left, float right, float top, float bottom, float zNearPlane, float zFarPlane)
{
	m[0] = (2.0f / (right - left));
	m[1] = 0.0f;
	m[2] = 0.0f;
	m[3] = 0.0f;

	m[4] = 0.0f;
	m[5] = (2.0f / (bottom - top));
	m[6] = 0.0f;
	m[7] = 0.0f;

	m[8] = 0.0f;
	m[9] = 0.0f;
	m[10] = (1.0f / (zFarPlane - zNearPlane));
	m[11] = 0.0f;

	m[12] = ((left + right) / (left - right));
	m[13] = ((top + bottom) / (bottom - top));
	m[14] = (zNearPlane / (zNearPlane - zFarPlane));
	m[15] = 1.0f;

	return *this;
}

Matrix4 Matrix4::CreateOrtho(float left, float top, float right, float bottom, float nearClipPlane, float farClipPlane)
{
	float x = 2 / (right - left);
	float y = 2 / (bottom - top);
	//float z = -2 / (farClipPlane - nearClipPlane);
	float z = 1.0f / (farClipPlane - nearClipPlane);

	//float tx = -(right + left) / (right - left);
	//float ty = -(top + bottom) / (top - bottom);
	//float tz = -(farClipPlane + nearClipPlane) / (farClipPlane - nearClipPlane);

	float tz = -nearClipPlane / (farClipPlane - nearClipPlane);

	return Matrix4(
		x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, z, 0,
		0, 0, tz, 1.0f);


	/*return Matrix4(
	x, 0.0f, 0.0f, 0.0f,
	0.0f, y, 0.0f, 0.0f,
	0.0f, 0.0f, z, 0.0f,
	tx, ty, tz, 1.0f);*/
}

Matrix4 Matrix4::CreateProjection(float fov, float aspectRatio, float nearClipPlane, float farClipPlane)
{
	float fd = 1.0f / (float)tan((fov * PI / 180) / 2.0f);
	//float a1 = (farClipPlane + nearClipPlane) / (nearClipPlane - farClipPlane);
	//float a2 = (2.0f * farClipPlane * nearClipPlane) / (nearClipPlane - farClipPlane);
	float a1 = farClipPlane / (farClipPlane - nearClipPlane);
	float a2 = -(nearClipPlane * farClipPlane) / (farClipPlane - nearClipPlane);

	return Matrix4(
		fd / aspectRatio, 0.0f, 0.0f, 0.0f,
		0.0f, fd, 0.0f, 0.0f,
		0.0f, 0.0f, a1, 1.0f,
		0.0, 0.0f, a2, 0.0f);

	/*return Matrix4(
	fd / aspectRatio, 0.0f, 0.0f, 0.0f,
	0.0f, fd, 0.0f, 0.0f,
	0.0f, 0.0f, a1, a2,
	0.0, -1.0f, 0.0f, 0.0f);*/
}

Matrix4 Matrix4::CreateLookAt(const Vector3& eye, const Vector3& lookAt, const Vector3& up)
{
	/*
	zaxis = normal(At - Eye)
	xaxis = normal(cross(Up, zaxis))
	yaxis = cross(zaxis, xaxis)

	xaxis.x           yaxis.x           zaxis.x          0
	xaxis.y           yaxis.y           zaxis.y          0
	xaxis.z           yaxis.z           zaxis.z          0
	-dot(xaxis, eye)  -dot(yaxis, eye)  -dot(zaxis, eye)  1

	*/

	Vector3 zAxis = lookAt - eye;
	zAxis.Normalize();

	Vector3 xAxis = CrossP(up, zAxis);
	xAxis.Normalize();

	Vector3 yAxis = CrossP(zAxis, xAxis);

	return Matrix4(
		xAxis.x, yAxis.x, zAxis.x, 0,
		xAxis.y, yAxis.y, zAxis.y, 0,
		xAxis.z, yAxis.z, zAxis.z, 0,
		-xAxis.Dot(eye), -yAxis.Dot(eye), -zAxis.Dot(eye), 1.0f);
}

void Matrix4::Invert(Matrix4& result)
{
	float num1 = m[0];
	float num2 = m[1];
	float num3 = m[2];
	float num4 = m[3];
	float num5 = m[4];
	float num6 = m[5];
	float num7 = m[6];
	float num8 = m[7];
	float num9 = m[8];
	float num10 = m[9];
	float num11 = m[10];
	float num12 = m[11];
	float num13 = m[12];
	float num14 = m[13];
	float num15 = m[14];
	float num16 = m[15];
	float num17 = (float)((double)num11 * (double)num16 - (double)num12 * (double)num15);
	float num18 = (float)((double)num10 * (double)num16 - (double)num12 * (double)num14);
	float num19 = (float)((double)num10 * (double)num15 - (double)num11 * (double)num14);
	float num20 = (float)((double)num9 * (double)num16 - (double)num12 * (double)num13);
	float num21 = (float)((double)num9 * (double)num15 - (double)num11 * (double)num13);
	float num22 = (float)((double)num9 * (double)num14 - (double)num10 * (double)num13);
	float num23 = (float)((double)num6 * (double)num17 - (double)num7 * (double)num18 + (double)num8 * (double)num19);
	float num24 = (float)-((double)num5 * (double)num17 - (double)num7 * (double)num20 + (double)num8 * (double)num21);
	float num25 = (float)((double)num5 * (double)num18 - (double)num6 * (double)num20 + (double)num8 * (double)num22);
	float num26 = (float)-((double)num5 * (double)num19 - (double)num6 * (double)num21 + (double)num7 * (double)num22);
	float num27 = (float)(1.0 / ((double)num1 * (double)num23 + (double)num2 * (double)num24 + (double)num3 * (double)num25 + (double)num4 * (double)num26));

	result.m[0] = num23 * num27;
	result.m[4] = num24 * num27;
	result.m[8] = num25 * num27;
	result.m[12] = num26 * num27;
	result.m[1] = (float)-((double)num2 * (double)num17 - (double)num3 * (double)num18 + (double)num4 * (double)num19) * num27;
	result.m[5] = (float)((double)num1 * (double)num17 - (double)num3 * (double)num20 + (double)num4 * (double)num21) * num27;
	result.m[9] = (float)-((double)num1 * (double)num18 - (double)num2 * (double)num20 + (double)num4 * (double)num22) * num27;
	result.m[13] = (float)((double)num1 * (double)num19 - (double)num2 * (double)num21 + (double)num3 * (double)num22) * num27;
	float num28 = (float)((double)num7 * (double)num16 - (double)num8 * (double)num15);
	float num29 = (float)((double)num6 * (double)num16 - (double)num8 * (double)num14);
	float num30 = (float)((double)num6 * (double)num15 - (double)num7 * (double)num14);
	float num31 = (float)((double)num5 * (double)num16 - (double)num8 * (double)num13);
	float num32 = (float)((double)num5 * (double)num15 - (double)num7 * (double)num13);
	float num33 = (float)((double)num5 * (double)num14 - (double)num6 * (double)num13);
	result.m[2] = (float)((double)num2 * (double)num28 - (double)num3 * (double)num29 + (double)num4 * (double)num30) * num27;
	result.m[6] = (float)-((double)num1 * (double)num28 - (double)num3 * (double)num31 + (double)num4 * (double)num32) * num27;
	result.m[10] = (float)((double)num1 * (double)num29 - (double)num2 * (double)num31 + (double)num4 * (double)num33) * num27;
	result.m[14] = (float)-((double)num1 * (double)num30 - (double)num2 * (double)num32 + (double)num3 * (double)num33) * num27;
	float num34 = (float)((double)num7 * (double)num12 - (double)num8 * (double)num11);
	float num35 = (float)((double)num6 * (double)num12 - (double)num8 * (double)num10);
	float num36 = (float)((double)num6 * (double)num11 - (double)num7 * (double)num10);
	float num37 = (float)((double)num5 * (double)num12 - (double)num8 * (double)num9);
	float num38 = (float)((double)num5 * (double)num11 - (double)num7 * (double)num9);
	float num39 = (float)((double)num5 * (double)num10 - (double)num6 * (double)num9);
	result.m[3] = (float)-((double)num2 * (double)num34 - (double)num3 * (double)num35 + (double)num4 * (double)num36) * num27;
	result.m[7] = (float)((double)num1 * (double)num34 - (double)num3 * (double)num37 + (double)num4 * (double)num38) * num27;
	result.m[11] = (float)-((double)num1 * (double)num35 - (double)num2 * (double)num37 + (double)num4 * (double)num39) * num27;
	result.m[15] = (float)((double)num1 * (double)num36 - (double)num2 * (double)num38 + (double)num3 * (double)num39) * num27;
}