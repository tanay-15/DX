#pragma once
#include"SimpleShader.h"

class Material
{
	SimpleVertexShader* vertexShader;
	SimplePixelShader* pixelShader;
public:
	Material(SimpleVertexShader*, SimplePixelShader*);
	SimpleVertexShader* getvertexShader();
	SimplePixelShader* getpixelShader();
	~Material();
};

