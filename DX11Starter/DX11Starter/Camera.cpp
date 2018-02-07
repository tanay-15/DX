#include "Camera.h"


//
Camera::Camera()
{

}

Camera::~Camera()
{

}

XMFLOAT4X4 Camera::cameraUpdate(XMFLOAT3 position,XMFLOAT3 rotation,float xRot,float yRot,float zRot, int width, int height)
{
	XMVECTOR pos = XMLoadFloat3(&position);
	XMVECTOR rotationQuat;
	XMVECTOR dir1 = XMLoadFloat3(&rotation);
	dir1 = XMVector3Normalize(dir1);
	//XMVECTOR dir = XMVectorSet(0, 0, 1, 0);
	XMVECTOR up = XMVectorSet(0, 1, 0, 0);
	rotationQuat = XMQuaternionRotationRollPitchYaw(yRot, zRot, xRot);
	XMVECTOR finalRotation = XMVector3Rotate(dir1, rotationQuat);
	XMMATRIX V = XMMatrixLookToLH(
		pos,     // The position of the "camera"
		finalRotation,     // Direction the camera is looking
		up);     // "Up" direction in 3D space (prevents roll)
	XMStoreFloat4x4(&viewMatrix, XMMatrixTranspose(V)); // Transpose for HLSL!
	return viewMatrix;
}


void Camera::cameraView(XMFLOAT3 position, float xRot, float yRot, float zRot, int width, int height)
{
	// Create the View matrix
	// - In an actual game, recreate this matrix every time the camera 
	//    moves (potentially every frame)
	// - We're using the LOOK TO function, which takes the position of the
	//    camera and the direction vector along which to look (as well as "up")
	// - Another option is the LOOK AT function, to look towards a specific
	//    point in 3D space
	XMVECTOR pos = XMLoadFloat3(&position);
	XMVECTOR rotationQuat;
	XMVECTOR dir = XMVectorSet(0, 0, 1, 0);
	XMVECTOR up = XMVectorSet(0, 1, 0, 0);
	rotationQuat = XMQuaternionRotationRollPitchYaw(yRot, zRot, xRot);
	XMVECTOR finalRotation = XMVector3Rotate(dir, rotationQuat);
	XMMATRIX V = XMMatrixLookToLH(
		pos,     // The position of the "camera"
		finalRotation,     // Direction the camera is looking
		up);     // "Up" direction in 3D space (prevents roll)
	XMStoreFloat4x4(&viewMatrix, XMMatrixTranspose(V)); // Transpose for HLSL!
	// Create the Projection matrix
	//- This should match the window's aspect ratio, and also update anytime
	//    the window resizes (which is already happening in OnResize() below)
	XMMATRIX P = XMMatrixPerspectiveFovLH(
		0.25f * 3.1415926535f,		// Field of View Angle
		(float)width / height,		// Aspect ratio
		0.1f,						// Near clip plane distance
		100.0f);					// Far clip plane distance
	XMStoreFloat4x4(&projectionMatrix, XMMatrixTranspose(P)); // Transpose for HLSL!
}
