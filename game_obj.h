#ifndef _GAME_OBJ_
#define _GAME_OBJ_

#define BATTLE_AREA_WIDTH 16
#define BATTLE_AREA_HEIGHT 16

#define TANK_SPEED 1
#define BULLET_SPEED 2

typedef struct{
	float X;
	float Y;
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
class CGAME_OBJECT{
public:
	CGAME_OBJECT(S_POS pos, E_DIRECTION direction, float speed, char type);
	~CGAME_OBJECT();
	void Move();
	void SetPos(S_POS pos);
	float GetSpeed(){	return Speed; }
	char GetType();
	S_POS GetPos();
	E_DIRECTION GetDirection();
	bool CheckCollision(CGAME_OBJECT * obj);
	bool IsInGameArea();
protected:	
	S_POS Position;
	E_DIRECTION Direction;	
	float Speed;
	char Type;
};

CGAME_OBJECT::CGAME_OBJECT(S_POS pos, E_DIRECTION direction, float speed, char type){
	Position = pos;
	Direction = direction;
	Speed = speed;
	Type = type;	
}

CGAME_OBJECT::~CGAME_OBJECT(){	}

char CGAME_OBJECT::GetType(){
	return this->Type;
}

S_POS CGAME_OBJECT::GetPos(){
	return this->Position;
}
E_DIRECTION CGAME_OBJECT::GetDirection(){
	return this->Direction;
}

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
		if(this->Position.X < BATTLE_AREA_WIDTH-1 )
			this->Position.X++;
		break;
	case LEFT:
		if(this->Position.X > 0	)
			this->Position.X--;
		break;
	case UP:
		if(this->Position.Y < BATTLE_AREA_HEIGHT-1)
			this->Position.Y++;
		break;
	case DOWN:	
		if(this->Position.Y > 0)
			this->Position.Y--;
		break;
	default:
		//Direction = NONE;
	break;		
	}	
}


bool CGAME_OBJECT::IsInGameArea(){
	if(this->Position.X < BATTLE_AREA_WIDTH && this->Position.X > 0	&& this->Position.Y < BATTLE_AREA_HEIGHT && this->Position.Y > 0){
		return true;
	}else{
		return false;
	}
}

#endif
