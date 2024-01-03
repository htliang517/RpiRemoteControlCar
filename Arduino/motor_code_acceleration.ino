#include <Servo.h>

int motorL_A = 8;  //IN1 RED
int motorL_B = 9;  //IN2 ORANGE
int motorR_A = 10; //IN3 YELLOW
int motorR_B = 11; //IN4 GREEN
int servo_pin = 4;
int enA = 6;
int enB = 3;
int motorL_PWM = 0;
int motorR_PWM = 0;
int motorL_max = 0; //240
int motorR_max = 0; //250
Servo front_servo;
int pos = 0; //0往前，90往上
int currentByte = 'b';
// void forward();
const unsigned long ACCEL_SPEEDus = 6000; //3921
unsigned long most_recent_bump_us;
int speedmode = 1; //slow=0, fast=1
int slow_pwmL = 140;
int slow_pwmR = 140;
int fast_pwmL = 240;
int fast_pwmR = 240;

void setup()
{
  front_servo.attach(servo_pin);
  Serial.begin(9600);
  pinMode(motorL_A, OUTPUT);
  pinMode(motorL_B, OUTPUT);
  pinMode(motorR_A, OUTPUT);
  pinMode(motorR_B, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  digitalWrite(motorL_A, LOW);
  digitalWrite(motorL_B, LOW);
  digitalWrite(motorR_A, LOW);
  digitalWrite(motorR_B, LOW);
  motorR_max = fast_pwmR;
  motorL_max = fast_pwmL;
}

void loop()
{

  // put your main code here, to run repeatedly:

  if (Serial.available() > 0)
  {
    int inbyte = Serial.read();
    currentByte = inbyte;
  }
  switch (currentByte)
  {
  case 'w':
    forward();
    break;
  case 's':
    backward();
    break;
  case 'a':
    left();
    break;
  case 'd':
    right();
    break;
  case 'b':
    brake();
    break;
  case 'i':
    // brake();
    openGate();
    break;
  case 'k':
    // brake();
    closeGate();
    break;
  case 'c':
    changeMode();
    break;
  case 'r':
    decrease_L_PWM();
    break;
  case 't':
    increase_L_PWM();
    break;
  case 'y':
    decrease_R_PWM();
    break;
  case 'u':
    increase_R_PWM();
    break;
  }
}
void forward()
{
  if (speedmode == 1)
  {
    while (motorL_PWM < fast_pwmL)
    {
      digitalWrite(motorL_A, HIGH);
      digitalWrite(motorL_B, LOW);
      digitalWrite(motorR_A, HIGH);
      digitalWrite(motorR_B, LOW);

      unsigned long t = micros();
      if (motorL_PWM == 0)
      {
        most_recent_bump_us = t;
      }
      else if (t - most_recent_bump_us < ACCEL_SPEEDus)
      {
        continue;
      }
      else
      {
        most_recent_bump_us += ACCEL_SPEEDus;
      }
      analogWrite(enA, ++motorL_PWM);
      analogWrite(enB, ++motorR_PWM);
    }
    digitalWrite(motorL_A, HIGH);
    digitalWrite(motorL_B, LOW);
    digitalWrite(motorR_A, HIGH);
    digitalWrite(motorR_B, LOW);
    analogWrite(enA, fast_pwmL);
    analogWrite(enB, fast_pwmR);
  }
  if (speedmode == 0)
  {
    motorL_PWM = slow_pwmL;
    motorR_PWM = slow_pwmR;
    analogWrite(enA, motorL_PWM);
    analogWrite(enB, motorR_PWM);
    digitalWrite(motorL_A, HIGH);
    digitalWrite(motorL_B, LOW);
    digitalWrite(motorR_A, HIGH);
    digitalWrite(motorR_B, LOW);
  }
}

void backward()
{
  motorL_PWM = motorL_max;
  motorR_PWM = motorR_max;
  analogWrite(enA, motorL_PWM);
  analogWrite(enB, motorR_PWM);
  digitalWrite(motorL_A, LOW);
  digitalWrite(motorL_B, HIGH);
  digitalWrite(motorR_A, LOW);
  digitalWrite(motorR_B, HIGH);
}
void left()
{
  motorL_PWM = motorL_max;
  motorR_PWM = motorR_max;
  analogWrite(enA, motorL_PWM);
  analogWrite(enB, motorR_PWM);
  digitalWrite(motorL_A, LOW);
  digitalWrite(motorL_B, HIGH);
  digitalWrite(motorR_A, HIGH);
  digitalWrite(motorR_B, LOW);
}
void right()
{
  motorL_PWM = motorL_max;
  motorR_PWM = motorR_max;
  analogWrite(enA, motorL_PWM);
  analogWrite(enB, motorR_PWM);
  digitalWrite(motorL_A, HIGH);
  digitalWrite(motorL_B, LOW);
  digitalWrite(motorR_A, LOW);
  digitalWrite(motorR_B, HIGH);
}
void brake()
{
  if (motorR_PWM > 0 || motorL_PWM > 0)
  {
    while (motorR_PWM > 5 || motorL_PWM > 5)
    {
      motorR_PWM = motorR_PWM / 1.01;
      motorL_PWM = motorL_PWM / 1.01;
      analogWrite(enA, motorL_PWM);
      analogWrite(enB, motorR_PWM);
    }
  }
  digitalWrite(motorL_A, LOW);
  digitalWrite(motorL_B, LOW);
  digitalWrite(motorR_A, LOW);
  digitalWrite(motorR_B, LOW);
  motorL_PWM = 0;
  motorR_PWM = 0;
  analogWrite(enA, motorL_PWM);
  analogWrite(enB, motorR_PWM);
}

void openGate()
{
  for (pos = 0; pos < 90; pos += 1)
  { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    front_servo.write(pos); // tell servo to go to position in variable 'pos'
    delay(15);              // waits 15ms for the servo to reach the position
  }
}
void closeGate()
{
  for (pos = 90; pos > 1; pos -= 1)
  {                         // goes from 180 degrees to 0 degrees
    front_servo.write(pos); // tell servo to go to position in variable 'pos'
    delay(15);              // waits 15ms for the servo to reach the position
  }
}

void changeMode()
{
  if (speedmode == 1)
  {
    speedmode = 0;
    motorL_max = slow_pwmL;
    motorR_max = slow_pwmR;
  }
  else if (speedmode == 0)
  {
    speedmode = 1;
    motorL_max = fast_pwmL;
    motorR_max = fast_pwmR;
  }
}

void increase_L_PWM()
{
  if (speedmode == 1)
  {
    fast_pwmL += 10;
    motorL_max = fast_pwmL;
  }
  else if (speedmode == 0)
  {
    slow_pwmL += 10;
    motorL_max = slow_pwmL;
  }
}

void increase_R_PWM()
{
  if (speedmode == 1)
  {
    fast_pwmR += 10;
    motorR_max = fast_pwmR;
  }
  else if (speedmode == 0)
  {
    slow_pwmR += 10;
    motorR_max = slow_pwmR;
  }
}
void decrease_L_PWM()
{
  if (speedmode == 1)
  {
    fast_pwmL -= 10;
    motorL_max = fast_pwmL;
  }
  else if (speedmode == 0)
  {
    slow_pwmL -= 10;
    motorL_max = slow_pwmL;
  }
}
void decrease_R_PWM()
{
  if (speedmode == 1)
  {
    fast_pwmR -= 10;
    motorR_max = fast_pwmR;
  }
  else if (speedmode == 0)
  {
    slow_pwmR -= 10;
    motorR_max = slow_pwmR;
  }
}
