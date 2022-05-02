//Arduino-based solar tracker using LDRs and servo motors
//Jude Nkereuwem
//June 2021

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>


Servo baseServo;
Servo jointServo;

LiquidCrystal_I2C lcd(0x27,16,2);

//pin declaration for LDR.
const int ldr1 = A0;
const int ldr2 = A1;
const int ldr3 = A2;
const int ldr4 = A3;

//declare variable to store LDR values.
int valN;
int valW;
int valS;
int valE;
int highestLDR = 0; //store LDR with highest intensity

const int voltgeSensor = A6;   //voltage sensor to Arduino A6 pin

//store values used for analog-voltage conversion
float vOUT = 0.0;
float vIN = 0.0;

//voltage sensor resistor values
float R1 = 30000.0;
float R2 = 7500.0;

int PanelValue = 0; //store panel voltage

void setup() {
  Serial.begin(9600);

  lcd.init();                      
  lcd.backlight();
  lcd.home();
  
  baseServo.attach(10);
  jointServo.attach(9);
}

void loop() {
  //Read values from LDR
  valN = analogRead(ldr1);
  valW = analogRead(ldr2);
  valS = analogRead(ldr3);
  valE = analogRead(ldr4);
  
  PanelValue = analogRead(A6);
  
  vOUT = (PanelValue * 5.0)/1024.0;
  vIN = vOUT / (R2/(R1+R2));  

  /*Find the LDR with highest light intensity 
   *and store it's value in vaiable = highestLDR.
   */
  if((valN>valW)&&(valN>valS)&&(valN>valE)){
    highestLDR = valN;
  }
  else if((valW>valN)&&(valW>valS)&&(valW>valE)){
    highestLDR = valW;
  }
  else if((valS>valN)&&(valS>valW)&&(valS>valE)){
    highestLDR = valS;
  }
  else if((valE>valN)&&(valE>valW)&&(valE>valS)){
    highestLDR = valE;
  }


  /*Main control logic
  * Move Panel to face direction with hightest sunlight
  */

  //North
  if(valN == highestLDR){
    delay(100);
    baseServo.write(0);
    delay(100);
    jointServo.write(0);
    delay(100);
  
    lcd.setCursor(0,0);
    lcd.print("            ");
    lcd.setCursor(0,0);
    lcd.print("P.pos: North");
  }

  //West
  else if(valW == highestLDR){
    delay(100);
    baseServo.write(100);
    delay(100);
    jointServo.write(0);
    delay(100);
        
    lcd.setCursor(0,0);
    lcd.print("            ");
    lcd.setCursor(0,0);
    lcd.print("P.pos: West");
  }

  //South
  else if(valS == highestLDR){
    delay(100);
    baseServo.write(0);
    delay(100);
    jointServo.write(160);
    delay(100);

    lcd.setCursor(0,0);
    lcd.print("            ");
    lcd.setCursor(0,0);
    lcd.print("P.pos: South");
  }

  //East
  else if(valE == highestLDR){
    delay(100);
    baseServo.write(100);
    delay(100);
    jointServo.write(160);
    delay(100);
    
    lcd.setCursor(0,0);
    lcd.print("            ");
    lcd.setCursor(0,0);
    lcd.print("P.pos: East");
  }

  //Display panel voltage
  lcd.setCursor(0,1);
  lcd.print("P.volt: ");
  lcd.print(vIN,2);
  lcd.print(" v  ");
}
