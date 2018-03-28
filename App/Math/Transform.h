#ifndef __TRANSFORM__
#define __TRANSFORM__

#include "Matrix.h"
#include "Vector3.h"

class Transform
{
public:
    Transform() : m_position(0,0,0), m_rotation(0,0,0), m_scale(1,1,1) {}

    Matrix4 GetMatrix()
    {
        Matrix4 mat = Matrix4::Identity;
        mat = Matrix4::CreateScale(m_scale) * mat;
        mat = Matrix4::CreateRotationZ(m_rotation.z) * mat;
        mat = Matrix4::CreateRotationY(m_rotation.y) * mat;
        mat = Matrix4::CreateRotationX(m_rotation.x) * mat;
        mat = Matrix4::CreateTranslation(m_position) * mat;

        return mat;
    }

    void Move(Vector3 offset) { m_position += offset; }
    void Rotate(Vector3 rotation) { m_rotation += rotation; }

protected:
    Vector3 m_position;
    Vector3 m_rotation;
    Vector3 m_scale;
};
#endif