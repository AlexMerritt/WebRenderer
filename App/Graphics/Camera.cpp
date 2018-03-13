#include "Camera.h"

Camera::Camera()
{
	SetPosition(Vector3(0, 0, -2));
	SetRotation(Vector3(0, 0, 0));

	m_upDir = Vector3(0, 1, 0);
}

void Camera::SetProjection(float fov, float aspectRatio, float nearPlane, float farPlane)
{
	m_fov = fov;
	m_aspectRatio = aspectRatio;
	m_nearPlane = nearPlane;
	m_farPlane = farPlane;

	m_projectionMatrix = Matrix4::CreateProjection(fov, aspectRatio, nearPlane, farPlane);

	Update();
}

void Camera::Update()
{
	// This look at isn't quite correct but works enough for me for now
	Vector3 lookAt = Vector3(sin(m_rotation.z), sin(m_rotation.x), cos(m_rotation.y));

	lookAt = lookAt + m_position;

	m_viewMatrix = Matrix4::CreateLookAt(m_position, lookAt, m_upDir);
}

void Camera::SetPosition(Vector3 position)
{
	m_position = position;
}

void Camera::Move(Vector3 position)
{
	m_position.x += position.x;
	m_position.y += position.y;
	m_position.z += position.z;
}

void Camera::SetRotation(Vector3 rotation)
{
	m_rotation = rotation;
}

void Camera::Rotate(Vector3 rotation)
{
	m_rotation.x += rotation.x;
	m_rotation.y += rotation.y;
	m_rotation.z += rotation.z;
}