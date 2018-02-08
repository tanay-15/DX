#pragma once
#include "Camera.h"
#include "Material.h"
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
	Material* material;
	
public:
	XMFLOAT4X4 worldMatrix;
	XMFLOAT4X4 wmTrans;
	XMFLOAT4X4 wmScale;
	XMFLOAT4X4 wmRot;
	XMFLOAT4X4 setTranslation(float,float,float);
	XMFLOAT4X4 setScale(float,float,float);
	XMFLOAT4X4 setRotation(float);
	void updateWorld();
	GameEntity(Mesh* m, Material* m1);
	Mesh* getMesh();
	Material* getMaterial();
	void prepareMaterial(Camera * C);
	~GameEntity();
};

