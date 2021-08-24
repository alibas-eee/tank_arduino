#ifndef _GAME_TANK_
#define _GAME_TANK_


#include "game_obj.h"
#include "bullet.h"

typedef enum{
	TURN_RIGTH,
	TURN_LEFT,
	FORWARD,
	BACKWARD,	
	STOP
}E_COMMAND;

class CTANK: public CGAME_OBJECT{
public:	
	CTANK(S_POS pos):CGAME_OBJECT(pos, RIGTH, TANK_SPEED, 'T'){ command = STOP; }
	CTANK(S_POS pos, E_DIRECTION direction):CGAME_OBJECT(pos, direction, TANK_SPEED, 'T'){command = STOP;}
	~CTANK(){}

	void TurnRigth();
	void TurnLeft();
	CBULLET *Shoot();
	void IsReloaded();
	void MoveForward();
	void MoveBacward();
	S_POS MoveSIM();
	E_COMMAND command;
private:	
	int ReloadTime;	
	
	
};


CBULLET *CTANK::Shoot(){
	CBULLET *p_bullet = new CBULLET(Position, Direction);	
  return p_bullet;
}


S_POS CTANK::MoveSIM(){
	S_POS Position = GetPos();
	E_DIRECTION Direction = GetDirection();	
	
	switch(Direction){
	case RIGTH:
		if(Position.X < BATTLE_AREA_WIDTH-1 )
			Position.X++;
		break;
	case LEFT:
		if(Position.X > 0	)
			Position.X--;
		break;
	case UP:
		if(Position.Y < BATTLE_AREA_HEIGHT-1)
			Position.Y++;
		break;
	case DOWN:	
		if(Position.Y > 0)
			Position.Y--;
		break;
	default:
		//Direction = NONE;
	break;		
	}	
	
	return Position;	
}

void CTANK::MoveForward(){
	Move();
}


void CTANK::TurnRigth(){
	E_DIRECTION direction = GetDirection();
	switch(direction){
	case RIGTH:
		direction = DOWN;
		break;
	case LEFT:
		direction = UP;
		break;
	case UP:
		direction = RIGTH;
		break;
	case DOWN:	
		direction = LEFT;
		break;
	default:
		//direction = NONE;
	break;		
	}
	SetDirection(direction);
}

void CTANK::TurnLeft(){
	E_DIRECTION direction = GetDirection();
	
	switch(direction){
	case RIGTH:
		direction = UP;
		break;
	case LEFT:
		direction = DOWN;
		break;
	case UP:
		direction = LEFT;
		break;
	case DOWN:	
		direction = RIGTH;
		break;
	default:
		//direction = NONE;
	break;		
	}	
	
	SetDirection(direction);	
}


#endif