//////////////////////left & right motor run pins
#define ENRF1 24
#define ENRF2 26
#define motor_rightfront 8

#define ENLF1 28
#define ENLF2 30
#define motor_leftfront 13

#define ENRB1 25
#define ENRB2 27
#define motor_rightback 7

#define ENLB1 29
#define ENLB2 31
#define motor_leftback 6

///////////////////////////

//////rightfront motor encoder///////////// 
static int pinA_RF = 11; // Our first hardware interrupt pin is digital pin 2
static int pinB_RF = 12; // Our second hardware interrupt pin is digital pin 3
volatile byte aFlag_RF = 0; // let's us know when we're expecting a rising edge on pinA to signal that the encoder has arrived at a detent
volatile byte bFlag_RF = 0; // let's us know when we're expecting a rising edge on pinB to signal that the encoder has arrived at a detent (opposite direction to when aFlag is set)
long int encoderPos_RF = 0; //this variable stores our current value of encoder position. Change to int or uin16_t instead of byte if you want to record a larger range than 0-255
long int oldEncPos_RF = 0; //stores the last encoder position value so we can compare to the current reading and see if it has changed (so we know when to print to the serial monitor)
volatile byte reading_RF = 0; //somewhere to store the direct values we read from our interrupt pins before checking to see if we have moved a whole detent

//////leftfront motor encoder///////////
static int pinA_LF = 10; // Our first hardware interrupt pin is digital pin 2
static int pinB_LF = 9; // Our second hardware interrupt pin is digital pin 3
volatile byte aFlag_LF = 0; // let's us know when we're expecting a rising edge on pinA to signal that the encoder has arrived at a detent
volatile byte bFlag_LF = 0; // let's us know when we're expecting a rising edge on pinB to signal that the encoder has arrived at a detent (opposite direction to when aFlag is set)
long int encoderPos_LF = 0; //this variable stores our current value of encoder position. Change to int or uin16_t instead of byte if you want to record a larger range than 0-255
long int oldEncPos_LF = 0; //stores the last encoder position value so we can compare to the current reading and see if it has changed (so we know when to print to the serial monitor)
volatile byte reading_LF = 0; //somewhere to store the direct values we read from our interrupt pins before checking to see if we have moved a whole detent

//////rightback motor encoder///////////
static int pinA_RB = 53; // Our first hardware interrupt pin is digital pin 2
static int pinB_RB = 51; // Our second hardware interrupt pin is digital pin 3
volatile byte aFlag_RB = 0; // let's us know when we're expecting a rising edge on pinA to signal that the encoder has arrived at a detent
volatile byte bFlag_RB = 0; // let's us know when we're expecting a rising edge on pinB to signal that the encoder has arrived at a detent (opposite direction to when aFlag is set)
long int encoderPos_RB = 0; //this variable stores our current value of encoder position. Change to int or uin16_t instead of byte if you want to record a larger range than 0-255
long int oldEncPos_RB = 0; //stores the last encoder position value so we can compare to the current reading and see if it has changed (so we know when to print to the serial monitor)
volatile byte reading_RB = 0; //somewhere to store the direct values we read from our interrupt pins before checking to see if we have moved a whole detent

//////leftback motor encoder///////////
static int pinA_LB = 47; // Our first hardware interrupt pin is digital pin 2
static int pinB_LB = 49; // Our second hardware interrupt pin is digital pin 3
volatile byte aFlag_LB = 0; // let's us know when we're expecting a rising edge on pinA to signal that the encoder has arrived at a detent
volatile byte bFlag_LB = 0; // let's us know when we're expecting a rising edge on pinB to signal that the encoder has arrived at a detent (opposite direction to when aFlag is set)
long int encoderPos_LB = 0; //this variable stores our current value of encoder position. Change to int or uin16_t instead of byte if you want to record a larger range than 0-255
long int oldEncPos_LB = 0; //stores the last encoder position value so we can compare to the current reading and see if it has changed (so we know when to print to the serial monitor)
volatile byte reading_LB = 0; //somewhere to store the direct values we read from our interrupt pins before checking to see if we have moved a whole detent

void setup() {
  /////////////////////////left and right encoder pins///////////

  pinMode(pinA_RF, INPUT_PULLUP); // set pinA as an input, pulled HIGH to the logic voltage (5V or 3.3V for most cases)
  pinMode(pinB_RF, INPUT_PULLUP); // set pinB as an input, pulled HIGH to the logic voltage (5V or 3.3V for most cases)
  attachInterrupt(digitalPinToInterrupt(pinA_RF),PinA_RF,RISING); // set an interrupt on PinA, looking for a rising edge signal and executing the "PinA" Interrupt Service Routine (below)
  attachInterrupt(digitalPinToInterrupt(pinB_RF),PinB_RF,RISING); // set an interrupt on PinB, looking for a rising edge signal and executing the "PinB" Interrupt Service Routine (below)

  pinMode(pinA_LF, INPUT_PULLUP); // set pinA as an input, pulled HIGH to the logic voltage (5V or 3.3V for most cases)
  pinMode(pinB_LF, INPUT_PULLUP); // set pinB as an input, pulled HIGH to the logic voltage (5V or 3.3V for most cases)
  attachInterrupt(digitalPinToInterrupt(pinA_LF),PinA_LF,RISING); // set an interrupt on PinA, looking for a rising edge signal and executing the "PinA" Interrupt Service Routine (below)
  attachInterrupt(digitalPinToInterrupt(pinB_LF),PinB_LF,RISING); // set an interrupt on PinB, looking for a rising edge signal and executing the "PinB" Interrupt Service Routine (below)

  pinMode(pinA_RB, INPUT_PULLUP); // set pinA as an input, pulled HIGH to the logic voltage (5V or 3.3V for most cases)
  pinMode(pinB_RB, INPUT_PULLUP); // set pinB as an input, pulled HIGH to the logic voltage (5V or 3.3V for most cases)
  attachInterrupt(digitalPinToInterrupt(pinA_RB),PinA_RB,RISING); // set an interrupt on PinA, looking for a rising edge signal and executing the "PinA" Interrupt Service Routine (below)
  attachInterrupt(digitalPinToInterrupt(pinB_RB),PinB_RB,RISING); // set an interrupt on PinB, looking for a rising edge signal and executing the "PinB" Interrupt Service Routine (below)

  pinMode(pinA_LB, INPUT_PULLUP); // set pinA as an input, pulled HIGH to the logic voltage (5V or 3.3V for most cases)
  pinMode(pinB_LB, INPUT_PULLUP); // set pinB as an input, pulled HIGH to the logic voltage (5V or 3.3V for most cases)
  attachInterrupt(digitalPinToInterrupt(pinA_LB),PinA_LB,RISING); // set an interrupt on PinA, looking for a rising edge signal and executing the "PinA" Interrupt Service Routine (below)
  attachInterrupt(digitalPinToInterrupt(pinB_LB),PinB_LB,RISING); // set an interrupt on PinB, looking for a rising edge signal and executing the "PinB" Interrupt Service Routine (below)
  Serial.begin(115200);

//////////////////////motor run pins/////////////////////
pinMode(ENRF1,OUTPUT);
pinMode(ENRF2,OUTPUT);
pinMode(ENLF1,OUTPUT);
pinMode(ENLF2,OUTPUT);
pinMode(ENRB1,OUTPUT);
pinMode(ENRB2,OUTPUT);
pinMode(ENLB1,OUTPUT);
pinMode(ENLB2,OUTPUT);
pinMode(motor_rightfront,OUTPUT);
pinMode(motor_rightback,OUTPUT);
pinMode(motor_leftfront,OUTPUT);
pinMode(motor_leftback,OUTPUT);

////Rightfront motor rotate commands
analogWrite(motor_rightfront,220);  
digitalWrite(ENRF2,HIGH);
digitalWrite(ENRF1,LOW);//EN

////leftfront motor rotate commands
analogWrite(motor_leftfront,255);  
digitalWrite(ENLF2,HIGH);
digitalWrite(ENLF1,LOW);//EN

////rightback motor rotate commands
analogWrite(motor_rightback,255);  
digitalWrite(ENRB2,HIGH);
digitalWrite(ENRB1,LOW);//EN

////leftback motor rotate commands
analogWrite(motor_leftback,255);  
digitalWrite(ENLB2,HIGH);
digitalWrite(ENLB1,LOW);//EN

}


void loop(){
////Demonstrating the variable values on the screen//// 
Serial.print("RF= ");
Serial.print(encoderPos_RF);
Serial.print(" ,LF= ");
Serial.print(encoderPos_LF);
Serial.print(" ,RB= ");
Serial.print(encoderPos_RB);
Serial.print(" ,LB= ");
Serial.println(encoderPos_LB);


}

// ********************************************** my functions ************************************************************************************************************************

void Action (){


}
////// all function /////////////////////


void PinA_RF(){
  noInterrupts(); //stop interrupts happening before we read pin values
   reading_RF =  4*digitalRead(pinA_RF)+8*digitalRead(pinB_RF); // read all eight pin values then strip away all but pinA and pinB's values
  if(reading_RF == B00001100 &&aFlag_RF) { //check that we have both pins at detent (HIGH) and that we are expecting detent on this pin's rising edge
    encoderPos_RF --; //decrement the encoder's position count
    //bFlag_RF = 0; //reset flags for the next turn
    //aFlag_RF = 0; //reset flags for the next turn
  }
  else if (reading_RF == B00000100) bFlag_RF = 1;  //signal that we're expecting pinB to signal the transition to detent from free rotation
  
   interrupts(); //restart interrupts
 
}

void PinB_RF(){
    noInterrupts(); //stop interrupts happening before we read pin values
   reading_RF = 4*digitalRead(pinA_RF)+8*digitalRead(pinB_RF); //read all eight pin values then strip away all but pinA and pinB's values
   if (reading_RF == B00001100) { //check that we have both pins at detent (HIGH) and that we are expecting detent on this pin's rising edge
   encoderPos_RF ++; //increment the encoder's position count
   bFlag_RF = 0; //reset flags for the next turn
   aFlag_RF = 0; //reset flags for the next turn
    
  }
  else if (reading_RF == B00001000) aFlag_RF = 1;  //signal that we're expecting pinA to signal the transition to detent from free rotation
  interrupts(); //restart interrupts
  
}

/////////////////////////////////////////////////////////////////////////////////////function for leftfront motor//////////////////////////////////////////////////////////////////////////////////

void PinA_LF(){
  noInterrupts(); //stop interrupts happening before we read pin values
  reading_LF =  4*digitalRead(pinA_LF)+8*digitalRead(pinB_LF); // read all eight pin values then strip away all but pinA and pinB's values
  if(reading_LF == B00001100 && aFlag_LF) { //check that we have both pins at detent (HIGH) and that we are expecting detent on this pin's rising edge
    encoderPos_LF --; //decrement the encoder's position count
    bFlag_LF = 0; //reset flags for the next turn
    aFlag_LF = 0; //reset flags for the next turn
  }
  else if (reading_LF == B00000100) bFlag_LF = 1; //signal that we're expecting pinB to signal the transition to detent from free rotation
    interrupts(); //restart interrupts
}

void PinB_LF(){
    noInterrupts(); //stop interrupts happening before we read pin values
  reading_LF = 4*digitalRead(pinA_LF)+8*digitalRead(pinB_LF); //read all eight pin values then strip away all but pinA and pinB's values
  if (reading_LF == B00001100 && bFlag_LF) { //check that we have both pins at detent (HIGH) and that we are expecting detent on this pin's rising edge
    encoderPos_LF ++; //increment the encoder's position count
    bFlag_LF = 0; //reset flags for the next turn
    aFlag_LF = 0; //reset flags for the next turn
  }
  else if (reading_LF == B00001000) aFlag_LF = 1; //signal that we're expecting pinA to signal the transition to detent from free rotation
  interrupts(); //restart interrupts
}

/////////////////////////////////////////////////////////////////////////////////////function for rightback motor//////////////////////////////////////////////////////////////////////////////////

void PinA_RB(){
  noInterrupts(); //stop interrupts happening before we read pin values
  reading_RB =  4*digitalRead(pinA_RB)+8*digitalRead(pinB_RB); // read all eight pin values then strip away all but pinA and pinB's values
  if(reading_RB == B00001100 && aFlag_RB) { //check that we have both pins at detent (HIGH) and that we are expecting detent on this pin's rising edge
    encoderPos_RB --; //decrement the encoder's position count
    bFlag_RB = 0; //reset flags for the next turn
    aFlag_RB = 0; //reset flags for the next turn
  }
  else if (reading_RB == B00000100) bFlag_RB = 1; //signal that we're expecting pinB to signal the transition to detent from free rotation
    interrupts(); //restart interrupts
}

void PinB_RB(){
    noInterrupts(); //stop interrupts happening before we read pin values
  reading_RB = 4*digitalRead(pinA_RB)+8*digitalRead(pinB_RB); //read all eight pin values then strip away all but pinA and pinB's values
  if (reading_RB == B00001100 && bFlag_RB) { //check that we have both pins at detent (HIGH) and that we are expecting detent on this pin's rising edge
    encoderPos_RB ++; //increment the encoder's position count
    bFlag_RB = 0; //reset flags for the next turn
    aFlag_RB = 0; //reset flags for the next turn
  }
  else if (reading_RB == B00001000) aFlag_RB = 1; //signal that we're expecting pinA to signal the transition to detent from free rotation
  interrupts(); //restart interrupts
}

/////////////////////////////////////////////////////////////////////////////////////function for leftback motor//////////////////////////////////////////////////////////////////////////////////

void PinA_LB(){
  noInterrupts(); //stop interrupts happening before we read pin values
  reading_LB =  4*digitalRead(pinA_LB)+8*digitalRead(pinB_LB); // read all eight pin values then strip away all but pinA and pinB's values
  if(reading_LB == B00001100 && aFlag_LB) { //check that we have both pins at detent (HIGH) and that we are expecting detent on this pin's rising edge
    encoderPos_LB --; //decrement the encoder's position count
    bFlag_LB = 0; //reset flags for the next turn
    aFlag_LB = 0; //reset flags for the next turn
  }
  else if (reading_LB == B00000100) bFlag_LB = 1; //signal that we're expecting pinB to signal the transition to detent from free rotation
    interrupts(); //restart interrupts
}

void PinB_LB(){
    noInterrupts(); //stop interrupts happening before we read pin values
  reading_LB = 4*digitalRead(pinA_LB)+8*digitalRead(pinB_LB); //read all eight pin values then strip away all but pinA and pinB's values
  if (reading_LB == B00001100 && bFlag_LB) { //check that we have both pins at detent (HIGH) and that we are expecting detent on this pin's rising edge
    encoderPos_LB ++; //increment the encoder's position count
    bFlag_LB = 0; //reset flags for the next turn
    aFlag_LB = 0; //reset flags for the next turn
  }
  else if (reading_LB == B00001000) aFlag_LB = 1; //signal that we're expecting pinA to signal the transition to detent from free rotation
  interrupts(); //restart interrupts
}
