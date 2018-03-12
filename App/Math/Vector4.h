#ifndef __VECTOR_4__
#define __VECTOR_4__

struct Vector4
{
	Vector4(): x(0), y(0), z(0), w(0) {}
	Vector4(float x, float y, float z): x(x), y(y), z(z), w(0) {}
	float x;
	float y;
	float z;
	float w;
};

#endif