//////////////////////////////////////////////////////////////////
//©2011 bildr
//Released under the MIT License - Please reuse change and share
//Simple code for the ADXL335, prints calculated orientation via serial
// now upgrade with a energy model by Andre Wakko and Alberto de Campo from 
// UDK Berlin
//////////////////////////////////////////////////////////////////

//Analog read pins
const int xPin = 0;
const int yPin = 1;
const int zPin = 2;

//The minimum and maximum values that came from
//the accelerometer while standing still
//You very well may need to change these
int minVal = 265;
int maxVal = 402;

//to hold the caculated values
double x;
double y;
double z;

int valueX;
int valueY;
int valueZ;

// energy entropie
int prevx = 0, prevy = 0, prevz = 0, energy = 0, minEnergy = 40; // test if 40 is high enough!
boolean alive = false;



void setup(){
  Serial.begin(9600);
}

void loop(){
  
  int x,y,z, newsum,lostenergy;

  //read the analog values from the accelerometer
  int xRead = analogRead(xPin);
  int yRead = analogRead(yPin);
  int zRead = analogRead(zPin);

  //convert read values to degrees -90 to 90 - Needed for atan2
  int xAng = map(xRead, minVal, maxVal, -90, 90);
  int yAng = map(yRead, minVal, maxVal, -90, 90);
  int zAng = map(zRead, minVal, maxVal, -90, 90);

  //Caculate 360deg values like so: atan2(-yAng, -zAng)
  //atan2 outputs the value of -π to π (radians)
  //We are then converting the radians to degrees
  x = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI);
  y = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI);
  z = RAD_TO_DEG * (atan2(-yAng, -xAng) + PI);
 
  // energy model: 
  energy = (energy * 0.5) // sets the decay, closer to 1, slower is
    + (((abs(x - prevx)) 
    + (abs(y - prevy))
    + (abs(z - prevz))) * (0.33333));

  prevx = x; prevy = y; prevz = z; 
  
  alive = energy - minEnergy > 0;
  
   if (alive > 0) {
   
  valueX =  x;
  valueY =  y;
  valueZ =  z;
  }
  
  else
  
 { 
   
 lostenergy = energy - 10;
 valueX = constrain(lostenergy, 0, 150);
 valueY = constrain(lostenergy, 0, 150);
 valueZ = constrain(lostenergy, 0, 150);
  
 }
 

  //Output the caculations
  Serial.print("x: ");
  Serial.print(x);
  Serial.print(" | y: ");
  Serial.print(y);
  Serial.print(" | z: ");
  Serial.println(z);
  
  Serial.print("valueX: ");
  Serial.print(valueX);
  Serial.print(" | valueY: ");
  Serial.print(valueY);
  Serial.print(" | valueZ: ");
  Serial.println(valueZ);
  
  delay(50);//just here to slow down the serial output - Easier to read
 
 
  
  
}
