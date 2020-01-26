/* \\==========================//
 * // Josh Watson              \\
 * \\ Automated Plant Workshop //
 * // UNB Makerspace Club      \\
 * \\==========================// */

// For running debug test code
bool debug = false;


/* Defining pins we'll be using on the Arduino Nano
   These are the ports that will be controlling our pump and lights
   Along with the hygrometer (moisture sensor)*/

#define PUMP 3 // hooked up to transistor/mosfet

#define HYGROMETER A0 // hygrometer

#define LED_L 9  // Left Section of the LEDs
#define LED_M 10 // Middle section of LEDs 
#define LED_R 11 // Right section of LEDs

#define SENSOR_PWR 2 // turns the sensor on/off when not in use to save power and avoid oxidization of the leads  

const unsigned int t1m = 60000; // One minute in milliseconds


/* Here is where you modified values depending on what kind of plant you want to grow */

int WATER_TIME = 2000; // time that the pump is on in ms
int h2o_goal = 642; // this is how moist you want the soil to be for the plant
int h2o_val = 1024; // Initializing this to the wettest setting so the pump doesn't turn on if something isn't working


/* This code is just setting some variable and function names that will be used later */

void water();
void light();
uint16_t h2o_readings[60] = {0};
unsigned long pump_time = 0; // Time since the pump last turned on (to prevent it from turning on too often) 

// Can use current time minus this to get the time it's been off

unsigned long light_time = 0; // used to track how long the light has been on for
unsigned long h24 = 8.64e7; // 24 h hours in ms 
unsigned long day = 4.32e7; // duration for the light to be on in 12 h = 43200000 ms

unsigned long previous_ms = millis();
  

void setup() {
  pinMode(PUMP, OUTPUT);
  pinMode(SENSOR_PWR, OUTPUT);
  pinMode(LED_L, OUTPUT);
  pinMode(LED_M, OUTPUT);
  pinMode(LED_R, OUTPUT);
  
  if(debug){Serial.begin(9600);}
}


void loop() {
  // First we grab the current time as we'll be making comparisons against it layer 
  unsigned long current_ms = millis();

  // Initializing how moist the soil is to 0 (dry)
  h2o_val = 0;

  
  // Takes a reading every 0.1 s over 6 seconds
  // This is to smooth any perturbences in the readings that might cause a false trigger
  for(int i = 0 ; i < 60 ; i++){
    int reading = analogRead(HYGROMETER);
    h2o_readings[i] = reading;
    h2o_val += reading;
    delay(100);
  }
  
  h2o_val = h2o_val/60; // mean of all the readings
 
  if(debug){Serial.println(h2o_val);}

  // Light timing control   
  if( light_time < day ) // if it's daytime and we haven't hit our light goal then turn on lights
      light_on(); 
  
  else if( (light_time - previous_ms) >= h24 ) // If the light has been on for over 24 hours reset it
        light_time = 0;
  
  else{ // night time
      light_off();
      light_time = millis();
    }
    
  // Pump timing control
  // Checks if soil is wet enough and if it's been longer than 1 min since last watered 
  
  if( h2o_val > h2o_goal){ // && (( millis() - pump_time) > t1m) ){
 
      if( digitalRead(LED_L) || digitalRead(LED_M) || digitalRead(LED_R)  ){  // if the lights are one turn them off before watering
        light_off(); // turn the lights off so the pump can draw enough power
        water(); // turn on the pump and water the plant for WATER_TIME amount of ms
        light_on(); // lastly turn the lights back on 
      }
      else{ water(); }
    //  delay(10*t1m);
  } // if hygrometer check

  if( (millis() - previous_ms) > h24 ) { previous_ms = millis(); } 
  
  // delay(600000); // wait for 10 minute before running through the loop again 

} // loop()


/* Functions */
void water(){
  delay(50);
  digitalWrite(PUMP, HIGH);
  delay(WATER_TIME); // pumps water for n seconds
  
  //while( analogRead(HYGROMETER) >= ( h2o_val - 100 ) ){
    // loops until the soil value raises to the desired level -24 to account for saturation time }
    //delay(100);
    //if(debug){Serial.println(h2o_val);} }

  digitalWrite(PUMP, LOW);
  delay(50);
  pump_time = millis();
} 


void light_on(){
  delay(50);
  digitalWrite(LED_L, HIGH);
  digitalWrite(LED_M, HIGH);
  digitalWrite(LED_R, HIGH);
  light_time = millis();
  delay(50);
} // light()


void light_off(){
  delay(50);
  digitalWrite(LED_L, LOW);
  digitalWrite(LED_M, LOW);
  digitalWrite(LED_R, LOW);
  delay(50);
}
