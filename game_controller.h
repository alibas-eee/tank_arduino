#include "game_obj.h"
#include "tank.h"
#include "bullet.h"
#include "obstacle.h"


#include "LinkedList/LinkedList.h"

class CGAME_CONTROLLER{
public:	
	CGAME_CONTROLLER();
	~CGAME_CONTROLLER(){}
	void Run();
	void CreateObjects();
	void MoveObjects();
	void CheckCollision();
	void PrintGame();	
	S_POS FindFreeSpace();
	
	LinkedList<CGAME_OBJECT*> *p_object_list;
};


CGAME_CONTROLLER::CGAME_CONTROLLER(){
	
	p_object_list = new LinkedList<CGAME_OBJECT*>();
	CreateObjects();
}

void CGAME_CONTROLLER::MoveObjects(){
	CGAME_OBJECT *p_obj;
	int speed = 0;
	for(int i = 0; i<p_object_list->size(); i++){
		p_obj = p_object_list->get(i);
		speed = (int)p_obj->GetSpeed();	
		for(int j = 0; j<speed; j++){
			p_obj->Move();
		}
		
	}
	
}


void CGAME_CONTROLLER::CreateObjects(){
	CGAME_OBJECT *p_obj;
	S_POS pos;
		
	//tank 0
	pos.X = 0;
	pos.Y = 0;
	p_obj = new CTANK(pos, RIGTH);
	p_object_list->add(p_obj);
		
	//tank 1
	pos.X = BATTLE_AREA_WIDTH-1;
	pos.Y = 0;
	p_obj = new CTANK(pos, DOWN);
	p_object_list->add(p_obj);	
	
	//tank 2
	pos.X = 0;
	pos.Y = BATTLE_AREA_HEIGHT-1;
	p_obj = new CTANK(pos, LEFT);
	p_object_list->add(p_obj);
	
	//tank 3
	pos.X = BATTLE_AREA_WIDTH-1;
	pos.Y = BATTLE_AREA_HEIGHT -1;
	p_obj = new CTANK(pos, LEFT);
	p_object_list->add(p_obj);


	//OBSTACLE
	p_obj = new COBSTACLE(FindFreeSpace());
	p_object_list->add(p_obj);
	
	p_obj = new COBSTACLE(FindFreeSpace());
	p_object_list->add(p_obj);
	
	p_obj = new COBSTACLE(FindFreeSpace());
	p_object_list->add(p_obj);
}

S_POS CGAME_CONTROLLER::FindFreeSpace(){
	S_POS pos;
	bool is_free = true;
	while(1){
		pos.X = (int)random(BATTLE_AREA_WIDTH);
		pos.Y = (int)random(BATTLE_AREA_HEIGHT);
		
		for(int i = 0; i<p_object_list->size(); i++){
			CGAME_OBJECT *obj = p_object_list->get(i);
			S_POS obj_pos = obj->GetPos();
			if(obj_pos.X == pos.X && obj_pos.Y == pos.Y){
				is_free = false;
				break;
			}						
		}
		
		if(is_free == true){
			return pos;
		}
	}
}

void CGAME_CONTROLLER::Run(){
	
	MoveObjects();
}