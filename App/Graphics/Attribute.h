#ifndef __ATTRIBUTE__
#define __ATTRIBUTE__

struct VertexAttribute
{
    VertexAttribute(unsigned int iStride) :
        Location(0), Stride(iStride) {}

    VertexAttribute(char* strName, unsigned int iLocation, unsigned int iStride) :
        Name(strName), Location(iLocation), Stride(iStride) {}
    
    char* Name;
    unsigned int Location;
    unsigned int Stride;

};

#endif