/*
  Analog input, analog output, serial output

  Reads an analog input pin, maps the result to a range from 0 to 255 and uses
  the result to set the pulse width modulation (PWM) of an output pin.
  Also prints the results to the Serial Monitor.

  The circuit:
  - potentiometer connected to analog pin 0.
    Center pin of the potentiometer goes to the analog pin.
    side pins of the potentiometer go to +5V and ground
  - LED connected from digital pin 9 to ground

  created 29 Dec. 2008
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogInOutSerial
*/

// These constants won't change. They're used to give names to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to



int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

bool flag = 0;
void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
   pinMode(6, OUTPUT);
   pinMode(5, OUTPUT);
}

//loop to check for claps
void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  //for testing purposes
  Serial.print(abs(sensorValue-500));
  Serial.print("\n");


  //if the volume gives a voltage difference that is greater than 500mv, add a clap

  //if it is not following you and it hears a clap, it will start scanning and follow you
  if((abs(sensorValue-500)>270)&&(flag==0))
  {
   digitalWrite(6,HIGH);
   digitalWrite(5,HIGH);
   delay(1000);
   flag=1;
   
  }

  //if it is following you and it hears a clap, it will stop
  else if((abs(sensorValue-500)>350)&&(flag==1))
  {
   digitalWrite(6,LOW);
   digitalWrite(5,LOW);
    delay(1000); 
   flag=0;
   
  }
  

  // wait 2 milliseconds before the next loop for the analog-to-digital
  delay(2);
  
}
