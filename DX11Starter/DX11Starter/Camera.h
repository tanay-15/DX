#pragma once
#include "DXCore.h"
#include "Mesh.h"
#include "SimpleShader.h"
#include <DirectXMath.h>
class Camera 
{
	DirectX::XMFLOAT4X4 viewMatrix;
	DirectX::XMFLOAT4X4 projectionMatrix;
	float rotationX;
	float rotationY;
	bool flag;
	XMFLOAT3 position;
	XMFLOAT3 direction;
	
public:
	Camera(XMFLOAT3,float,float,float,int,int);
	~Camera();
	void pMatrix(int,int);
	void cameraUpdate();
	XMFLOAT4X4 getviewMatrix();
	XMFLOAT4X4 getprojectionMatrix();
	void moveForward(float value);
	void moveLeft(float value);
	void updateRotationX(float value);
	void updateRotationY(float factor);
};

