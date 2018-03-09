#ifndef __CAMERA__
#define __CAMERA__

#include "../Math/Matrix.h"
#include "../Math/Vector3.h"

class Camera
{
public:
	Camera();
	~Camera() {}

	void SetProjection(float fov, float aspectRatio, float nearPlane, float farPlane);

	void SetPosition(Vector3 position);
	void Move(Vector3 position);
	void SetRotation(Vector3 rotation);
	void Rotate(Vector3 rotation);

	void Update();

	Matrix4 GetViewMatrix() { return m_viewMatrix; }
	Matrix4 GetProjectionMatrix() { return m_projectionMatrix; }
	Matrix4 GetViewProjection() { return m_viewMatrix * m_projectionMatrix; }

private:
	Vector3 m_position;
	Vector3 m_rotation;
	Vector3 m_upDir;

	float m_fov;
	float m_aspectRatio;
	float m_nearPlane;
	float m_farPlane;

	Matrix4 m_viewMatrix;
	Matrix4 m_projectionMatrix;
};

#endif