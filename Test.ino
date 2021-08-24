
#include "game_controller.h"

#if PLATFROM_ARDUINO > 0

CGAME_CONTROLLER controller;

void setup(){
  Serial.begin(500000);

}

void loop(){

  char c = ' '; 
  if (Serial.available()) {
    c = Serial.read();  
      Serial.println(c);
      controller.SetUserCommand(c);
      controller.Run();
  }
  Serial.flush();
  
  
  delay(1000);

 }


void print_pos(CGAME_OBJECT *p_obj){
  Serial.print(p_obj->GetType());
  Serial.print(p_obj->GetDirection());

  Serial.print(" ID: ");
  Serial.print(p_obj->GetUniqueId());
  
  Serial.print(" X: ");
  Serial.print(p_obj->GetPos().X);
  Serial.print(" Y: ");
  Serial.println(p_obj->GetPos().Y);
}  

#endif
