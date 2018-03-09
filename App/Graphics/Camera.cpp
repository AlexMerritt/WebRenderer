#include "Camera.h"

void Camera::Initialize(float fov, float aspectRatio, float nearPlane, float farPlane)
{
	SetPosition(Vector3(0, 0, 2));
	SetRotation(Vector3(0, 0, -1));

	m_upDir = Vector3(0, 1, 0);

	m_fov = fov;
	m_aspectRatio = aspectRatio;
	m_nearPlane = nearPlane;
	m_farPlane = farPlane;

	m_projectionMatrix = Matrix4::CreateProjection(fov, aspectRatio, nearPlane, farPlane);

	Update();
}

void Camera::Update()
{
	m_viewMatrix = Matrix4::CreateLookAt(m_position, m_rotation, m_upDir);
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