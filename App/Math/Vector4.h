#pragma once

struct Vector4
{
	Vector4(): x(0), y(0), z(0) {}
	Vector4(float x, float y, float z): x(x), y(y), z(z) {}
	float x;
	float y;
	float z;
	float w;
};