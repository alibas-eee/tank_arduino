#ifndef _GAME_OBJ_
#define _GAME_OBJ_

#include "config.h"

typedef struct{
	int X;
	int Y;
}S_POS;

typedef enum{
	RIGTH,
	LEFT,
	UP,
	DOWN,
	NONE
}E_DIRECTION;

//CGAME_OBJECT{
//	S_POS Position;
//};

//CBULLET{
	
static int ObjectId = 0;	
	
class CGAME_OBJECT{
public:
	CGAME_OBJECT(S_POS pos, E_DIRECTION direction, float speed, char type);
	CGAME_OBJECT(const CGAME_OBJECT &obj);// Copy constructor
	~CGAME_OBJECT();
	
	void Move();
	void SetPos(S_POS pos);
	float GetSpeed(){	return Speed; }
	char GetType(){		return Type;}
	bool GetIsAlive(){	return IsAlive;}
	void SetAsDead(){	IsAlive = false;}
	int GetUniqueId(){	return UniqueObjectId; }
	S_POS GetPos(){		return Position; }
	E_DIRECTION GetDirection(){	return Direction;}
	
	void SetDirection(E_DIRECTION direction){Direction = direction;	}
	bool CheckCollision(CGAME_OBJECT * obj);
	bool IsInGameArea();
	
protected:	
	S_POS Position;
	E_DIRECTION Direction;	
	float Speed;
	char Type;
	bool IsAlive;
	int UniqueObjectId;
};

CGAME_OBJECT::CGAME_OBJECT(S_POS pos, E_DIRECTION direction, float speed, char type){
	Position = pos;
	Direction = direction;
	Speed = speed;
	Type = type;
	IsAlive = true; 	
	UniqueObjectId = ObjectId;
	ObjectId++;
}


CGAME_OBJECT::CGAME_OBJECT(const CGAME_OBJECT &obj){
	Position = obj.Position;
	Direction = obj.Direction;
	Speed = obj.Speed;
	Type = obj.Type;
	IsAlive = obj.IsAlive;	
}

CGAME_OBJECT::~CGAME_OBJECT(){	}


bool CGAME_OBJECT::CheckCollision(CGAME_OBJECT * obj){
	
	if(this->Position.X == obj->Position.X && this->Position.Y == obj->Position.Y){
		return true;		
	}else{
		return false;
	}
}

void CGAME_OBJECT::Move(){
	switch(this->Direction){
		case RIGTH:
				this->Position.X++;
			break;
		case LEFT:
				this->Position.X--;
			break;
		case UP:
				this->Position.Y++;
			break;
		case DOWN:	
				this->Position.Y--;
			break;
		default:
			//Direction = NONE;
		break;		
		}	
}


bool CGAME_OBJECT::IsInGameArea(){
	if(this->Position.X < BATTLE_AREA_WIDTH && this->Position.X >= 0	&& this->Position.Y < BATTLE_AREA_HEIGHT && this->Position.Y >= 0){
		return true;
	}else{
		return false;
	}
}

#endif
