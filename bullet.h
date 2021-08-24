#ifndef _GAME_BULLET_
#define _GAME_BULLET_


#include "game_obj.h"


class CBULLET: public CGAME_OBJECT{
public:	
	CBULLET(S_POS pos, E_DIRECTION direction):CGAME_OBJECT(pos, direction, BULLET_SPEED, 'B'){
		speed = BULLET_SPEED;
	}
	~CBULLET(){}
	float speed;
};




#endif