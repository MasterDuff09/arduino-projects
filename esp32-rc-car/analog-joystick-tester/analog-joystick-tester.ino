
#define JOYSTICK_X 34
#define JOYSTICK_Y 35
 
void setup(){
  Serial.begin(9600);
  pinMode(22,OUTPUT);
  pinMode(1,OUTPUT);

}
 
void loop(){
  
  int x = analogRead(JOYSTICK_X);
  if (x>2200){
    digitalWrite(22, HIGH);
    digitalWrite(1, LOW);
    }
  else if (x<1400){
    digitalWrite(22, LOW);
    digitalWrite(1, HIGH);
    }
   else {
    digitalWrite(22, LOW);
    digitalWrite(1, LOW);
    }
}
