#pragma once

#include "DXCore.h"
#include "Mesh.h"
#include"GameEntity.h"
#include"Camera.h"
#include "SimpleShader.h"
#include <DirectXMath.h>
#include<vector>
using namespace std;
class Game 
	: public DXCore
{
	


public:
	Game(HINSTANCE hInstance);
	~Game();

	// Overridden setup and game loop methods, which
	// will be called automatically
	void Init();
	void OnResize();
	void Update(float deltaTime, float totalTime);
	void datatoShader(GameEntity* GE, Camera* C);
	void Draw(float deltaTime, float totalTime);

	// Overridden mouse input helper methods
	void OnMouseDown (WPARAM buttonState, int x, int y);
	void OnMouseUp	 (WPARAM buttonState, int x, int y);
	void OnMouseMove (WPARAM buttonState, int x, int y);
	void OnMouseWheel(float wheelDelta,   int x, int y);
private:
	int i = 0;
	//vector<GameEntity*> entityList;
	Camera* View;
	GameEntity* Player;
	GameEntity* Player2;
	GameEntity* Player3;
	GameEntity* Player4;
	GameEntity* Player5;
	Mesh* Quad;
	Mesh* Square;
	Mesh* Hexagon;
	Material* newMaterial;
	// Initialization helper methods - feel free to customize, combine, etc.
	void LoadShaders(); 
	void CreateMatrices();
	void CreateBasicGeometry();

	// Buffers to hold actual geometry data
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;

	// Wrappers for DirectX shaders to provide simplified functionality
	SimpleVertexShader* vertexShader;
	SimplePixelShader* pixelShader;

	// The matrices to go from model space to screen space
	//DirectX::XMFLOAT4X4 worldMatrix;
	//DirectX::XMFLOAT4X4 viewMatrix;
	//DirectX::XMFLOAT4X4 projectionMatrix;

	// Keeps track of the old mouse position.  Useful for 
	// determining how far the mouse moved in a single frame.
	POINT prevMousePos;
};

