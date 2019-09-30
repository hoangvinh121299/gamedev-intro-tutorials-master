#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
CGameObject::CGameObject(LPCWSTR texturePath)
{
	x = y = 0;

	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFile(texturePath, &info);
	if (result != D3D_OK)
	{
		DebugOut(L"[ERROR] GetImageInfoFromFile failed: %s\n",texturePath);
		return;
	}

	LPDIRECT3DDEVICE9 d3ddv = CGame::GetInstance()->GetDirect3DDevice();

	result = D3DXCreateTextureFromFileEx(
		d3ddv,								// Pointer to Direct3D device object
		texturePath,						// Path to the image to load
		info.Width,							// Texture width
		info.Height,						// Texture height
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 255, 255),			// Transparent color
		&info,
		NULL,
		&texture);								// Created texture pointer

	if (result != D3D_OK)
	{
		OutputDebugString(L"[ERROR] CreateTextureFromFile failed\n");
		return;
	}

	DebugOut(L"[INFO] Texture loaded Ok: %s \n", texturePath);
}

void CGameObject::Render()
{
	CGame::GetInstance()->Draw(x, y, texture);
}
void CGameObject::Update(DWORD dt,int i)
{};

CGameObject::~CGameObject()
{
	if (texture != NULL) texture->Release();
}

void CMario::Update(DWORD dt,int i)
{
	x += vx * dt*i;
	if ((vx > 0 && x > SCREEN_WIDTH-30) || (x < 0 && vx < 0))
	{
		vx = -vx;
	}
}
void CBall::Update(DWORD dt,int i)
{
	x += vx * dt*i;
	if ((vx > 0 && x > SCREEN_WIDTH - 30) || (x < 0 && vx < 0)) vx = -vx;
	y += vy * dt*i;
	if ((vy > 0 && y > SCREEN_HEIGHT - 30) || (y < 0 && vy < 0)) vy = -vy;

}
