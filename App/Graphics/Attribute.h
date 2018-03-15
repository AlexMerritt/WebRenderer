#ifndef __ATTRIBUTE__
#define __ATTRIBUTE__

struct VertexAttribute
{
    VertexAttribute(unsigned int iStride) : Stride(iStride) {}
    unsigned int Stride;
};

#endif