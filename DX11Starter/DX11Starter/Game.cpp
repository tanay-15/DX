#include "Game.h"
#include "Vertex.h"
#include<math.h>

// For the DirectX Math library
using namespace DirectX;

// --------------------------------------------------------
// Constructor
//
// DXCore (base class) constructor will set up underlying fields.
// DirectX itself, and our window, are not ready yet!
//
// hInstance - the application's OS-level handle (unique ID)
// --------------------------------------------------------
Game::Game(HINSTANCE hInstance)
	: DXCore(
		hInstance,		   // The application's handle
		"DirectX Game",	   // Text for the window's title bar
		1280,			   // Width of the window's client area
		720,			   // Height of the window's client area
		true)			   // Show extra stats (fps) in title bar?
{
	// Initialize fields
	vertexBuffer = 0;
	indexBuffer = 0;
	vertexShader = 0;
	pixelShader = 0;

#if defined(DEBUG) || defined(_DEBUG)
	// Do we want a console window?  Probably only in debug mode
	CreateConsoleWindow(500, 120, 32, 120);
	printf("Console window created successfully.  Feel free to printf() here.");
#endif
	
}

// --------------------------------------------------------
// Destructor - Clean up anything our game has created:
//  - Release all DirectX objects created here
//  - Delete any objects to prevent memory leaks
// --------------------------------------------------------
Game::~Game()
{
	// Release any (and all!) DirectX objects
	// we've made in the Game class
	//if (vertexBuffer) { vertexBuffer->Release(); }
	//if (indexBuffer) { indexBuffer->Release(); }

	// Delete our simple shader objects, which
	// will clean up their own internal DirectX stuff
	delete vertexShader;
	delete pixelShader;
	delete Quad;
	delete Square;
	delete Hexagon;
	delete Player;
	delete Player2;
	delete Player3;
	delete Player4;
	delete Player5;
	delete View;
	delete newMaterial;
	
}

// --------------------------------------------------------
// Called once per program, after DirectX and the window
// are initialized but before the game loop.
// --------------------------------------------------------
void Game::Init()
{
	// Helper methods for loading shaders, creating some basic
	// geometry to draw and some simple camera matrices.
	//  - You'll be expanding and/or replacing these later
	LoadShaders();
	CreateMatrices();
	CreateBasicGeometry();

	// Tell the input assembler stage of the pipeline what kind of
	// geometric primitives (points, lines or triangles) we want to draw.  
	// Essentially: "What kind of shape should the GPU draw with our data?"
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

// --------------------------------------------------------
// Loads shaders from compiled shader object (.cso) files using
// my SimpleShader wrapper for DirectX shader manipulation.
// - SimpleShader provides helpful methods for sending
//   data to individual variables on the GPU
// --------------------------------------------------------
void Game::LoadShaders()
{
	vertexShader = new SimpleVertexShader(device, context);
	vertexShader->LoadShaderFile(L"VertexShader.cso");

	pixelShader = new SimplePixelShader(device, context);
	pixelShader->LoadShaderFile(L"PixelShader.cso");

	newMaterial = new Material(vertexShader, pixelShader);
}



// --------------------------------------------------------
// Initializes the matrices necessary to represent our geometry's 
// transformations and our 3D camera
// --------------------------------------------------------
void Game::CreateMatrices()
{
	XMFLOAT3 cameraPosition = XMFLOAT3(0.0f, 0.0f, -5.0f);
	View = new Camera(cameraPosition, 0.0f,0.0f,0.0f,width,height);
	View->pMatrix(width, height);
	
}


// --------------------------------------------------------
// Creates the geometry we're going to draw - a single triangle for now
// --------------------------------------------------------
void Game::CreateBasicGeometry()
{
	
	XMFLOAT4 red = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	XMFLOAT4 green = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	XMFLOAT4 blue = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);

	Vertex quad[] =												//quadrilateral
	{
		{ XMFLOAT3(+0.0f, +1.0f, +0.0f), red },
		{ XMFLOAT3(+1.5f, +0.0f, +0.0f), blue },
		{ XMFLOAT3(+0.0f, -1.0f, +0.0f), red },
		{ XMFLOAT3(-1.5f, +0.0f, +0.0f), green }
	};

	int qindices[] = { 0, 1, 2, 0, 2, 3};
	//int countIndex = 0;
	//countIndex= Mindinces.GetIndexCount(qindices);
	
	//Quad = new Mesh(quad, qindices, 4,countIndex, device);
	Quad = new Mesh(quad, qindices, 4, 6, device);
	Player = new GameEntity(Quad, newMaterial);
	Player2 = new GameEntity(Quad, newMaterial);

	Vertex square[] =											//square
	{
		{ XMFLOAT3(+2.4f, +0.9f, +0.0f), red },
		{ XMFLOAT3(+3.2f, +0.0f, +0.0f), blue },
		{ XMFLOAT3(+2.4f, -0.9f, +0.0f), red },
		{ XMFLOAT3(+1.6f, +0.0f, +0.0f), green }
	};

	int sindices[] = { 0, 1, 2, 0, 2, 3 };
	Square = new Mesh(square, sindices, 4, 6, device);
	Player3 = new GameEntity(Square, newMaterial);
	Player4 = new GameEntity(Square, newMaterial);

	Vertex hexagon[] =											//Hexagon
	{
		{ XMFLOAT3(-2.4f, +0.9f, +0.0f), red },
		{ XMFLOAT3(-1.6f, +0.0f, +0.0f), blue },
		{ XMFLOAT3(-2.4f, -0.9f, +0.0f), red },
		{ XMFLOAT3(-3.2f, -0.9f, +0.0f), green },
		{ XMFLOAT3(-3.6f, 0.0f, +0.0f), blue },
		{ XMFLOAT3(-3.2f, +0.9f, +0.0f), green },
	};

	int hindices[] = { 0, 1, 5, 1, 2, 3, 1, 3, 4, 1, 4, 5 };
	Hexagon = new Mesh(hexagon, hindices, 6, 12, device);
	Player5 = new GameEntity(Hexagon, newMaterial);
//	entityList.push_back(Player);
//	Player2 = new GameEntity(Quad);
//	entityList.push_back(Player2);
//	Player3 = new GameEntity(Quad);
//	entityList.push_back(Player3);
//	Player4 = new GameEntity(Quad);
//	entityList.push_back(Player4);
//	Player5 = new GameEntity(Quad);
//	entityList.push_back(Player5);
	// View and Projection Matrix
	

}


// --------------------------------------------------------
// Handle resizing DirectX "stuff" to match the new window size.
// For instance, updating our projection matrix's aspect ratio.
// --------------------------------------------------------
void Game::OnResize()
{
	// Handle base-level DX resize stuff
	DXCore::OnResize();

	View->pMatrix(width, height);
	// Update our projection matrix since the window size changed
	//XMMATRIX P = XMMatrixPerspectiveFovLH(
	//	0.25f * 3.1415926535f,	// Field of View Angle
	//	(float)width / height,	// Aspect ratio
	//	0.1f,				  	// Near clip plane distance
	//	100.0f);			  	// Far clip plane distance
	//XMStoreFloat4x4(&projectionMatrix, XMMatrixTranspose(P)); // Transpose for HLSL!
}


// --------------------------------------------------------
// Update your game here - user input, move objects, AI, etc.
// --------------------------------------------------------
void Game::Update(float deltaTime, float totalTime)
{
	// Quit if the escape key is pressed
	i++;
	Player->setTranslation(float(sin(i*0.0015)), 0.0f, 0.0f);
	Player->setScale(0.5f, 0.5f, 0.5f);
	Player->updateWorld();
	Player2->setScale(float(sin(i*0.0015)), float(sin(i*0.0015)), 1);
	Player2->updateWorld();
	Player3->setTranslation(0.0f , float(sin(i*0.0015)), 0.0f);
	Player3->updateWorld();
	Player4->setScale(1.0f, float(sin(i*0.0015)), 1.0f);
	Player4->updateWorld();
	Player5->setTranslation(-1.0f, 0.0f, 0.0f);
	Player5->setScale(0.5f, 0.5, 0.5f);
	Player5->setRotation(float(sin(i*0.0015)));
	Player5->updateWorld();
	float speed = 1.5f;
	if (GetAsyncKeyState(VK_ESCAPE))
		Quit();
	if (GetAsyncKeyState('W') & 0x8000)
	{
		View->moveForward(deltaTime * speed);
	}

	if (GetAsyncKeyState('S') & 0x8000)
	{
		View->moveForward(-1.0f * deltaTime * speed);
	}

	if (GetAsyncKeyState('D') & 0x8000) 
	{
		View->moveLeft( -1.0f * deltaTime * speed);
	}

	if (GetAsyncKeyState('A') & 0x8000) 
	{
		View->moveLeft( deltaTime * speed);
	}
	View->cameraUpdate();
}
//--------------------------------------------------------
//Send data to shader variables
//--------------------------------------------------------

void Game::datatoShader(GameEntity* GE, Camera* C)
{
	GameEntity* tempGE = GE;
	Camera* tempC = C;
	tempGE->prepareMaterial(tempC);
}
// --------------------------------------------------------
// Clear the screen, redraw everything, present to the user
// --------------------------------------------------------
void Game::Draw(float deltaTime, float totalTime)
{
	// Background color (Cornflower Blue in this case) for clearing
	const float color[4] = { 0.0f, 0.6f, 0.75f, 0.0f };

	context->ClearRenderTargetView(backBufferRTV, color);
	context->ClearDepthStencilView(
		depthStencilView,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
		1.0f,
		0);
	datatoShader(Player,View);			//ENTITY 1
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	ID3D11Buffer* VB;
	VB = Player->getMesh()->GetVertexBuffer();

	context->IASetVertexBuffers(0, 1, &VB, &stride, &offset);

	ID3D11Buffer* IB;
	IB = Player->getMesh()->GetIndexBuffer();
	context->IASetIndexBuffer(IB, DXGI_FORMAT_R32_UINT, 0);
	int qindices[] = { 0, 1, 2, 0, 2, 3 };
	int Qindice;
	Qindice = Player->getMesh()->GetIndexCount(qindices);
	context->DrawIndexed(
		Qindice,     // The number of indices to use (we could draw a subset if we wanted)
		0,     // Offset to the first index we want to use
		0);    // Offset to add to each index when looking up vertices

	datatoShader(Player2,View);			//ENTITY 2
	VB = Player2->getMesh()->GetVertexBuffer();

	context->IASetVertexBuffers(0, 1, &VB, &stride, &offset);
	IB = Player2->getMesh()->GetIndexBuffer();
	context->IASetIndexBuffer(IB, DXGI_FORMAT_R32_UINT, 0);
	Qindice = Player2->getMesh()->GetIndexCount(qindices);
	context->DrawIndexed(
		Qindice,     // The number of indices to use (we could draw a subset if we wanted)
		0,     // Offset to the first index we want to use
		0);    // Offset to add to each index when looking up vertices

	datatoShader(Player3,View);		//ENTITY 3
	UINT stride1 = sizeof(Vertex);
	UINT offset1 = 0;
	ID3D11Buffer* squareVB;
	squareVB = Player3->getMesh()->GetVertexBuffer();

	context->IASetVertexBuffers(0, 1, &squareVB, &stride1, &offset1);

	ID3D11Buffer* squareIB;
	squareIB = Player3->getMesh()->GetIndexBuffer();
	context->IASetIndexBuffer(squareIB, DXGI_FORMAT_R32_UINT, 0);
	int sindices[] = { 0, 1, 2, 0, 2, 3 };
	int Sindice;
	Sindice = Player3->getMesh()->GetIndexCount(sindices);
	context->DrawIndexed(
		Sindice,     // The number of indices to use (we could draw a subset if we wanted)
		0,     // Offset to the first index we want to use
		0);    // Offset to add to each index when looking up vertices


	datatoShader(Player4,View);   // ENTITY 4
	squareVB = Player4->getMesh()->GetVertexBuffer();
	context->IASetVertexBuffers(0, 1, &squareVB, &stride1, &offset1);
	squareIB = Player4->getMesh()->GetIndexBuffer();
	context->IASetIndexBuffer(squareIB, DXGI_FORMAT_R32_UINT, 0);
	Sindice = Player4->getMesh()->GetIndexCount(sindices);
	context->DrawIndexed(
		Sindice,     // The number of indices to use (we could draw a subset if we wanted)
		0,     // Offset to the first index we want to use
		0);    // Offset to add to each index when looking up vertices
	
	datatoShader(Player5,View); //ENTITY 5

	UINT stride2 = sizeof(Vertex);
	UINT offset2 = 0;
	ID3D11Buffer* hexVB;
	hexVB = Player5->getMesh()->GetVertexBuffer();

	context->IASetVertexBuffers(0, 1, &hexVB, &stride2, &offset2);

	ID3D11Buffer* hexIB;
	hexIB = Player5->getMesh()->GetIndexBuffer();
	context->IASetIndexBuffer(hexIB, DXGI_FORMAT_R32_UINT, 0);
	int hindices[] = { 0, 1, 5, 1, 2, 3, 1, 3, 4, 1, 4, 5 };
	int Hindice;
	Hindice = Player5->getMesh()->GetIndexCount(hindices);
	context->DrawIndexed(
		Hindice,     // The number of indices to use (we could draw a subset if we wanted)
		0,     // Offset to the first index we want to use
		0);    // Offset to add to each index when looking up vertices
	
	swapChain->Present(0, 0);
}


#pragma region Mouse Input

// --------------------------------------------------------
// Helper method for mouse clicking.  We get this information
// from the OS-level messages anyway, so these helpers have
// been created to provide basic mouse input if you want it.
// --------------------------------------------------------
void Game::OnMouseDown(WPARAM buttonState, int x, int y)
{
	// Add any custom code here...

	// Save the previous mouse position, so we have it for the future
	prevMousePos.x = x;
	prevMousePos.y = y;

	// Caputure the mouse so we keep getting mouse move
	// events even if the mouse leaves the window.  we'll be
	// releasing the capture once a mouse button is released
	SetCapture(hWnd);
}

// --------------------------------------------------------
// Helper method for mouse release
// --------------------------------------------------------
void Game::OnMouseUp(WPARAM buttonState, int x, int y)
{
	// Add any custom code here...

	// We don't care about the tracking the cursor outside
	// the window anymore (we're not dragging if the mouse is up)
	ReleaseCapture();
}

// --------------------------------------------------------
// Helper method for mouse movement.  We only get this message
// if the mouse is currently over the window, or if we're 
// currently capturing the mouse.
// --------------------------------------------------------
void Game::OnMouseMove(WPARAM buttonState, int x, int y)
{
	// Add any custom code here...
	if (buttonState & 0x0001) {
		float diffX = x - float(prevMousePos.x);
		float diffY = y - float(prevMousePos.y);

		View->updateRotationX(diffY * 0.001f);
		View->updateRotationY(diffX * 0.001f);
	}

	// Save the previous mouse position, so we have it for the future
	prevMousePos.x = x;
	prevMousePos.y = y;
}

// --------------------------------------------------------
// Helper method for mouse wheel scrolling.  
// WheelDelta may be positive or negative, depending 
// on the direction of the scroll
// --------------------------------------------------------
void Game::OnMouseWheel(float wheelDelta, int x, int y)
{
	// Add any custom code here...
}
#pragma endregion