#ifndef __BUFFER__
#define __BUFFER__

#include <cstdio>
// #include <vector>

struct AttributeInfo
{
    AttributeInfo(unsigned int iStride) : Stride(iStride) {}
    unsigned int Stride;
};

struct BufferData
{
    BufferData(void* data, unsigned int numElements, unsigned int elementSize) : m_data(data), m_numElements(numElements), m_elementSize(elementSize) {}

    //inline operator const void*() const { return m_data; }
    void* GetData() { return m_data; }

    size_t GetElementSize() { return m_elementSize; }
    size_t GetNumElements() { return m_numElements; }
    size_t GetBufferSize() { return m_elementSize * m_numElements; }
    // std::vector<AttributeInfo> GetAttributes() { return m_attributes; }

    void* m_data;
    unsigned int m_numElements;
    unsigned int m_elementSize;
    // vector<AttributeInfo> m_attributes;
};

struct Buffer
{
public:
    Buffer() {};
    Buffer(unsigned int buffer, unsigned int numElements, unsigned int itemSize) : m_buffer(buffer), m_numElements(numElements), m_itemSize(itemSize) {}

    inline unsigned int GetBuffer() { return m_buffer; }
    inline unsigned int GetNumElements() const { return m_numElements; }
    inline unsigned int GetItemSize() const { return m_itemSize; }
    inline unsigned int GetBufferSize() const { return m_itemSize * m_numElements; }

private:
    unsigned int m_buffer;
    unsigned int m_numElements;
    unsigned int m_itemSize;

    
};

struct VertexBuffer : Buffer
{
    VertexBuffer() {};
    VertexBuffer(unsigned int vao, unsigned int buffer, unsigned int numElements, unsigned int itemSize) : Buffer(buffer, numElements, itemSize), m_vao(vao) {}

    inline unsigned int GetVertexArray() const { return m_vao; }

private:
    unsigned int m_vao;
};

#endif