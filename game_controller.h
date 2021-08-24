#include "game_obj.h"
#include "tank.h"
#include "bullet.h"
#include "obstacle.h"
#include "ai.h"

#include "LinkedList/LinkedList.h"
#include "util.h"

#if PLATFROM_ARDUINO < 1
#include <iostream>
using namespace std;
#endif

class CGAME_CONTROLLER{
public:	
	CGAME_CONTROLLER();
	~CGAME_CONTROLLER(){}
	void Run();
	void CreateObjects();
	void MoveObjects();
	void CheckCollisionWithBullet(CGAME_OBJECT* p_obj, int bullet_id);
	void PrintGame();	
	void print_char(char c);
	void clear_screen();
	void SetUserCommand(char cmd);
	void ProcessCommand(CTANK* p_tank);
	bool IsSpaceFree(S_POS pos);
	S_POS FindFreeSpace();	
	CGAME_OBJECT * WhoIsThere(S_POS pos);
	
	LinkedList<CGAME_OBJECT*> *p_object_list;
	CGAME_AI *ai_list[BOT_COUNT];
	CTANK* user_tank;
};


CGAME_CONTROLLER::CGAME_CONTROLLER(){
	
	p_object_list = new LinkedList<CGAME_OBJECT*>();
	CreateObjects();
}

CGAME_OBJECT *CGAME_CONTROLLER::WhoIsThere(S_POS pos){
	for(int i = 0; i<p_object_list->size(); i++){
		CGAME_OBJECT *p_it = p_object_list->get(i);
		
		S_POS obj_pos = p_it->GetPos();
		if(obj_pos.X == pos.X && obj_pos.Y == pos.Y){
			return p_it;
		}
	}

	return nullptr;
}


void CGAME_CONTROLLER::print_char(char c){
#if PLATFROM_ARDUINO > 1	
	Serial.print(c);
#else
	cout <<c;
#endif
}

void CGAME_CONTROLLER::PrintGame(){
	S_POS pos_it;
	
char sp = ' ';

	for(int i = BATTLE_AREA_HEIGHT - 1; i>=0; i--){
		for(int j = 0; j < BATTLE_AREA_WIDTH; j++){
			print_char(' '); 
			pos_it.X = j;
			pos_it.Y = i;
			if(IsSpaceFree(pos_it)	)
			{
				print_char(' '); 
			}else{
				CGAME_OBJECT *obj = WhoIsThere(pos_it);
				if (obj != nullptr)
				{
					if (obj->GetType() == 'T')
					{
						if(obj->GetIsAlive()){
							switch (obj->GetDirection())
							{
							case UP:{
								print_char('^'); 
								break;
							}
							case DOWN:{
								print_char('v'); 
								break;
							}
							case RIGTH:{
								print_char('>'); 
								break;
							}
							case LEFT:{
								print_char('<');
								break;
							}																			
							default:
								break;
							}
						}else{
							print_char('X'); 
						}
					}else if (obj->GetType() == 'B')
					{
						print_char('*'); 
					}
					else if (obj->GetType() == 'O')
					{
						print_char('#'); 
					}
					else{
						print_char(obj->GetType());	
					}

				
				}else{
					print_char(' '); 
				}
				
			}				
		}	
		print_char('\n');
	}
	
}


void CGAME_CONTROLLER::CheckCollisionWithBullet(CGAME_OBJECT* p_obj, int bullet_id){
	
	if(p_obj->IsInGameArea() ){	
		for(int i = 0; i<p_object_list->size(); i++){
			CGAME_OBJECT *p_it = p_object_list->get(i);
			
			S_POS obj_pos = p_it->GetPos();
			
			if(p_obj->GetUniqueId() != p_it->GetUniqueId()){
				if( p_obj->CheckCollision(p_it) ){
					if(p_it->GetType() == 'T'){
						p_it->SetAsDead();
						p_object_list->remove(bullet_id); //RIP BULLET
					}else
					{
						p_object_list->remove(i);
					}
										
				}
			}
									
		}
	}else{
		p_object_list->remove(bullet_id); //RIP BULLET
	}
	
}

void CGAME_CONTROLLER::SetUserCommand(char cmd){
	
	switch(cmd){
		case 'w':{
			user_tank->command = FORWARD;
			}
		break;
		case 'a':{
			user_tank->command = TURN_LEFT;
			}
		break;
		case 'd':{
			user_tank->command = TURN_RIGTH;
			}
		break;
		case 's':{
			user_tank->command = BACKWARD;
			}
		break;
		case 'f':{
			user_tank->command = STOP;
			CBULLET *p_bullet = user_tank->Shoot();
			p_object_list->add(p_bullet);	
		}
		break;
		
		default:{
			user_tank->command = STOP;
		}
		
		break;
		
		
	}
	
}

void CGAME_CONTROLLER::ProcessCommand(CTANK* p_tank){
	if(p_tank->GetIsAlive()){
		switch(p_tank->command){
			case TURN_RIGTH:
				p_tank->TurnRigth();
			break;
			
			case TURN_LEFT:
				p_tank->TurnLeft();
			break;
			
			case FORWARD:{
			
				CGAME_OBJECT tmp = *p_tank;// copy				
				tmp.Move();	//Test if tank can go
				if(IsSpaceFree(tmp.GetPos()) && tmp.IsInGameArea()){
					p_tank->MoveForward();	
				}		
			}
			break;
			
			case BACKWARD:{}
			
			break;
			
			default:{}
			
			break;		
		}
	}
}


void CGAME_CONTROLLER::MoveObjects(){
	CGAME_OBJECT *p_obj;
	int speed = 0;
	for(int i = 0; i<p_object_list->size(); i++){
		p_obj = p_object_list->get(i);
		speed = (int)p_obj->GetSpeed();	
		for(int j = 0; j<speed; j++){
			if(p_obj->GetType() == 'T'){
				ProcessCommand((CTANK*)p_obj);
			}else if(p_obj->GetType() == 'B'){
				((CBULLET*)p_obj)->Move();
				CheckCollisionWithBullet(p_obj, i);
			}		
		}		
	}
	
}


void CGAME_CONTROLLER::CreateObjects(){
	CGAME_OBJECT *p_obj;
	
	S_POS pos;
	CTANK *p_player, *p_bot;
		
	//tank 0
	pos.X = 0;
	pos.Y = 0;
	p_player = new CTANK(pos, RIGTH);
	p_object_list->add(p_player);
	user_tank = p_player;
		
for (int i = 0; i < BOT_COUNT; i++)
{
	//tank 1
	pos.X = random(BATTLE_AREA_WIDTH);
	pos.Y = random(BATTLE_AREA_HEIGHT);
	p_bot = new CTANK(pos, DOWN);
	p_object_list->add(p_bot);
	ai_list[i] = new CGAME_AI(p_bot, p_player, p_object_list );	
}
	
for (int i = 0; i < OBSTACLE_COUNT; i++)
{
	//OBSTACLE
	p_obj = new COBSTACLE(FindFreeSpace());
	p_object_list->add(p_obj);
}	

}

S_POS CGAME_CONTROLLER::FindFreeSpace(){
	S_POS pos;
	while(1){
		pos.X = (int)random(BATTLE_AREA_WIDTH);
		pos.Y = (int)random(BATTLE_AREA_HEIGHT);
			
		if(IsSpaceFree(pos)){
			return pos;
		}
	}
}


bool CGAME_CONTROLLER::IsSpaceFree(S_POS pos){
	bool is_free = true;
	for(int i = 0; i<p_object_list->size(); i++){
		CGAME_OBJECT *obj = p_object_list->get(i);
		S_POS obj_pos = obj->GetPos();
		if(obj_pos.X == pos.X && obj_pos.Y == pos.Y){
			is_free = false;
			break;
		}						
	}
	
	return is_free;
}

void CGAME_CONTROLLER::Run(){
		
	for(int i = 0; i< BOT_COUNT; i++){
		ai_list[i]->Play();
	}
	MoveObjects();
	clear_screen();
	PrintGame();
}


void CGAME_CONTROLLER::clear_screen() {
#if PLATFROM_ARDUINO > 0	
  Serial.write(27);       // ESC command
  Serial.print("[2J");    // clear screen command
  Serial.write(27);
  Serial.print("[H");     // cursor to home command
  
#endif
}
	
