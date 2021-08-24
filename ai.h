
#ifndef _GAME_AI_
#define _GAME_AI_

#include "game_obj.h"
#include "tank.h"
#include "bullet.h"
#include "LinkedList/LinkedList.h"
#include "util.h"

class CGAME_AI{
public:	
	CGAME_AI(CTANK *p_tank, CTANK *p_enemy, LinkedList<CGAME_OBJECT*> *p_object_list );
	
	~CGAME_AI(){}
	
	CTANK *pTank;
	
	CTANK *pEnemy;
	
	void Play();
	
	void RandomMove();
	
	bool SpotTarget();
	
	bool CheckIfBlockExist();
	
	void LookRIGTH(S_POS pos);
	
	void LookLEFT(S_POS pos);
	
	void LookUP(S_POS pos);
	
	void LookDOWN(S_POS pos);
	
	LinkedList<CGAME_OBJECT*> *p_object_list; 
	
};

CGAME_AI::CGAME_AI(CTANK *p_tank, CTANK *p_enemy, LinkedList<CGAME_OBJECT*> *p_object_list ){
	this->pTank = p_tank;
	this->pEnemy = p_enemy;
	this->p_object_list = p_object_list;
}


void  CGAME_AI::Play(){

	if(pTank->GetIsAlive()){
		SpotTarget();	
	}
}

bool CGAME_AI::CheckIfBlockExist(){
	
	bool blk_exist = false;
	CGAME_OBJECT *p_obj;
	char obj_type; 
	
	S_POS our_pos =  pTank->GetPos();
	S_POS enemy_pos =  pEnemy->GetPos();
	S_POS obj_pos;
	
	for(int i = 0; i<p_object_list->size(); i++){
		p_obj = p_object_list->get(i);
		obj_type = p_obj->GetType();
		if(obj_type == 'O'){	
			obj_pos = p_obj->GetPos();
			if(our_pos.X == enemy_pos.X  && our_pos.X == obj_pos.X){
				if(our_pos.Y > enemy_pos.Y ){
					if(our_pos.Y > obj_pos.Y && obj_pos.Y > enemy_pos.Y){
						return true;
					}						
				}else if(our_pos.Y < enemy_pos.Y ){
					if(our_pos.Y < obj_pos.Y && obj_pos.Y < enemy_pos.Y){
						return true;
					}						
				}
			}			
			else if(our_pos.Y == enemy_pos.Y  && our_pos.Y == obj_pos.Y){
				if(our_pos.X > enemy_pos.X ){
					if(our_pos.X > obj_pos.X && obj_pos.X > enemy_pos.X){
						return true;
					}						
				}else if(our_pos.X < enemy_pos.X ){
					if(our_pos.X < obj_pos.X && obj_pos.X < enemy_pos.X){
						return true;
					}						
				}
			}
			
		}			
	}
	
	return false;
}


void CGAME_AI::RandomMove(){
	
	int rng = random(6);
	
	switch(rng){
		case 0:
			pTank->command = TURN_RIGTH;
		break;
		case 1:
			pTank->command = TURN_LEFT;
		break;
		case 2:
		case 3:
		case 4:
		case 5:		
			pTank->command = FORWARD;
		break;
		case 6:
			pTank->command = BACKWARD;
		break;
		
		default:
			pTank->command = STOP;
		break;
	}
	
}



//Check if enemy in view area
bool CGAME_AI::SpotTarget(){
	
	E_DIRECTION Direction = pTank->GetDirection();
	S_POS our_pos =  pTank->GetPos();
	S_POS enemy_pos =  pEnemy->GetPos();
	
	
	if(!CheckIfBlockExist()){
	
		if(our_pos.X == enemy_pos.X )
		{
			if(our_pos.Y > enemy_pos.Y ){
				switch(Direction){
					case RIGTH:
						//turn rigth
						pTank->TurnRigth();				
						break;
					case LEFT:{
						//turn left						
						pTank->TurnLeft();	
						break;}
					case UP:
						//can't see what to do
						RandomMove();
						break;
					case DOWN:	{
						CBULLET *p_bullet = pTank->Shoot();
						p_object_list->add(p_bullet);
						break;
					}
					default:
						//
						break;
					}	
			}else{
				switch(Direction){
					case RIGTH:{
						//turn left
						pTank->TurnLeft();
						}				
						break;
					case LEFT:{
						//turn rigth
						pTank->TurnRigth();
						}
						break;
					case UP:{
						//shoot
						CBULLET *p_bullet = pTank->Shoot();
						p_object_list->add(p_bullet);
						}
						break;
					case DOWN:{
						//can't see what to do
						RandomMove();
						}
						break;
					default:{}
						//
						break;		
					}			
			}
		}else if(our_pos.Y == enemy_pos.Y ){
			if(our_pos.X > enemy_pos.X ){		
				switch(Direction){
					case RIGTH:{
						//turn left
						pTank->TurnLeft();
						break;
					}
					case LEFT:{
						//shoot
						CBULLET *p_bullet = pTank->Shoot();
						p_object_list->add(p_bullet);	
						break;
					}
					case UP:{
						//turn rigth
						pTank->TurnRigth();
						break;
					}
					case DOWN:{	
						//can't see what to do
						RandomMove();
						break;
					}										
					default:{
						
						break;		
					}	
				}	
			}else{
				switch(Direction){
					case RIGTH:{
					//shoot
						CBULLET *p_bullet = pTank->Shoot();
						p_object_list->add(p_bullet);	
						break;
					}
					case LEFT:{
						//can't see what to do
						RandomMove();
						break;
					}
					case UP:{
						//turn right
						pTank->TurnRigth();									
						break;
					}
					case DOWN:	{
						//turn left
						pTank->TurnLeft();					
						break;
					}
					default:{						
						break;	
					}	
				}				
			}
		}else{
			//can't see what to do
			RandomMove();
		}
	}else{
		//there is block can't see
		RandomMove();
	}
	
	return false;
}


	void CGAME_AI::LookRIGTH(S_POS pos){
		
	}
	
	void CGAME_AI::LookLEFT(S_POS pos){
		
	}
	
	void CGAME_AI::LookUP(S_POS pos){
		
	}
	
	void CGAME_AI::LookDOWN(S_POS pos){
		
	}


#endif