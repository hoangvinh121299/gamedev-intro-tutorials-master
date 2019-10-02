#include "Mario.h"
#include "Game.h"
void CMario::Update(DWORD dt)
{
	CGameObject::Update(dt);

	// simple fall down
	vy += MARIO_GRAVITY;
	if (y > 100) 
	{
		vy = 0; y = 100.0f;
	}
	// simple screen edge collision!!!
	if (vx > 0 && x > 290) x = 290;
	if (vx < 0 && x < 0) x = 0;
}

void CMario::Render()
{
	int ani;
	if (status == 0)
	{
		if (vx == 0)
		{
			if (nx > 0)
			{
				if (fx > 0) ani = MARIO_ANI_SIT_RIGHT;
				else
					ani = MARIO_ANI_IDLE_RIGHT;
			}
			else
			{
				if (fx > 0) ani = MARIO_ANI_SIT_LEFT;
				else
					ani = MARIO_ANI_IDLE_LEFT;
			}

		}
		else if (vx > 0)
			ani = MARIO_ANI_WALKING_RIGHT;
		else ani = MARIO_ANI_WALKING_LEFT;
	}
	else if (status == 1)
	{
		if (vx == 0)
		{
			if (nx > 0)
			{
				if (fx > 0) ani = MARIO_ANI_WHITE_SIT_RIGHT;
				else
					ani = MARIO_ANI_WHITE_IDLE_RIGHT;
			}
			else
			{
				if (fx > 0) ani = MARIO_ANI_WHITE_SIT_LEFT;
				else
					ani = MARIO_ANI_WHITE_IDLE_LEFT;
			}

		}
		else if (vx > 0)
			ani = MARIO_ANI_WHITE_WALKING_RIGHT;
		else ani = MARIO_ANI_WHITE_WALKING_LEFT;
	}
	else if(status == 2)
	{
		if (vx == 0)
		{
			if (nx > 0)
			{
				
					ani = MARIO_ANI_LITTLE_IDLE_RIGHT;
			}
			else
			{
				
					ani = MARIO_ANI_LITTLE_IDLE_LEFT;
			}

		}
		else if (vx > 0)
			ani = MARIO_ANI_LITTLE_WALKING_RIGHT;
		else ani = MARIO_ANI_LITTLE_WALKING_LEFT;
	}
	animations[ani]->Render(x, y);
}
void CMario::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MARIO_STATE_WALKING_RIGHT:
		vx = MARIO_WALKING_SPEED;
		nx = 1;
		fx = 0;
		break;
	case MARIO_STATE_WALKING_LEFT:
		vx = -MARIO_WALKING_SPEED;
		nx = -1;
		fx = 0;
		break;
	case MARIO_STATE_JUMP:
		if (y==100)
			vy = -MARIO_JUMP_SPEED_Y;
		fx = 0;
		break;
	case MARIO_STATE_IDLE:
		fx = 0;
		vx = 0;
		break;
	case MARIO_STATE_SIT:
		vx = 0;
		
		fx = 1;
		break;
		//WHITE MARIO STATE 
	case MARIO_STATE_WHITE_WALKING_RIGHT:
		status = 1;
		vx = MARIO_WALKING_SPEED;
		nx = 1;
		fx = 0;
		break;
	case MARIO_STATE_WHITE_WALKING_LEFT:
		status = 1;
		vx = -MARIO_WALKING_SPEED;
		nx = -1;
		fx = 0;
		break;
	case MARIO_STATE_WHITE_JUMP:
		status = 1;
		if (y == 100)
			vy = -MARIO_JUMP_SPEED_Y;
		fx = 0;
		break;
	case MARIO_STATE_WHITE_IDLE: 
		status = 1;
		fx = 0;
		vx = 0;
		break;
	case MARIO_STATE_WHITE_SIT:
		status = 1;
		fx = 1;
		break;
		//LITTLE MARIO STATE
	case MARIO_STATE_LITTLE_WALKING_RIGHT:
		status = 2;
		vx = MARIO_WALKING_SPEED;
		nx = 1;
		fx = 0;
		break;
	case MARIO_STATE_LITTLE_WALKING_LEFT:
		status = 2;
		vx = -MARIO_WALKING_SPEED;
		nx = -1;
		fx = 0;
		break;
	case MARIO_STATE_LITTLE_JUMP:
		status = 2;
		if (y == 100)
			vy = -MARIO_JUMP_SPEED_Y;
		fx = 0;
		break;
	case MARIO_STATE_LITTLE_IDLE:
		fx = 0;
		vx = 0;
		break;
	}
}


