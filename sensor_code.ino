#define trigPin 13
#define echoPin 12
#define trigPin2 7
#define echoPin2 8

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
}

void loop() {
  long duration, distance;
  long duration2, distance2;
 //writing the first sensor
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);

//writing to echopin
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

//writing to the second sensor
   digitalWrite(trigPin2, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin2, HIGH);

//writing to echopin2
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = ((duration2)/2) / 29.1;
  
  
 
    Serial.print("distance 1 is ");
    Serial.print(distance);
    Serial.println(" cm");

    Serial.print("distance 2 is ");
    Serial.print(distance2);
    Serial.println(" cm");

 if(((distance-distance2)<(-20))&& (distance < 100))
 { 
  Serial.println("turning right");
 }

 if(((distance2- distance)<(-20))&& (distance2 < 100))
 { 
  Serial.println("turning left");
 }
  
  delay(300);
}
