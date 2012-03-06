//////////////////////////////////////////////////////////////////
//©2011 bildr
//Released under the MIT License - Please reuse change and share
//Simple code for the ADXL335, prints calculated orientation via serial
// now upgrade with a energy model by Andre Wakko and Alberto de Campo from 
// UDK Berlin
//////////////////////////////////////////////////////////////////

//The minimum and maximum values that came from
//the accelerometer while standing still
//You very well may need to change these
int minVal = 265;
int maxVal = 402;

//////////sensor 1

//Analog read pins
const int x1Pin = 0;
const int y1Pin = 1;
const int z1Pin = 2;

//to hold the caculated values
double x1;
double y1;
double z1;

int valueX1;
int valueY1;
int valueZ1;

// energy entropie
int prevx1 = 0, prevy1 = 0, prevz1 = 0, energy1 = 0, minEnergy1 = 40; // test if 40 is high enough!
boolean alive1 = false;

////// sensor 2


//Analog read pins
const int x2Pin = 3;
const int y2Pin = 4;
const int z2Pin = 5;

//to hold the caculated values
double x2;
double y2;
double z2;

int valueX2;
int valueY2;
int valueZ2;

// energy entropie
int prevx2 = 0, prevy2 = 0, prevz2 = 0, energy2 = 0, minEnergy2 = 40; // test if 40 is high enough!
boolean alive2 = false;

void setup(){
  Serial.begin(9600);
}


void loop(){
  
  int x1,y1,z1, newsum1,lostenergy1;
  int x2,y2,z2, newsum2,lostenergy2;
  
  //sensor 1 convert

  //read the analog values from the accelerometer
  int x1Read = analogRead(x1Pin);
  int y1Read = analogRead(y1Pin);
  int z1Read = analogRead(z1Pin);

  //convert read values to degrees -90 to 90 - Needed for atan2
  int x1Ang = map(x1Read, minVal, maxVal, -90, 90);
  int y1Ang = map(y1Read, minVal, maxVal, -90, 90);
  int z1Ang = map(z1Read, minVal, maxVal, -90, 90);

  //Caculate 360deg values like so: atan2(-yAng, -zAng)
  //atan2 outputs the value of -π to π (radians)
  //We are then converting the radians to degrees
  x1 = RAD_TO_DEG * (atan2(-y1Ang, -z1Ang) + PI);
  y1 = RAD_TO_DEG * (atan2(-x1Ang, -z1Ang) + PI);
  z1 = RAD_TO_DEG * (atan2(-y1Ang, -x1Ang) + PI);
 
 ///sensor 2 convert
 
   //read the analog values from the accelerometer
  int x2Read = analogRead(x2Pin);
  int y2Read = analogRead(y2Pin);
  int z2Read = analogRead(z2Pin);

  //convert read values to degrees -90 to 90 - Needed for atan2
  int x2Ang = map(x2Read, minVal, maxVal, -90, 90);
  int y2Ang = map(y2Read, minVal, maxVal, -90, 90);
  int z2Ang = map(z2Read, minVal, maxVal, -90, 90);

  //Caculate 360deg values like so: atan2(-yAng, -zAng)
  //atan2 outputs the value of -π to π (radians)
  //We are then converting the radians to degrees
  x2 = RAD_TO_DEG * (atan2(-y2Ang, -z2Ang) + PI);
  y2 = RAD_TO_DEG * (atan2(-x2Ang, -z2Ang) + PI);
  z2 = RAD_TO_DEG * (atan2(-y2Ang, -x2Ang) + PI);
  
  
 
 // sensor 1 Energy
 
  // energy model: 
  energy1 = (energy1 * 0.5) // sets the decay, closer to 1, slower is
    + (((abs(x1 - prevx1)) 
    + (abs(y1 - prevy1))
    + (abs(z1 - prevz1))) * (0.33333));

  prevx1 = x1; prevy1 = y1; prevz1 = z1; 
  
  alive1 = energy1 - minEnergy1 > 0;
  
   if (alive1 > 0) {
   
  valueX1 =  x1;
  valueY1 =  y1;
  valueZ1 =  z1;
  }
  
  else
  
 { 
   
 lostenergy1 = energy1 - 10;
 valueX1 = constrain(lostenergy1, 0, 150);
 valueY1 = constrain(lostenergy1, 0, 150);
 valueZ1 = constrain(lostenergy1, 0, 150);
  
 }
 


 // sensor 2 Energy
 
  // energy model: 
  energy2 = (energy2 * 0.5) // sets the decay, closer to 1, slower is
    + (((abs(x2 - prevx2)) 
    + (abs(y2 - prevy2))
    + (abs(z2 - prevz2))) * (0.33333));

  prevx2 = x2; prevy2 = y2; prevz2 = z2; 
  
  alive2 = energy2 - minEnergy2 > 0;
  
   if (alive2 > 0) {
   
  valueX2 =  x2;
  valueY2 =  y2;
  valueZ2 =  z2;
  }
  
  else
  
 { 
   
 lostenergy2 = energy2 - 10;
 valueX2 = constrain(lostenergy2, 0, 150);
 valueY2 = constrain(lostenergy2, 0, 150);
 valueZ2 = constrain(lostenergy2, 0, 150);
  
 }

 /*
 //Output the caculations
  Serial.print("x: ");
  Serial.print(x1);
  Serial.print(" | y: ");
  Serial.print(y1);
  Serial.print(" | z: ");
  Serial.println(z1);
  
  */
  
  Serial.print("valueX: ");
  Serial.print(valueX1);
  Serial.print(" | valueY: ");
  Serial.print(valueY1);
  Serial.print(" | valueZ: ");
  Serial.println(valueZ1);
  
  
/* 
 //Output the caculations
  Serial.print("x2: ");
  Serial.print(x2);
  Serial.print(" | y2: ");
  Serial.print(y2);
  Serial.print(" | z2: ");
  Serial.println(z2);
  */
  
  Serial.print("valueX2: ");
  Serial.print(valueX2);
  Serial.print(" | valueY2: ");
  Serial.print(valueY2);
  Serial.print(" | valueZ2: ");
  Serial.println(valueZ2);
  
  delay(300);//just here to slow down the serial output - Easier to read
 
 
  
  
}
