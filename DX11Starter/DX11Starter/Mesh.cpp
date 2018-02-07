#include "Mesh.h"
#include "Vertex.h"
// For the DirectX Math library
using namespace DirectX;




Mesh::Mesh()
{
	
}

Mesh::Mesh(Vertex Vertices[], int indices[],int noofVertices, int noofIndices, ID3D11Device* Device)
{
	
	/*XMFLOAT4 red = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	XMFLOAT4 green = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	XMFLOAT4 blue = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
	Vertex Vertices[] =
	{
		{ XMFLOAT3(+0.0f, +1.0f, +0.0f), red },
		{ XMFLOAT3(+1.5f, -1.0f, +0.0f), blue },
		{ XMFLOAT3(-1.5f, -1.0f, +0.0f), green },
		{ XMFLOAT3(+0.0f, -2.0f, +0.0f), red }
	};*/
	
	D3D11_BUFFER_DESC vbi;
	vbi.Usage = D3D11_USAGE_IMMUTABLE;
	vbi.ByteWidth = sizeof(Vertex) * noofVertices;       // 3 = number of vertices in the buffer
	vbi.BindFlags = D3D11_BIND_VERTEX_BUFFER; // Tells DirectX this is a vertex buffer
	vbi.CPUAccessFlags = 0;
	vbi.MiscFlags = 0;
	vbi.StructureByteStride = 0;

	// Create the proper struct to hold the initial vertex data
	// - This is how we put the initial data into the buffer
	D3D11_SUBRESOURCE_DATA initialVertexData;
	initialVertexData.pSysMem = Vertices;

	Device->CreateBuffer(&vbi, &initialVertexData, &vertexBuffer);

//	int indices[] = { 0,1,2,3 };
//	int noofIndices = 4;

	// Create the INDEX BUFFER description ------------------------------------
	// - The description is created on the stack because we only need
	//    it to create the buffer.  The description is then useless.
	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(int) * noofIndices;         // 3 = number of indices in the buffer
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER; // Tells DirectX this is an index buffer
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;

	// Create the proper struct to hold the initial index data
	// - This is how we put the initial data into the buffer
	D3D11_SUBRESOURCE_DATA initialIndexData;
	initialIndexData.pSysMem = indices;

	// Actually create the buffer with the initial data
	// - Once we do this, we'll NEVER CHANGE THE BUFFER AGAIN
	Device->CreateBuffer(&ibd, &initialIndexData, &indexBuffer);
	
}



Mesh::~Mesh()
{
	if (vertexBuffer) { vertexBuffer->Release(); }
	if (indexBuffer) { indexBuffer->Release(); }
}

ID3D11Buffer * Mesh::GetVertexBuffer()
{
	return vertexBuffer;
}

ID3D11Buffer * Mesh::GetIndexBuffer()
{
	return indexBuffer;
}



int Mesh::GetIndexCount(int indices[])
{
	for (int i = 0; i < sizeof(indices) / sizeof(indices[0]);i++)
	{
		indexCount++;
	}
	return indexCount;
}

/*int Mesh::GetIndexCount()
{
	return 0;
}*/