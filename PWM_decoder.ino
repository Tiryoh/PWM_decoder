/*
 * This program is made for deocding PWM duty ratio.
 * Copyright (c) 2015 Tiryoh <tiryoh@gmail.com>
 *
 * This software is released under the MIT License.
 * http://opensource.org/licenses/mit-license.php
 */

//define period (ms)
#define period 20
//define Max duty ratio (percent)
#define DutyMax 10
//define Min. duty ratio (percent)
#define DutyMin 5

//pin definition
int rcv1 = 7; //1st ch
int rcv2 = 8; //2nd ch
int outPin1_1 = 5;
int outPin1_2 = 6;
int outPin2_1 = 9;
int outPin2_2 = 10;

//variable definition
volatile unsigned long duration1=0,duration2=0;

void setup()
{
  Serial.begin(9600);
  pinMode(rcv1, INPUT);
  pinMode(rcv2, INPUT);
  pinMode(outPin1_1, OUTPUT);
  pinMode(outPin1_2, OUTPUT);
  pinMode(outPin2_1, OUTPUT);
  pinMode(outPin2_2, OUTPUT);
}

void loop()
{
  duration1 = pulseIn(rcv1, HIGH);
  int speedVal1 = map(duration1, period*10*DutyMin, period*10*DutyMax, -255, 255);
  duration2 = pulseIn(rcv2, HIGH);
  int speedVal2 = map(duration2, period*10*DutyMin, period*10*DutyMax, -255, 255);
  speedVal1 = constrain(speedVal1, -255, 255);
  speedVal2 = constrain(speedVal2, -255, 255);
  Serial.print("rcv1:,");
  Serial.print(speedVal1);
  Serial.print(",rcv2:,");
  Serial.println(speedVal2);
  if( speedVal1 > 20)
  {
    analogWrite(outPin1_1, speedVal1);
    digitalWrite(outPin1_2, LOW);
  }
  else if( speedVal1 < -20)
  {
    digitalWrite(outPin1_1, LOW);
    analogWrite(outPin1_2, -speedVal1);
  }
  else
  {
    digitalWrite(outPin1_1, LOW);
    digitalWrite(outPin1_2, LOW);
  }

  if( speedVal2 > 20)
  {
    analogWrite(outPin2_1, speedVal2);
    digitalWrite(outPin2_2, LOW);
  }
  else if( speedVal2 < -20)
  {
    digitalWrite(outPin2_1, LOW);
    analogWrite(outPin2_2, -speedVal2);
  }
  else
  {
    digitalWrite(outPin2_1, LOW);
    digitalWrite(outPin2_2, LOW);
  }
  delayMicroseconds(period*1000);
}
