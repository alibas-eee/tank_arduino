#ifndef _GAME_TANK_
#define _GAME_TANK_


#include "game_obj.h"
#include "bullet.h"

class CTANK: public CGAME_OBJECT{
public:	
	CTANK(S_POS pos):CGAME_OBJECT(pos, RIGTH, TANK_SPEED, 'T'){}
	CTANK(S_POS pos, E_DIRECTION direction):CGAME_OBJECT(pos, direction, TANK_SPEED, 'T'){}
	~CTANK(){}

	void TurnRigth();
	void TurnLeft();
	CBULLET *Shoot();
	void IsReloaded();
	void MoveForward();
	void MoveBacward();
private:	
	int ReloadTime;	
	
};

CBULLET *CTANK::Shoot(){
	CBULLET *p_bullet = new CBULLET(Position, Direction);	
  return p_bullet;
}

void CTANK::TurnRigth(){
	switch(Direction){
	RIGTH:
		Direction = DOWN;
		break;
	LEFT:
		Direction = UP;
		break;
	UP:
		Direction = RIGTH;
		break;
	DOWN:	
		Direction = LEFT;
		break;
	default:
		Direction = NONE;
	break;		
	}
	
}

void CTANK::TurnLeft(){
	switch(Direction){
	RIGTH:
		Direction = UP;
		break;
	LEFT:
		Direction = DOWN;
		break;
	UP:
		Direction = LEFT;
		break;
	DOWN:	
		Direction = RIGTH;
		break;
	default:
		Direction = NONE;
	break;		
	}	
	
}


#endif