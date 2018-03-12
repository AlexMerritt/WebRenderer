#ifndef __MODEL__
#define __MODEL__

#include "RenderObject.h"
#include "Mesh.h"
#include "Material.h"
#include "../Math/Vector4.h"

class Model
{
public:
    Model();
    // Change to set material
    void SetMaterial();
    void GetMaterial();

    void SetMesh();
    void GetMesh();

    RenderObject* GetRenderObject() { return m_pRenderObject; }

protected:
    // Cached render object, when the mesh or materail changes this will be updated
    RenderObject* m_pRenderObject;
    Material* m_pMaterial;
    Mesh* m_pMesh;

    Vector4 m_position;
};

#endif