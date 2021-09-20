#define MAX_MOTOR_SPEED 250
#define MIN_MOTOR_SPEED 130
#define L_MOTOR_ENABLE 6
#define R_MOTOR_ENABLE 5
#define R_MOTOR_1 7
#define R_MOTOR_2 8
#define L_MOTOR_1 9
#define L_MOTOR_2 11
#define LINE_FOLLOW_A A1
#define LINE_FOLLOW_B A2
#define LINE_FOLLOW_C A3

void setup() {
 Serial.begin(9600);
 pinMode(L_MOTOR_ENABLE, OUTPUT);
 pinMode(R_MOTOR_ENABLE, OUTPUT);
 pinMode(L_MOTOR_1, OUTPUT);
 pinMode(L_MOTOR_2, OUTPUT);
 pinMode(R_MOTOR_1, OUTPUT);
 pinMode(R_MOTOR_2, OUTPUT);
 pinMode(LINE_FOLLOW_A, INPUT);
 pinMode(LINE_FOLLOW_B, INPUT);
 pinMode(LINE_FOLLOW_C, INPUT);
}
void driveLeftMotor(int speed){
  if(abs(speed)< MIN_MOTOR_SPEED){
    analogWrite(L_MOTOR_ENABLE, speed);
    digitalWrite(L_MOTOR_1, LOW);
    digitalWrite(L_MOTOR_2, LOW);
  }
  else{
    analogWrite(L_MOTOR_ENABLE, abs(speed));
    if(speed>0){
      digitalWrite(L_MOTOR_1, HIGH);
      digitalWrite(L_MOTOR_2, LOW);
    }
    else{
      digitalWrite(L_MOTOR_1, LOW);
      digitalWrite(L_MOTOR_2, HIGH);
    }
  }
}

void driveRightMotor(int speed){
  if(abs(speed)< MIN_MOTOR_SPEED){
    analogWrite(R_MOTOR_ENABLE, speed);
    digitalWrite(R_MOTOR_1, LOW);
    digitalWrite(R_MOTOR_2, LOW);
  }
  else{
    analogWrite(R_MOTOR_ENABLE, abs(speed));
    if(speed>0){
      digitalWrite(R_MOTOR_1, LOW);
      digitalWrite(R_MOTOR_2, HIGH);
    }
    else{
      digitalWrite(R_MOTOR_1, HIGH);
      digitalWrite(R_MOTOR_2, LOW);
    }
  }
}
void loop() {
  int value = analogRead(LINE_FOLLOW_C);
  Serial.println(value);
  if(value<600){
    driveRightMotor(-210);
    driveLeftMotor(210);
    delay(15);
    driveRightMotor(0);
    driveLeftMotor(0);
    delay(50);
  }
  else if(value>850){
      driveRightMotor(210);
      driveLeftMotor(-210);
      delay(30);
      driveRightMotor(0);
      driveLeftMotor(0);
      delay(50);
  } else {
      driveRightMotor(-150);
      driveLeftMotor(-160);
      delay(50);
      driveRightMotor(0);
      driveLeftMotor(0);
      delay(20);
  }
 
}
