

//set the microphone input to the analog signal from the a0 pin
const int analogInPin = A0;  

//set the trigger pins and echo pins to analog 13, 12, 7, and 8 for the ultrasonic sensor
#define trigPin 13
#define echoPin 12
#define trigPin2 7
#define echoPin2 8

//set the motor pin outputs to digital pins 5 and 6 (analog output)
#define leftMotor 5
#define rightMotor 6

//initializing sensorvalue and output value for the microphone
int sensorValue = 0;        
int outputValue = 0;        

//flag for when the follow mode is activated and not activated
bool flag = 0;//clap flag
bool flag2 = 0;//detection flag
bool flag3 = 0;
void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);

  //set up the pins for each motor
  pinMode(rightMotor, OUTPUT);
  pinMode(leftMotor, OUTPUT);

  //set up pins for each sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
}

//loop to check for claps
void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  //for testing and troubleshooting the microphone purposes
  delay(80);
  //initialize variables
  long duration, distance;
  long duration2, distance2;
  
  //check for number of claps
  //if the volume gives a voltage difference that is greater than 500mv, add a clap

  //if it is not following you and it hears a clap (registers a sound wave with a very high amplitude), it will start scanning and follow you
  if((abs(sensorValue-500)>250)&&(flag==0))
  {
   //start following
   while(flag3==0)
   {
    //update sensorvalue to listen for the stop command
    sensorValue = analogRead(analogInPin);
    if((abs(sensorValue-500)>250))
    {
     Serial.print("sleeping");
     digitalWrite(rightMotor,LOW);
     digitalWrite(leftMotor,LOW);
     delay(100);
     //set every flag to 1 to escape all 3 loops
     flag=1;
     flag2=1;
     flag3=1;
    }
    
   //while the robot still has not found you
   while(flag2==0){
    //turn left until it finds you
    digitalWrite(rightMotor,HIGH);
    digitalWrite(leftMotor,LOW);
    
     //writing the right sensor trigpin
     digitalWrite(trigPin, LOW);  
     delayMicroseconds(2); 
     digitalWrite(trigPin, HIGH);

     //writing to right sensor echopin
     delayMicroseconds(10); 
     digitalWrite(trigPin, LOW);
     duration = pulseIn(echoPin, HIGH);
     distance = (duration/2) / 29.1;

    //writing to the left sensor trig pin2
     digitalWrite(trigPin2, LOW);  
     delayMicroseconds(2); 
     digitalWrite(trigPin2, HIGH);

    //writing to the left sensor echopin2 
     delayMicroseconds(10); 
     digitalWrite(trigPin2, LOW);
     duration2 = pulseIn(echoPin2, HIGH);
     distance2 = ((duration2)/2) / 29.1;

    //if something comes into the detection range, follow it by exiting the rotating loop
    if((distance2<100) or (distance<100))
    {
      Serial.print("found the target");
      flag2=1;//does not satisfy while contidition so by setting flag 2 to 1, it breaks the loop
    }//end of distance if
    
     }//end of while
     
 //looking for the person
 //writing the right sensor trigpin
     digitalWrite(trigPin, LOW);  
     delayMicroseconds(2); 
     digitalWrite(trigPin, HIGH);

     //writing to right sensor echopin
     delayMicroseconds(10); 
     digitalWrite(trigPin, LOW);
     duration = pulseIn(echoPin, HIGH);
     distance = (duration/2) / 29.1;

    //writing to the left sensor trig pin2
     digitalWrite(trigPin2, LOW);  
     delayMicroseconds(2); 
     digitalWrite(trigPin2, HIGH);

    //writing to the left sensor echopin2 
     delayMicroseconds(10); 
     digitalWrite(trigPin2, LOW);
     duration2 = pulseIn(echoPin2, HIGH);
     distance2 = ((duration2)/2) / 29.1;

     
     //if the bot finds you it will stop until you move again
     if((distance< 10) && (distance2 < 10))
     {
      //stops
      digitalWrite(rightMotor,LOW);
      digitalWrite(leftMotor,LOW);
      delay(10);
      //flag3=1;// it has caught you and will wait for you to clap again
      
     }
     //if the value from the right sensor is less than the left, indicating there is an object to the right, turn right
     else if(((distance-distance2)<(-20))&& (distance2 < 250))
     { 
      //turns right
      analogWrite(leftMotor,150);
      digitalWrite(rightMotor,LOW);
      delay(10);//let the motors run for awhile
      
      
     }
     
    //if the value from the left sensor is less than that of the right, it indicates there is an object to the left, turn left
    else if(((distance2-distance)<(-20))&& (distance < 250))
    { 
      //turns left
      analogWrite(rightMotor,150);
      digitalWrite(leftMotor,LOW);
      delay(10);//let the motors run for awhile
      
    }

    //if the object does not fall on the peripherals, go straight
    else if((distance2<250)&& (distance<250))
    {
     //drives forward
     analogWrite(rightMotor,150);
     analogWrite(leftMotor,150);
     delay(10);
    }

    
   }
   
    
  
  }//end of following if

  //if it is following you and it hears a clap, it will stop and reset the flag to wait for another clap
  else
  {
    //stops the motors
    digitalWrite(rightMotor,LOW);
    digitalWrite(leftMotor,LOW);
    delay(10);
    
    //reinitialize variables to listen for the clap
    flag=0;
    flag2=0;
    flag3=0;
  }


  // wait 2 milliseconds before the next loop for the analog-to-digital
  delay(2);
  
}
