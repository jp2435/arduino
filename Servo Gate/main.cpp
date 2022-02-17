// C++ code
//
#include <Servo.h>
#define led_red 2
#define led_green 3
#define led_blue 4
#define pino_servo 9
#define pino_botao 7 

Servo servo_main;
int pos = 0;
bool GateOpen = false;

void setup()
{
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  
  // Led RGB
  pinMode(led_red,OUTPUT);
  pinMode(led_green,OUTPUT);
  pinMode(led_blue,OUTPUT);
  
  // Button
  pinMode(pino_botao,INPUT);
  
  // Servo
  servo_main.attach(pino_servo);
  
  RGBColor(245,200,15);
}

void loop()
{
  if(digitalRead(pino_botao) == HIGH){
    moveServo();
  } 
}


void RGBColor(int red_light,int green_light, int blue_light){
  analogWrite(led_red, red_light);
  analogWrite(led_green, green_light);
  analogWrite(led_blue, blue_light);
}

void moveServo(){
    Serial.println("Init");
    if(GateOpen){
        // Portão está aberto
      	RGBColor(60,220,30);
      	Serial.println("O portao esta aberto");
        for(int posInit=pos;posInit >=0;posInit-=1){
            servo_main.write(posInit);
            if(posInit==0){
                pos = posInit;
            }
            delay(15);
        }
        GateOpen=false;
      	Serial.println("O portao foi fechado");
    }else{
        // Portão está fechado
      	Serial.println("O portao esta fechado");
      	RGBColor(60,220,30);
        for(int posInit=pos;posInit<=90;posInit+=1){
            servo_main.write(posInit);
            if(posInit==90){
                pos = posInit;
            }
            delay(15);
        }
        GateOpen = true;
      	Serial.println("O portao foi aberto");
    }
    //Stop servo
    servo_main.writeMicroseconds(1500);
    RGBColor(255,0,0);
    delay(1800);
    RGBColor(245,200,15);
}