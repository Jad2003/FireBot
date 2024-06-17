#include <Servo.h>
#include <NewPing.h>
#define A0_PIN A0
#define SERVO_PIN 6
#define ULTRASONIC_SENSOR_TRIG A4
#define ULTRASONIC_SENSOR_ECHO A5
#define DISTANCE_TO_CHECK 60

char command;
int pos = 0; 
const int in1 = 11;//LEFT FORWARD
const int in2 = 10;//LEFT BACK

const int in3= 8;//RIGHT BACK
const int in4 = 9;//RIGHT FORWARD
const int pumpPin=3;
Servo myServo;
Servo myservo1;
NewPing mySensor(ULTRASONIC_SENSOR_TRIG, ULTRASONIC_SENSOR_ECHO, 400);

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(13,INPUT);//FRONT FLAME SENSOR
  pinMode(12,INPUT);//RIGHT SENSOR
  pinMode(7,INPUT);//LEFT SENSOR
  pinMode(pumpPin,OUTPUT);
  myservo1.attach(5); //WATER SERVO 
  myservo1.write(90);
  myServo.attach(SERVO_PIN);
  myServo.write(90);
  Serial.begin(9600);
 
}
void moveForward() {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3,LOW);
    digitalWrite(in4,HIGH);
}
void moveBackward() {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
}
void turnLeft() {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
}
void turnRight() {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
}
void stopCar() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
    }
void pump(){
  digitalWrite(pumpPin, HIGH);
  for (pos = 40; pos <= 90; pos += 1) { 
    myservo1.write(pos);             
    delay(15); 
  }
  for (pos = 90; pos >= 40; pos -= 1) { 
    myservo1.write(pos);                        
    delay(15); 
  }
   digitalWrite(pumpPin, LOW);
}


void executeCommand(char cmd) {
  switch (cmd) {
    case 'F':
      moveForward();
      break;
    case 'B':
      moveBackward();
      break;
    case 'R':
      turnLeft();
      break;
    case 'L':
      turnRight();
      break;
    case 'S':
      stopCar();
      break;
    case 'P':
     pump();
    break;
    case 'Z':
    break;
  }
}


void movetruck(int move) {

  //TURN LEFT
  if (move==1) 
  {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
  //FORWARD
  else if (move==2) 
  {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3,LOW);
    digitalWrite(in4,HIGH);
  }
  //TURN RIGHT
  else if (move==3) 
  {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }
  //REVERSE
  else if (move==4) 
  {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
  }
  //STOP
  else 
  {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }
}

void loop() {

while(Serial.available() > 0) {
    command = Serial.read();
    executeCommand(command); 
}
Serial.println(command);


while(command=='Z' || command==NULL){
int flameValue=analogRead(A0);
int flameON1=digitalRead(13);
int flameON2=digitalRead(12);
int flameON3=digitalRead(7);
int bluetooth=Serial.available();
if(bluetooth>0)
break;


while(flameON1==1)
{
  flameON1=digitalRead(13);
  flameValue=analogRead(A0);
movetruck(2);
if (flameON1==0)
break;
if (flameValue < 80) {
  stopCar();
  digitalWrite(pumpPin, HIGH);
  for (pos = 40; pos <= 90; pos += 1) { 
    myservo1.write(pos);             
    delay(15); 
  }
  for (pos = 90; pos >= 40; pos -= 1) { 
    myservo1.write(pos);                        
    delay(15); 
  }
}
   digitalWrite(pumpPin, LOW);
}

while(flameON1==0 && flameON2==1 && flameON3==1){
  flameON1=digitalRead(13);
  flameON2=digitalRead(12);
  flameON3=digitalRead(7);
  bluetooth=Serial.available();
  if(bluetooth>0)
  break;

if(flameON2==0 && flameON1==0){
  flameON1=digitalRead(13);
  while(flameON1==0)
  {
    movetruck(1);
    flameON1=digitalRead(13);
    if(flameON1==1)
    break;
  }
while(flameON1==1)
{
  flameON1=digitalRead(13);
  flameValue=analogRead(A0);
movetruck(2);
if (flameON1==0)
break;
if (flameValue < 80) {
  stopCar();
  digitalWrite(pumpPin, HIGH);
  for (pos = 40; pos <= 90; pos += 1) { 
    myservo1.write(pos);             
    delay(15); 
  }
  for (pos = 90; pos >= 40; pos -= 1) { 
    myservo1.write(pos);                        
    delay(15); 
  }
}
   digitalWrite(pumpPin, LOW);
}
  }
else if(flameON3==0 && flameON1==0){
  flameON1=digitalRead(13);
  while(flameON1==0)
  {
    movetruck(3);
    flameON1=digitalRead(13);
    if(flameON1==1)
    break;
  }
  while(flameON1==1)
{
  flameON1=digitalRead(13);
  flameValue=analogRead(A0);
movetruck(2);
if (flameON1==0)
break;
if (flameValue < 80) {
  stopCar();
  digitalWrite(pumpPin, HIGH);
  for (pos = 40; pos <= 90; pos += 1) { 
    myservo1.write(pos);             
    delay(15); 
  }
  for (pos = 90; pos >= 40; pos -= 1) { 
    myservo1.write(pos);                        
    delay(15); 
  }
}
   digitalWrite(pumpPin, LOW);
}
}

else{
  movetruck(2);
  int distance = mySensor.ping_cm();
  flameON1=digitalRead(13);
  flameON2=digitalRead(12);
  flameON3=digitalRead(7);
  bluetooth=Serial.available();

  while(flameON1==0 && flameON2==1 && flameON3==1 && distance > DISTANCE_TO_CHECK && bluetooth<=0){
    movetruck(2);
    distance = mySensor.ping_cm();
    flameON1=digitalRead(13);
    flameON2=digitalRead(12);
    flameON3=digitalRead(7);
    bluetooth=Serial.available();
    if(bluetooth>0)
    break;
  }

    movetruck(2);
    distance = mySensor.ping_cm();

  //If distance is within 30 cm then adjust motor direction as below
  while (distance > 0 && distance < DISTANCE_TO_CHECK && flameON1==0 && flameON2==1 && flameON3==1 && bluetooth<=0)
  {

    flameON1=digitalRead(13);
    flameON2=digitalRead(12);
    flameON3=digitalRead(7);
    bluetooth=Serial.available();
    if(flameON1==1 || flameON2==0 ||flameON3==0|| bluetooth>0)
    break;

    movetruck(2);
    distance = mySensor.ping_cm();

    flameON1=digitalRead(13);
    flameON2=digitalRead(12);
    flameON3=digitalRead(7);
    bluetooth=Serial.available();
    if(flameON1==1 || flameON2==0 ||flameON3==0|| bluetooth>0)
    break;

    if(distance < DISTANCE_TO_CHECK){
    //Stop motors
    stopCar();
    delay(500);  

    flameON1=digitalRead(13);
    flameON2=digitalRead(12);
    flameON3=digitalRead(7);
    bluetooth=Serial.available();
    if(flameON1==1 || flameON2==0 ||flameON3==0|| bluetooth>0)
    break;


    //Reverse motors
    movetruck(4);      
    delay(200);

    flameON1=digitalRead(13);
    flameON2=digitalRead(12);
    flameON3=digitalRead(7);
    bluetooth=Serial.available();
    if(flameON1==1 || flameON2==0 ||flameON3==0 || bluetooth>0)
    break;

    //Stop motors
    stopCar();
    delay(500);

    flameON1=digitalRead(13);
    flameON2=digitalRead(12);
    flameON3=digitalRead(7);
    bluetooth=Serial.available();
    if(flameON1==1 || flameON2==0 ||flameON3==0 || bluetooth>0)
    break;

    //Rotate servo to left    
    myServo.write(180);
    delay(500);

    //Read left side distance using ultrasonic sensor
    int distanceLeft = mySensor.ping_cm();    

    //Rotate servo to right
    myServo.write(0);    
    delay(500);    

    //Read right side distance using ultrasonic sensor   
    int distanceRight = mySensor.ping_cm();

    //Bring servo to center
    myServo.write(90); 
    delay(500);        

    flameON1=digitalRead(13);
    flameON2=digitalRead(12);
    flameON3=digitalRead(7);
    bluetooth=Serial.available();
    if(flameON1==1 || flameON2==0 ||flameON3==0 || bluetooth>0)
    break;
  
    if (distanceLeft == 0 )
    {
      movetruck(3);
      delay(200);
    }
    else if (distanceRight == 0 )
    {
      movetruck(1);
      delay(200);
    }
    else if (distanceLeft >= distanceRight)
    {
      movetruck(3);
      delay(200);
    }
    else
    {
    movetruck(1);
    delay(200); 
    }     
    stopCar();
    delay(200);   
}
  }
}
    flameON1=digitalRead(13);
    flameON2=digitalRead(12);
    flameON3=digitalRead(7);
    bluetooth=Serial.available();
    if(flameON1==1 || flameON2==0 ||flameON3==0 || bluetooth>0)
    break;    

    movetruck(2);
    flameON1=digitalRead(13);
    flameON2=digitalRead(12);
    flameON3=digitalRead(7);
    bluetooth=Serial.available();
    if(flameON1==1 || flameON2==0 ||flameON3==0 || bluetooth>0)
    break;
}
if(flameON2==0 && flameON1==0){
  flameON1=digitalRead(13);
  while(flameON1==0)
  {
    movetruck(1);
    flameON1=digitalRead(13);
    if(flameON1==1)
    break;
  }
while(flameON1==1)
{
  flameON1=digitalRead(13);
  flameValue=analogRead(A0);
movetruck(2);
if (flameON1==0)
break;
if (flameValue < 80) {
  stopCar();
  digitalWrite(pumpPin, HIGH);
  for (pos = 40; pos <= 90; pos += 1) { 
    myservo1.write(pos);             
    delay(15); 
  }
  for (pos = 90; pos >= 40; pos -= 1) { 
    myservo1.write(pos);                        
    delay(15); 
  }
}
   digitalWrite(pumpPin, LOW);
}
  }

else if(flameON3==0 && flameON1==0){
  flameON1=digitalRead(13);
  while(flameON1==0)
  {
    movetruck(3);
    flameON1=digitalRead(13);
    if(flameON1==1)
    break;
  }
  while(flameON1==1)
{
  flameON1=digitalRead(13);
  flameValue=analogRead(A0);
movetruck(2);
if (flameON1==0)
break;
if (flameValue < 80) {
  stopCar();
  digitalWrite(pumpPin, HIGH);
  for (pos = 40; pos <= 90; pos += 1) { 
    myservo1.write(pos);             
    delay(15); 
  }
  for (pos = 90; pos >= 40; pos -= 1) { 
    myservo1.write(pos);                        
    delay(15); 
  }
}
   digitalWrite(pumpPin, LOW);
}
}
}
}
