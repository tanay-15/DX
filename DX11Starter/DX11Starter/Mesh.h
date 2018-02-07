#pragma once
#include "DXCore.h"
#include"Vertex.h"
#include <d3d11.h>
#include <DirectXMath.h>

using namespace std;
using namespace DirectX;
class Mesh
{
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	


public:
	int indexCount = 0;
	Mesh();
	Mesh(Vertex Vertices[], int indices[], int noofVertices,int noofIndices, ID3D11Device* Device);
	~Mesh();
	ID3D11Buffer* GetVertexBuffer();
	ID3D11Buffer* GetIndexBuffer();
	int GetIndexCount(int indices[]);
	//int GetIndexCount();
};

