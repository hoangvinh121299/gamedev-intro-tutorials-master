#pragma once
#include "GameObject.h"

#define MARIO_WALKING_SPEED		0.1f
#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_SIT_SPEED_Y       0.2f
#define MARIO_GRAVITY			0.1f
//MARIO_STATE_NORMAL
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200
#define MARIO_STATE_JUMP			300
#define MARIO_STATE_SIT             400
//MARIO_STATE_WHITE
#define MARIO_STATE_WHITE_IDLE      500
#define MARIO_STATE_WHITE_WALKING_RIGHT 600
#define MARIO_STATE_WHITE_WALKING_LEFT 700
#define MARIO_STATE_WHITE_JUMP        800
#define MARIO_STATE_WHITE_SIT        900
//MARIO_STATE_LITTLE
#define MARIO_STATE_LITTLE_IDLE     1000
#define MARIO_STATE_LITTLE_WALKING_RIGHT 1010
#define MARIO_STATE_LITTLE_WALKING_LEFT 1020
#define MARIO_STATE_LITTLE_JUMP 1030
//MARIO_ANI_NORMAL
#define MARIO_ANI_IDLE_RIGHT		0
#define MARIO_ANI_IDLE_LEFT			1
#define MARIO_ANI_WALKING_RIGHT		2
#define MARIO_ANI_WALKING_LEFT		3
#define MARIO_ANI_SIT_RIGHT    4
#define MARIO_ANI_SIT_LEFT     5
 //MARIO_ANI_WHITE
#define MARIO_ANI_WHITE_IDLE_RIGHT		6
#define MARIO_ANI_WHITE_IDLE_LEFT			7
#define MARIO_ANI_WHITE_WALKING_RIGHT		8
#define MARIO_ANI_WHITE_WALKING_LEFT		9
#define MARIO_ANI_WHITE_SIT_RIGHT    10
#define MARIO_ANI_WHITE_SIT_LEFT     11
//MARIO_ANI_LITTLE
#define MARIO_ANI_LITTLE_IDLE_RIGHT		12
#define MARIO_ANI_LITTLE_IDLE_LEFT			13
#define MARIO_ANI_LITTLE_WALKING_RIGHT		14
#define MARIO_ANI_LITTLE_WALKING_LEFT		15
class CMario : public CGameObject
{
private:
	float status; //check status of mario 
public: 
	void Update(DWORD dt);
	void Render();
	void SetState(int state);
	void ChangeState();
	void setStatus(int status) { this->status = status; }
	int getStatus() { return this->status; }
};