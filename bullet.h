#ifndef _GAME_BULLET_
#define _GAME_BULLET_


#include "game_obj.h"


class CBULLET: public CGAME_OBJECT{
public:	
	CBULLET(S_POS pos, E_DIRECTION direction):CGAME_OBJECT(pos, direction, BULLET_SPEED, 'B'){
		speed = BULLET_SPEED;
	}
	~CBULLET(){}
	void Move();
	float speed;
};


void CBULLET::Move(){
switch(this->Direction){
	case RIGTH:
			this->Position.X+=speed;
		break;
	case LEFT:
			this->Position.X-=speed;
		break;
	case UP:
			this->Position.Y+=speed;
		break;
	case DOWN:	
			this->Position.Y-=speed;
		break;
	default:
		//Direction = NONE;
	break;		
	}	
}


#endif