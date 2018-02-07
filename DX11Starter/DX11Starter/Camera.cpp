#include "Camera.h"


//
Camera::Camera(XMFLOAT3 pos, float xRot, float yRot, float zRot, int width, int height)
{
	position = pos;
	rotationX = xRot;
	rotationY = yRot;
	pMatrix(width, height);
	flag = true;
	cameraUpdate();
}

Camera::~Camera()
{

}

void Camera::cameraUpdate()
{
	if (flag)
	{
		XMVECTOR pos = XMLoadFloat3(&position);
		
		XMVECTOR dir = XMVectorSet(0, 0, 1, 0);   //direction
		XMVECTOR up = XMVectorSet(0, 1, 0, 0); //up direction in 3d space
		XMVECTOR rotationQuat = XMQuaternionRotationRollPitchYaw(rotationX,rotationY,0);
		XMVECTOR finalRotation = XMVector3Rotate(dir, rotationQuat);

		XMStoreFloat3(&direction, finalRotation);

		XMMATRIX V = XMMatrixLookToLH(
			pos,     // The position of the "camera"
			finalRotation,     // Direction the camera is looking
			up);     // "Up" direction in 3D space (prevents roll)
		
		XMStoreFloat4x4(&viewMatrix, XMMatrixTranspose(V)); // Transpose for HLSL!

		flag = false;

	}
	
}


void Camera::pMatrix(int width, int height)
{
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


XMFLOAT4X4 Camera::getviewMatrix()
{
	return viewMatrix;
}


XMFLOAT4X4 Camera::getprojectionMatrix()
{
	return projectionMatrix;
}


void Camera::moveForward(float value)
{
	// We can add current direction of the camera to the position of the camera
	position.x += direction.x * value;
	position.y += direction.y * value;
	position.z += direction.z * value;
	flag = true;
}

void Camera::moveRight(float value)
{
	XMVECTOR rightSide;
	XMVECTOR up = XMVectorSet(0, 1, 0, 0);
	XMVECTOR dir = XMLoadFloat3(&direction);
	rightSide = XMVector3Cross(dir, up); // left or right vectors can be found out by cross product of the direction of camera 
										//& the up direction
	rightSide = XMVector3Normalize(rightSide);
	XMFLOAT3 rightSideValue;
	XMStoreFloat3(&rightSideValue, rightSide);

	position.x += rightSideValue.x * value;
	position.y += rightSideValue.y * value;
	position.z += rightSideValue.z * value;

	flag = true;

}

void Camera::updateRotationX(float value)
{
	if (rotationX + value < 0.3f & rotationX + value > -0.3f) 
	{
		rotationX += value;
		flag = true;
	}
}

void Camera::updateRotationY(float value)
{
	if (rotationY + value < 0.6f & rotationY + value > -0.6f)
	{
	rotationY += value;
	flag = true;
	}
}