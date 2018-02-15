#include "GameEntity.h"

using namespace DirectX;

XMFLOAT4X4  GameEntity::setTranslation(float x, float y, float z)
{
	XMMATRIX translation = XMMatrixTranslation(x, y, z);
	XMStoreFloat4x4(&wmTrans, translation);
	position.x = x;
	position.y = y;
	position.z = z;
	return wmTrans;


}

XMFLOAT4X4 GameEntity::setScale(float x, float y, float z)
{

	XMMATRIX scaling = XMMatrixScaling(x, y, z);
	XMStoreFloat4x4(&wmScale, scaling);
	scale.x = x;
	scale.y = y;
	scale.z = z;
	return wmScale;
}

XMFLOAT4X4 GameEntity::setRotation(float z)
{

	XMMATRIX rot = XMMatrixRotationY(z);
	XMStoreFloat4x4(&wmRot, rot);
	rotation.z = z;

	return wmRot;
}

void GameEntity::updateWorld()
{
	XMStoreFloat4x4(&worldMatrix, XMMatrixIdentity());
	XMMATRIX world = XMLoadFloat4x4(&worldMatrix);
	XMMATRIX trans = XMLoadFloat4x4(&wmTrans);
	XMMATRIX rot = XMLoadFloat4x4(&wmRot);
	XMMATRIX scale = XMLoadFloat4x4(&wmScale);
	world = trans * rot*scale;
	XMStoreFloat4x4(&worldMatrix, XMMatrixTranspose(world));

}

GameEntity::GameEntity(Mesh* m,Material* m1)
{
	mesh = m;
	material = m1;
	position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	this->setTranslation(0.0f, 0.0f, 0.0f);
	this->setScale(1.0f, 1.0f, 1.0f);
	this->setRotation(0.0f);
	updateWorld();

}

Mesh* GameEntity::getMesh()
{
	return mesh;
}

Material * GameEntity::getMaterial()
{
	return material;
}

void GameEntity::prepareMaterial(Camera* C)
{
	SimpleVertexShader* localvertexShader = this->getMaterial()->getvertexShader();
	SimplePixelShader* localpixelShader = this->getMaterial()->getpixelShader();
	localvertexShader->SetMatrix4x4("world", this->worldMatrix);
	localvertexShader->SetMatrix4x4("view", C->getviewMatrix());
	localvertexShader->SetMatrix4x4("projection", C->getprojectionMatrix());
	localvertexShader->CopyAllBufferData();
	localpixelShader->CopyAllBufferData();
	localvertexShader->SetShader();
	localpixelShader->SetShader();
	//localpixelShader->SetFloat3("")
	
}

GameEntity::~GameEntity()
{
}
