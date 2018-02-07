#pragma once
#include "DXCore.h"
#include "Mesh.h"
#include"GameEntity.h"
#include "SimpleShader.h"
#include <DirectXMath.h>
class Camera 
{
	DirectX::XMFLOAT4X4 viewMatrix;
	DirectX::XMFLOAT4X4 projectionMatrix;
	
public:
	Camera();
	~Camera();
	void cameraView(XMFLOAT3,float,float,float,int, int);
	XMFLOAT4X4 cameraUpdate(XMFLOAT3, XMFLOAT3, float,float,float,int,int);
};

