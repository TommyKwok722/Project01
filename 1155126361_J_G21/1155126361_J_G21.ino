/*
  ENGG1100 Given program for demo.
  Board: Arduino Nano
  Version: 201808

Output, Servo1 : (D9)
Output, Servo2 : (D6)
Output,  7-segment (D10,D11)
Output, motors (D3,D2), (D5,D4)
Input: IR sensor long range (A5)
Input: IR sensor left (A4)
Input: IR sensor middle (A3)
Input: IR sensor right (A2)
*/
#include "ENGG1100.h"
#include <Servo.h>
#define BLK 0
#define WHT 1

#define RIGHT_POS 170 
#define REAR_POS 80
#define LEFT_POS 0

#define CLAMP_OPEN 180
#define CLAMP_RELEASE 120
#define CLAMP_CLOSE 83

#define NORMAL_SPEED 240
#define TURN_SPEED 180
#define LEFT_OFFSET 15
#define RIGHT_OFFSET -15

int count=0;
  
FSMClass FSM1;          //The given FSM is named 'FSM1'.
TM1637DisplayClass LEDDisplay(D10, D11); //7-segment LED Display is connected to D10,D11 for debug
ServoClass Servo1(D9);
ServoClass Servo2(D6);
SensorClass S1(A5);
 
SensorClass S2(A4); 
SensorClass S3(A3); 
SensorClass S4(A2); 

SensorClass S5(A0); 
SensorClass S6(A1); 
SensorClass S7(A6); 

MotorClass MotorR(D3,D2);
MotorClass MotorL(D5,D4);

//===== Basically, no need to modify setup() and loop() ====
void setup()
{
  Serial.begin(115200);          //optional, for debug
  LEDDisplay.setBrightness(15); //optional
  FSM1.init(S_999);           // must have this line, you can change the first state of the FSM
  Servo1.init();
  Servo2.init();
}

void loop()
{
    FSM1.run(); //important, don't modify this line              
}
//================= Students add STATES below this line ====================
//----------start of state S_999 -----
void S_999()   
{
  if(FSM1.doTask())
  {
    if(count==12)
      FSM1.transit(S_666); 
    if(count==8||count==9)
    {
    Servo1.setValue(CLAMP_OPEN);
    Servo2.setValue(LEFT_POS);
    LEDDisplay.setValue(000);
    }
    if(count==10||count==11)
    {
    Servo1.setValue(CLAMP_OPEN);
    Servo2.setValue(RIGHT_POS);
    LEDDisplay.setValue(001);
    }
    if(count<3&&count>-1)
    {
    Servo1.setValue(CLAMP_OPEN);
    Servo2.setValue(LEFT_POS);
    LEDDisplay.setValue(999);
    }
    if(count==3)
    {
    Servo1.setValue(CLAMP_OPEN);
    Servo2.setValue(RIGHT_POS);
    LEDDisplay.setValue(998);
    }
    if(count>3&&count<7)
    {
    Servo1.setValue(CLAMP_OPEN);
    Servo2.setValue(RIGHT_POS);
    LEDDisplay.setValue(997);
    }
    if(count==7)
    {
    Servo1.setValue(CLAMP_OPEN);
    Servo2.setValue(LEFT_POS);
    LEDDisplay.setValue(996);
    }
  }
  if (FSM1.getTime() >250) FSM1.transit(S_101);      
}
//------------------------------------
void S_101()   // forward adjustments from start zone to the junction
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(101); 
  }
  if (S2.getHiLow()== WHT && S4.getHiLow()== WHT) FSM1.transit(S_102);
  if (S2.getHiLow()== WHT && S4.getHiLow()== BLK) FSM1.transit(S_103);
  if (S2.getHiLow()== BLK && S4.getHiLow()== WHT) FSM1.transit(S_104);  
  if (S2.getHiLow()== BLK && S3.getHiLow()== BLK && S4.getHiLow()== BLK) 
  {
     if (count>7)FSM1.transit(S_201); 
     if (count<8) FSM1.transit(S_202);    
  }
}
//------------------------------------
void S_102()   // move forward
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(104); 
    MotorR.setSpeed(NORMAL_SPEED+RIGHT_OFFSET-20); 
    MotorL.setSpeed(NORMAL_SPEED+LEFT_OFFSET-20);  
  }
  if (S2.getHiLow()== BLK && S3.getHiLow()== BLK && S4.getHiLow()== BLK) 
  {
     if (count>7) FSM1.transit(S_201); 
     if (count<8) FSM1.transit(S_202);    
  }
  if (!(S2.getHiLow()== WHT && S4.getHiLow()== WHT)) FSM1.transit(S_101);  
}
//------------------------------------
void S_103()   // turn right
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(103); 
    MotorR.setSpeed(0);
    MotorL.setSpeed(TURN_SPEED+LEFT_OFFSET-20);   
  }
  if (S2.getHiLow()== BLK && S3.getHiLow()== BLK && S4.getHiLow()== BLK) 
  {
     if (count>7) FSM1.transit(S_201); 
     if (count<8) FSM1.transit(S_202);    
  }
  if (!(S2.getHiLow()== WHT && S4.getHiLow()== BLK)) FSM1.transit(S_101);   
}
//------------------------------------
void S_104()   // turn left
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(102); 
    MotorR.setSpeed(TURN_SPEED+RIGHT_OFFSET-20);
    MotorL.setSpeed(0);
  }
  if (S2.getHiLow()== BLK && S3.getHiLow()== BLK && S4.getHiLow()== BLK) 
  {
     if (count>7)FSM1.transit(S_201); 
     if (count<8) FSM1.transit(S_202);    
  }
  if (!(S2.getHiLow()== BLK && S4.getHiLow()== WHT)) FSM1.transit(S_101);   
}
//------------------------------------
void S_201()   // at the junction
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(201); 
    MotorR.setSpeed(NORMAL_SPEED+RIGHT_OFFSET-20); 
    MotorL.setSpeed(NORMAL_SPEED+LEFT_OFFSET-20);      
  }
  if ((count>7)&&(FSM1.getTime() >100)) FSM1.transit(S_301); 
}
//------------------------------------
void S_202()   
{
  if(FSM1.doTask())
  {
    if(count>7)   // route 1: center route (DELETE)
    {
    LEDDisplay.setValue(202); 
    MotorR.setSpeed(NORMAL_SPEED+RIGHT_OFFSET); 
    MotorL.setSpeed(NORMAL_SPEED+LEFT_OFFSET);
    if (!(S2.getHiLow()== BLK && S3.getHiLow()== BLK && S4.getHiLow()== BLK)) FSM1.transit(S_301);    
    }
    if(count<4&&count>-1)   // route 1: left route
    {
    LEDDisplay.setValue(202); 
    MotorR.setSpeed(TURN_SPEED+RIGHT_OFFSET);
    MotorL.setSpeed(0); 
    if (S2.getHiLow()== WHT && S3.getHiLow()== WHT) FSM1.transit(S_301);    
    }
    if(count>3&&count<8)  // route 2: right route
    {
    LEDDisplay.setValue(202); 
    MotorR.setSpeed(0); 
    MotorL.setSpeed(TURN_SPEED+LEFT_OFFSET-15); 
    if (S4.getHiLow()== WHT && S3.getHiLow()== WHT) FSM1.transit(S_301);  
    }   
  }   
  //if (S2.getHiLow()== WHT && S3.getHiLow()== BLK && S4.getHiLow()== WHT) FSM1.transit(S_301);
    if(count<4&&count>-1)   // route 1: left route
    {
      if (S2.getHiLow()== WHT && S3.getHiLow()== WHT && S4.getHiLow()== BLK) FSM1.transit(S_301);
    }
    if(count>3&&count<8)  // route 2: right route
    {
      if (S4.getHiLow()== WHT && S3.getHiLow()== WHT && S2.getHiLow()== BLK) FSM1.transit(S_301);  
    }
}
//------------------------------------
void S_301()   // forward adjustments after the junction
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(301); 
  }
  if (S1.getHiLow()== BLK)  FSM1.transit(S_401);
  if (S2.getHiLow()== WHT && S4.getHiLow()== WHT) FSM1.transit(S_302);
  if (S2.getHiLow()== WHT && S4.getHiLow()== BLK) FSM1.transit(S_303);
  if (S2.getHiLow()== BLK && S4.getHiLow()== WHT) FSM1.transit(S_304);   
}
//------------------------------------
void S_302()   // move forward
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(302); 
    MotorR.setSpeed(NORMAL_SPEED+RIGHT_OFFSET+20); 
    MotorL.setSpeed(NORMAL_SPEED+LEFT_OFFSET+20);    
  }
  if (S1.getHiLow()== BLK)  FSM1.transit(S_401);
  if (!(S2.getHiLow()== WHT && S4.getHiLow()== WHT)) FSM1.transit(S_301); 
}
//------------------------------------
void S_303()   // turn right
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(303);
    MotorR.setSpeed(0);  
    MotorL.setSpeed(TURN_SPEED+LEFT_OFFSET-10);
  }
  if (S1.getHiLow()== BLK) FSM1.transit(S_401);
  if (!(S2.getHiLow()== WHT && S4.getHiLow()== BLK)) FSM1.transit(S_301); 
}
//------------------------------------
void S_304()   // turn left
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(304); 
    MotorR.setSpeed(TURN_SPEED+RIGHT_OFFSET-10); 
    MotorL.setSpeed(0);  
  }
  if (S1.getHiLow()== BLK)  FSM1.transit(S_401);
  if (!(S2.getHiLow()== BLK && S4.getHiLow()== WHT)) FSM1.transit(S_301);   
}
//------------------------------------
void S_401()   // detect a cup, then stop and grab the cup
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(401); 
    MotorR.setSpeed(0);
    MotorL.setSpeed(0);
    Servo1.setValue(CLAMP_CLOSE); 
  }
  if ((FSM1.getTime() >500)&&(S1.getHiLow()== BLK))  FSM1.transit(S_402);
}
//------------------------------------
void S_402()   // stop and return to rear position
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(402); 
    MotorR.setSpeed(0);
    MotorL.setSpeed(0);
    Servo2.setValue(REAR_POS);
  }
  if (S1.getHiLow()== BLK)  FSM1.transit(S_501);
}
//------------------------------------
void S_501()   // backward route to the junction after grabbing a cup
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(501); 
  }
  if(count>7)   // forward adjustment for center route (facing backward direction)
  {
  if (S5.getHiLow()== WHT && S6.getHiLow()== BLK && S7.getHiLow()== WHT) FSM1.transit(S_502);
  if (S5.getHiLow()== BLK && S7.getHiLow()== WHT) FSM1.transit(S_504);
  if (S5.getHiLow()== WHT && S7.getHiLow()== BLK) FSM1.transit(S_503);
  if (S5.getHiLow()== BLK && S6.getHiLow()== BLK && S7.getHiLow()== BLK) FSM1.transit(S_505);   
  }
  if(count<4&&count>-1)   // forward adjustment for left route (facing backward direction)
  {
  if (S5.getHiLow()== WHT && S6.getHiLow()== WHT && S7.getHiLow()== WHT) FSM1.transit(S_504);
  if (S5.getHiLow()== WHT && S6.getHiLow()== BLK && S7.getHiLow()== WHT) FSM1.transit(S_502);
  if (S5.getHiLow()== BLK && S7.getHiLow()== WHT) FSM1.transit(S_504);
  if (S5.getHiLow()== WHT && S7.getHiLow()== BLK) FSM1.transit(S_503);
  if (S5.getHiLow()== BLK && S6.getHiLow()== BLK && S7.getHiLow()== BLK) FSM1.transit(S_505);   
  }
  if(count>3&&count<8)   // forward adjustment for right route (facing backward direction)
  {
  if (S5.getHiLow()== WHT && S6.getHiLow()== WHT && S7.getHiLow()== WHT) FSM1.transit(S_503);
  if (S5.getHiLow()== WHT && S6.getHiLow()== BLK && S7.getHiLow()== WHT) FSM1.transit(S_502);
  if (S5.getHiLow()== BLK && S7.getHiLow()== WHT) FSM1.transit(S_504);
  if (S5.getHiLow()== WHT && S7.getHiLow()== BLK) FSM1.transit(S_503);
  if (S5.getHiLow()== BLK && S6.getHiLow()== BLK && S7.getHiLow()== BLK) FSM1.transit(S_505);
  }
}
//------------------------------------
void S_502()   // move forward (facing backward direction)
{
  if(FSM1.doTask())
  {
    if(count<8)
    {
    LEDDisplay.setValue(502); 
    MotorR.setSpeed(-NORMAL_SPEED-RIGHT_OFFSET-10); 
    MotorL.setSpeed(-NORMAL_SPEED-LEFT_OFFSET-10);  
    }
    if(count>7)
    {
    LEDDisplay.setValue(502); 
    MotorR.setSpeed(-NORMAL_SPEED-RIGHT_OFFSET-40); 
    MotorL.setSpeed(-NORMAL_SPEED-LEFT_OFFSET-40);  
    }
  }
  if ((FSM1.getTime() >50)&&(!(S5.getHiLow()== WHT && S7.getHiLow()== WHT))) FSM1.transit(S_501); 
}
//------------------------------------
void S_503()   // turn right (facing backward direction)
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(503);
    MotorR.setSpeed(-TURN_SPEED-RIGHT_OFFSET+10);  
    MotorL.setSpeed(0);
  }
  if (S5.getHiLow()== BLK && S6.getHiLow()== BLK && S7.getHiLow()== BLK) FSM1.transit(S_502);
  if (S6.getHiLow()== BLK && S7.getHiLow()== WHT)  FSM1.transit(S_501); 
}
//------------------------------------
void S_504()   // turn left (facing backward direction)
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(504); 
    MotorR.setSpeed(0); 
    MotorL.setSpeed(-TURN_SPEED-LEFT_OFFSET+10);  
  }
  if (S5.getHiLow()== BLK && S6.getHiLow()== BLK && S7.getHiLow()== BLK) FSM1.transit(S_502);
  if (S5.getHiLow()== WHT && S6.getHiLow()== BLK) FSM1.transit(S_501);   
}
//------------------------------------
void S_505()   // back to the junction
{
  if(count>7)
  {
  if(FSM1.doTask())   // forward adjustment after passing through the junction
  {
    LEDDisplay.setValue(505); 
    MotorR.setSpeed(-NORMAL_SPEED-RIGHT_OFFSET-30); 
    MotorL.setSpeed(-NORMAL_SPEED-LEFT_OFFSET-30);      
  }
  if (S5.getHiLow()== WHT && S7.getHiLow()== BLK) FSM1.transit(S_507);
  if (S5.getHiLow()== BLK && S7.getHiLow()== WHT) FSM1.transit(S_506);
  if (S5.getHiLow()== WHT && S7.getHiLow()== WHT && S6.getHiLow()== WHT && S3.getHiLow()== BLK) FSM1.transit(S_508);
  }
  if(count<4&&count>-1)
  {
  if(FSM1.doTask())   // forward adjustment after passing through the junction
  {
    LEDDisplay.setValue(505); 
    MotorR.setSpeed(-NORMAL_SPEED-RIGHT_OFFSET-10); 
    MotorL.setSpeed(-NORMAL_SPEED-LEFT_OFFSET-10);        
  }
  if ((FSM1.getTime() >0) && (S5.getHiLow()== BLK && S6.getHiLow()== BLK && S7.getHiLow()== BLK)) FSM1.transit(S_510); //*
  if (S5.getHiLow()== WHT && S7.getHiLow()== BLK) FSM1.transit(S_507);
  if ((FSM1.getTime() >200) && (S5.getHiLow()== WHT && S7.getHiLow()== WHT && S6.getHiLow()== WHT && S3.getHiLow()== BLK)) FSM1.transit(S_508);
  }
   if(count>3&&count<8)
  {
  if(FSM1.doTask())   // forward adjustment after passing through the junction
  {
    LEDDisplay.setValue(505); 
    MotorR.setSpeed(-NORMAL_SPEED-RIGHT_OFFSET-10); 
    MotorL.setSpeed(-NORMAL_SPEED-LEFT_OFFSET-10);       
  }
  if ((FSM1.getTime() >0) && (S5.getHiLow()== BLK && S6.getHiLow()== BLK && S7.getHiLow()== BLK)) FSM1.transit(S_509); //*
  if (S5.getHiLow()== BLK && S7.getHiLow()== WHT) FSM1.transit(S_506);
  if ((FSM1.getTime() >200) && (S5.getHiLow()== WHT && S7.getHiLow()== WHT && S6.getHiLow()== WHT && S3.getHiLow()== BLK)) FSM1.transit(S_508);
  }
}
//------------------------------------
void S_506()   // turn left at the junction (for right route only)
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(506); 
    MotorR.setSpeed(0);
    MotorL.setSpeed(-TURN_SPEED-LEFT_OFFSET-30);      
  }
  if (S5.getHiLow()== WHT && S7.getHiLow()== WHT && S6.getHiLow()== BLK) FSM1.transit(S_505);  
  if (S5.getHiLow()== WHT && S7.getHiLow()== WHT && S6.getHiLow()== WHT && S3.getHiLow()== BLK) FSM1.transit(S_508);
}
//------------------------------------
void S_507()   // turn right at the junction (for left route only)
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(507); 
    MotorR.setSpeed(-TURN_SPEED-RIGHT_OFFSET-30);
    MotorL.setSpeed(0);      
  }
  if (S5.getHiLow()== WHT && S7.getHiLow()== WHT && S6.getHiLow()== BLK) FSM1.transit(S_505); 
  if (S5.getHiLow()== WHT && S7.getHiLow()== WHT && S6.getHiLow()== WHT && S3.getHiLow()== BLK) FSM1.transit(S_508);
}
//------------------------------------
void S_508()   // stop and release cup at the end zone
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(508); 
    MotorR.setSpeed(0); 
    MotorL.setSpeed(0); 
    Servo1.setValue(CLAMP_RELEASE);     
    count++; 
  }
  if (FSM1.getTime() >50) FSM1.transit(S_999); 
}
void S_509()   // turn left at the junction (for right route only)
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(509); 
    MotorR.setSpeed(0);
    MotorL.setSpeed(-TURN_SPEED-LEFT_OFFSET-30);      
  }
  if (S5.getHiLow()== WHT && S7.getHiLow()== BLK && S6.getHiLow()== WHT) FSM1.transit(S_511);  
  if (S5.getHiLow()== WHT && S7.getHiLow()== WHT && S6.getHiLow()== WHT && S3.getHiLow()== BLK) FSM1.transit(S_508);
}
//------------------------------------
void S_510()   // turn right at the junction (for left route only)
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(510); 
    MotorR.setSpeed(-TURN_SPEED-RIGHT_OFFSET-30);
    MotorL.setSpeed(0);      
  }
  if (S5.getHiLow()== BLK && S7.getHiLow()== WHT && S6.getHiLow()== WHT) FSM1.transit(S_511); 
  if (S5.getHiLow()== WHT && S7.getHiLow()== WHT && S6.getHiLow()== WHT && S3.getHiLow()== BLK) FSM1.transit(S_508);
}
void S_511()   // turn left or right towards end zone
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(511); 
    if(count<4&&count>-1)
    {
    MotorR.setSpeed(0); 
    MotorL.setSpeed(-TURN_SPEED-LEFT_OFFSET-30);      
    }
    if(count>3&&count<8)
    {
    MotorR.setSpeed(-TURN_SPEED-RIGHT_OFFSET-30); 
    MotorL.setSpeed(0); 
    }
  }
  if (S5.getHiLow()== WHT && S7.getHiLow()== WHT && S6.getHiLow()== BLK) FSM1.transit(S_505); 
  if (S5.getHiLow()== WHT && S7.getHiLow()== WHT && S6.getHiLow()== WHT && S3.getHiLow()== BLK) FSM1.transit(S_508);
}
//------------------------------------
void S_666()   // program ends
{
  if(FSM1.doTask())
  {
    LEDDisplay.setValue(666); 
    MotorR.setSpeed(0); 
    MotorL.setSpeed(0); 
    Servo2.setValue(REAR_POS);
    Servo1.setValue(CLAMP_OPEN);     
  }
}
