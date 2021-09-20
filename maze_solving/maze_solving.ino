#include <Ultrasonic.h>
#define MAX_MOTOR_SPEED 255 //max motor speed
#define MIN_MOTOR_SPEED 120 //min motor speed
#define L_MOTOR_ENABLE 6 
#define R_MOTOR_ENABLE 5
#define R_MOTOR_1 7
#define R_MOTOR_2 8
#define L_MOTOR_1 9
#define L_MOTOR_2 11
#define IR_SENSOR A0

Ultrasonic leftSensor(12,10,10000UL);
Ultrasonic frontSensor(A5,A4,10000UL);
unsigned long startTime = millis();

void setup() 
{
  Serial.begin(9600);
  pinMode(L_MOTOR_ENABLE, OUTPUT);
  pinMode(R_MOTOR_ENABLE, OUTPUT);
  pinMode(L_MOTOR_1, OUTPUT);
  pinMode(L_MOTOR_2, OUTPUT);
  pinMode(R_MOTOR_1, OUTPUT);
  pinMode(R_MOTOR_2, OUTPUT);
  pinMode(IR_SENSOR, INPUT);
}

void loop() {
  int distanceLeft = leftSensor.read();
  int distanceFront = frontSensor.read();
  bool noWall = digitalRead(A0);
  Serial.println(distanceFront);

  if(noWall){
    Serial.println("turn left");
    leftTurn();
  }
  else if(distanceFront < 14) {
    Serial.println("turn right");
    rightTurn();
  }
  else{
    wallFollowing(distanceLeft);
    Serial.println("Wall Follow");
  }

 
}

void wallFollowing(int distanceLeft){
 if(distanceLeft < 10){
    driveRightMotor(120);
    driveLeftMotor(180);
  } else if (distanceLeft > 14) {
    driveRightMotor(130);
    driveLeftMotor(120);
  } else {
    driveRightMotor(143);
    driveLeftMotor(170);
  }
}

void rightTurn(){
  driveLeftMotor(160);
  driveRightMotor(-160);
  delay(210);
  driveLeftMotor(0);
  driveRightMotor(0);
  delay(400);
}

void leftTurn(){
  delay (200);
  driveLeftMotor(-160);
  driveRightMotor(160);
  delay(200);
  driveLeftMotor(0);
  driveRightMotor(0);
  delay(500);
  driveRightMotor(143);
  driveLeftMotor(170);
  delay(400);
}
//MOTOR DRIVES
void driveLeftMotor(int speed){
  if(abs(speed)<MIN_MOTOR_SPEED){
    analogWrite(L_MOTOR_ENABLE,speed);
    digitalWrite(L_MOTOR_1, LOW);
    digitalWrite(L_MOTOR_2, LOW);
  }
  else{
    analogWrite(L_MOTOR_ENABLE, abs(speed));
    if(speed>0){
      digitalWrite(L_MOTOR_1, HIGH);
      digitalWrite (L_MOTOR_2, LOW);
    }
    else{
      digitalWrite(L_MOTOR_1, LOW);
      digitalWrite (L_MOTOR_2, HIGH);
    }
  }
}

void driveRightMotor(int speed){
  if(abs(speed)<MIN_MOTOR_SPEED){
    analogWrite(R_MOTOR_ENABLE,speed);
    digitalWrite(R_MOTOR_1, LOW);
    digitalWrite(R_MOTOR_2, LOW);
  }
  else{
    analogWrite(R_MOTOR_ENABLE, abs(speed));
    if(speed>0){
      digitalWrite(R_MOTOR_1, LOW);
      digitalWrite (R_MOTOR_2, HIGH);
    }
    else{
      digitalWrite(R_MOTOR_1, HIGH);
      digitalWrite (R_MOTOR_2, LOW);
    }
  }
}
