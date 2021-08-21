#include "tank.h"
#include "game_controller.h"

S_POS pos;
CTANK *p_tank; 
CBULLET *p_bullet;

CGAME_CONTROLLER controller;

void setup(){
  Serial.begin(9600);

}

void loop(){

  controller.Run();
  for(int i = 0; i<controller.p_object_list->size(); i++){
    print_pos(controller.p_object_list->get(i));
  }

  delay(1000);
 }


void print_pos(CGAME_OBJECT *p_obj){
  Serial.print(p_obj->GetType());
  Serial.print(p_obj->GetDirection());
  
  Serial.print(" X: ");
  Serial.print(p_obj->GetPos().X);
  Serial.print(" Y: ");
  Serial.println(p_obj->GetPos().Y);
}  
