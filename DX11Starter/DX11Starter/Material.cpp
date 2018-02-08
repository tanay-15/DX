#include "Material.h"


Material::Material(SimpleVertexShader* vShader, SimplePixelShader* pShader)
{
	vertexShader = vShader;
	pixelShader = pShader;

}

SimpleVertexShader* Material::getvertexShader()
{
	return vertexShader;
}

SimplePixelShader* Material::getpixelShader()
{
	return pixelShader;
}


Material::~Material()
{
}