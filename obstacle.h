
#ifndef _GAME_OBSTACLE_
#define _GAME_OBSTACLE_

#include "game_obj.h"


class COBSTACLE: public CGAME_OBJECT{
public:	
	COBSTACLE(S_POS pos):CGAME_OBJECT(pos, NONE, 0, 'O'){
	}
	~COBSTACLE(){}
};

#endif