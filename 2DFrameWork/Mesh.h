#pragma once
class Mesh
{
private:
    ID3D11Buffer*           vertexBuffer;
    ID3D11Buffer*           indexBuffer;

public:
    D3D_PRIMITIVE_TOPOLOGY  primitiveTopology;
    VertexType              vertexType;
    UINT                    byteWidth;
    UINT*                   indices;
    UINT                    indexCount;
    void*                   vertices;
    UINT                    vertexCount;
    string                  file;
public:
    Mesh();
    Mesh(void* vertices, UINT vertexCount, UINT* indices,
        UINT indexCount, VertexType type);
    ~Mesh();
    void Set();
    void LoadFile(string file);
    void SaveFile(string file);
    void                RenderDetail();
    /*void Reset();
    
    */
};

