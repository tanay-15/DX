#pragma once
#include "DXCore.h"
#include "Mesh.h"
#include "SimpleShader.h"
#include <DirectXMath.h>

class GameEntity 
{
	
	XMFLOAT3 position;
	XMFLOAT3 rotation;
	XMFLOAT3 scale;
	Mesh* mesh;
public:
	XMFLOAT4X4 worldMatrix;
	XMFLOAT4X4 wmTrans;
	XMFLOAT4X4 wmScale;
	XMFLOAT4X4 wmRot;
	XMFLOAT4X4 setTranslation(float,float,float);
	XMFLOAT4X4 setScale(float,float,float);
	XMFLOAT4X4 setRotation(float);
	void updateWorld();
	GameEntity(Mesh* m);
	Mesh* getMesh();
	~GameEntity();
};

