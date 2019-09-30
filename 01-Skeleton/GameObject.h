#pragma once

#include <Windows.h>
#include <d3dx9.h>
class CGameObject
{
protected: 
	float x; 
	float y;
	LPDIRECT3DTEXTURE9 texture;			
public: 
	void SetPosition(float x, float y) { this->x = x, this->y = y; }

	CGameObject(LPCWSTR texturePath);
	virtual void Update(DWORD dt,int i);
	void Render();
	~CGameObject();
};

class CMario : public CGameObject
{
private:
	float vx = 0.2f;
public: 
	CMario(LPCWSTR texturePath) :CGameObject(texturePath) {};
	void Update(DWORD dt,int i);
};
class CBrick : public CGameObject
{
public:
	CBrick(LPCWSTR texturePath) : CGameObject(texturePath) {};
	void Update(DWORD dt,int i);
};
class CBall : public CGameObject
{
private:
	float vx = 0.3f;
	float vy = 0.5f;
	
public:
	CBall(LPCWSTR texturePath) :CGameObject(texturePath) {};
	void Update(DWORD dt,int i);
};