/* =============================================================
	INTRODUCTION TO GAME PROGRAMMING SE102
	
	SAMPLE 03 - KEYBOARD AND OBJECT STATE

	This sample illustrates how to:

		1/ Process keyboard input
		2/ Control object state with keyboard events
================================================================ */

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <iostream>
#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"
#include <fstream>
#include <string>
#include "Mario.h"
#include <vector>
#include<istream>
#include<iterator>
#include<sstream>
#define _CRT_SECURE_NO_WARNINGS
#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"02 - Sprite animation"
#define BACKGROUND_COLOR D3DCOLOR_XRGB(200, 200, 255)
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define MAX_FRAME_RATE 90

#define ID_TEX_MARIO 0
#define ID_TEX_ENEMY 10
#define ID_TEX_MISC 20
using namespace std;
CGame *game;
CMario *mario;
vector <string> varText;
vector <string> id_Locat;
class CSampleKeyHander: public CKeyEventHandler
{
	virtual void KeyState(BYTE *states);
    virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

CSampleKeyHander * keyHandler;
void loadVectorString()
{
	fstream input("textures\\load.txt");
	while (!input.eof())
	{
		char temp[255];
		input.getline(temp, 255);
		string load = temp;
		varText.push_back(temp);
	}
}

void CSampleKeyHander::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	switch (KeyCode)
	{
	
		case DIK_SPACE:
			mario->SetState(MARIO_STATE_JUMP);
			break;
		case DIK_A:
			switch (mario->getStatus())
			{
			case 0:
				mario->setStatus(1);
				break;
			case 1:
				mario->setStatus(2);
				break;
			case 2:
				mario->setStatus(0);
				break;
			}
			break;
	}
}
	void CSampleKeyHander::OnKeyUp(int KeyCode)
	{
		DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
		/*switch (KeyCode)
		{
		case DIK_DOWN:
			mario->SetState(MARIO_STATE_IDLE);
			break;
		}*/
	}
void CSampleKeyHander::KeyState(BYTE *states)
{
	//if (game->IsKeyDown(DIK_RIGHT))
	//	mario->SetState(MARIO_STATE_WALKING_RIGHT);
	//else if (game->IsKeyDown(DIK_LEFT))
	//	mario->SetState(MARIO_STATE_WALKING_LEFT);
	//else if (game->IsKeyDown(DIK_DOWN))
	//	mario->SetState(MARIO_STATE_SIT);
	//else mario->SetState(MARIO_STATE_IDLE);
	/*mario->ChangeState();*/
	if (mario->getStatus() == 0)
	{
		if (game->IsKeyDown(DIK_RIGHT))
			mario->SetState(MARIO_STATE_WALKING_RIGHT);
		else if (game->IsKeyDown(DIK_LEFT))
			mario->SetState(MARIO_STATE_WALKING_LEFT);
		else if (game->IsKeyDown(DIK_DOWN))
			mario->SetState(MARIO_STATE_SIT);
		else mario->SetState(MARIO_STATE_IDLE);
	}
	if (mario->getStatus() == 1)
	{
		if (game->IsKeyDown(DIK_RIGHT))
			mario->SetState(MARIO_STATE_WHITE_WALKING_RIGHT);
		else if (game->IsKeyDown(DIK_LEFT))
			mario->SetState(MARIO_STATE_WHITE_WALKING_LEFT);
		else if (game->IsKeyDown(DIK_DOWN))
			mario->SetState(MARIO_STATE_WHITE_SIT);
		else mario->SetState(MARIO_STATE_WHITE_IDLE);
	}
	if (mario->getStatus() == 2)
	{
		if (game->IsKeyDown(DIK_RIGHT))
			mario->SetState(MARIO_STATE_LITTLE_WALKING_RIGHT);
		else if (game->IsKeyDown(DIK_LEFT))
			mario->SetState(MARIO_STATE_LITTLE_WALKING_LEFT);
		else mario->SetState(MARIO_STATE_LITTLE_IDLE);
	}
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	Load all game resources 
	In this example: load textures, sprites, animations and mario object
*/
void LoadResources()
{
	CTextures * textures = CTextures::GetInstance();
	loadVectorString();
	textures->Add(ID_TEX_MARIO,L"textures\\mario.png",D3DCOLOR_XRGB(255, 255, 255));
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	LPDIRECT3DTEXTURE9 texMario = textures->Get(ID_TEX_MARIO);
//load Spritre from TXT Flie
	for (int i = 0; i < varText.size(); i++)
	{
		istringstream iss(varText[i]);
		vector<string> id_Locat((istream_iterator<string>(iss)),
		                           istream_iterator<string>());
		sprites->Add(stoi(id_Locat[0]), stoi(id_Locat[1]), stoi(id_Locat[2]), stoi(id_Locat[3]),stoi(id_Locat[4]), texMario);
	}
	////Normal Mario Sprites
	//sprites->Add(10001, 246, 154, 260, 181, texMario);

	//sprites->Add(10002, 275, 154, 290, 181, texMario);
	//sprites->Add(10003, 304, 154, 321, 181, texMario);

	//sprites->Add(10011, 186, 154, 200, 181, texMario);

	//sprites->Add(10012, 155, 154, 170, 181, texMario);
	//sprites->Add(10013, 125, 154, 140, 181, texMario);

	//sprites->Add(10030, 2, 233, 23, 260, texMario); //sit left
	//sprites->Add(10020, 422, 233, 441, 260, texMario);//sit right
	////White Mario Sprites
	//sprites->Add(20001, 182, 389, 206, 426,  texMario); //idle white left
	//sprites->Add(20002, 150, 389, 176, 426,  texMario);
	//sprites->Add(20003, 120, 389,   146, 426, texMario);

	//sprites->Add(20011, 241, 389, 264, 426,  texMario);//white idle right
	//sprites->Add(20012,  271, 389,  294, 426, texMario);
	//sprites->Add(20013,  301, 389,  324, 426, texMario);

	//sprites->Add(20021, 425, 474, 442, 502,  texMario);//white sit right
	//sprites->Add(20022,  4, 474, 22, 502, texMario);// white sit left
	////Little Mario Sprites
	//sprites->Add(30001, 184, -1, 201, 18,  texMario); //idle little left 
	//sprites->Add(30002,  154, -1, 171, 18,  texMario);
	//sprites->Add(30003, 124, -1,   141, 18, texMario);

	//sprites->Add(30011, 245, -1,   261, 18, texMario);//little idle right
	//sprites->Add(30012, 275, -1, 291, 18,  texMario);
	//sprites->Add(30013, 305, -1, 321, 18,  texMario);
	LPANIMATION ani;
//Normal Mario
	ani = new CAnimation(100);
	/*ani->Add(10001);*/
	ani->Add(10020);
	animations->Add(600,ani);//sit right

	ani = new CAnimation(100);
	/*ani->Add(10011);*/
	ani->Add(10030);
	animations->Add(601, ani); //sit left

	ani = new CAnimation(100);	
	ani->Add(10001);
	animations->Add(400, ani);

	ani = new CAnimation(100);
	ani->Add(10011);
	animations->Add(401, ani);


	ani = new CAnimation(100);
	ani->Add(10001);
	ani->Add(10002);
	ani->Add(10003);
	animations->Add(500, ani);

	ani = new CAnimation(100);
	ani->Add(10011);
	ani->Add(10012);
	ani->Add(10013);
	animations->Add(501, ani);
	//White Mario Ani
	ani = new CAnimation(100);
	ani->Add(20001);
	animations->Add(701, ani);//idle left

	ani = new CAnimation(100);
	ani->Add(20001);
	ani->Add(20002);
	ani->Add(20003);
	animations->Add(801, ani);//walking_left
	
	ani = new CAnimation(100);
	ani->Add(20011);
	animations->Add(700, ani);//idle_right

	ani = new CAnimation(100);
	ani->Add(20011);
	ani->Add(20012);
	ani->Add(20013);
	animations->Add(800, ani);//walking_right

	ani = new CAnimation(100);
	ani->Add(20021);
	animations->Add(900, ani);//sit_rihgt;

	ani = new CAnimation(100);
	ani->Add(20022);
	animations->Add(901, ani);//sit_left;
	//little mario ani
	ani = new CAnimation(100);
	ani->Add(30001);
	animations->Add(10001, ani);//idle left

	ani = new CAnimation(100);
	ani->Add(30001);
	ani->Add(30002);
	ani->Add(30003);
	animations->Add(10011, ani);//walking_left

	ani = new CAnimation(100);
	ani->Add(30011);
	animations->Add(10000, ani);//idle right

	ani = new CAnimation(100);
	ani->Add(30011);
	ani->Add(30012);
	ani->Add(30013);
	animations->Add(10010, ani);//walking_right;

	mario = new CMario();
	CMario::AddAnimation(400);		// idle right
	CMario::AddAnimation(401);		// idle left
	CMario::AddAnimation(500);		// walk right
	CMario::AddAnimation(501);		// walk left
	CMario::AddAnimation(600);     
	CMario::AddAnimation(601);
	/*white mario*/
	CMario::AddAnimation(700);
	CMario::AddAnimation(701);
	CMario::AddAnimation(800);
	CMario::AddAnimation(801);
	CMario::AddAnimation(900);
	CMario::AddAnimation(901);
	//little mario
	CMario::AddAnimation(10000);
	CMario::AddAnimation(10001);
	CMario::AddAnimation(10010);
	CMario::AddAnimation(10011);

	mario->SetPosition(0.0f, 100.0f);
}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	mario->Update(dt);
}

/*
	Render a frame 
*/
void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		mario->Render();

		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd) 
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			game->ProcessKeyboard();
			
			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);	
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	game = CGame::GetInstance();
	game->Init(hWnd);

	keyHandler = new CSampleKeyHander();
	game->InitKeyboard(keyHandler);


	LoadResources();
	Run();
	return 0;
}