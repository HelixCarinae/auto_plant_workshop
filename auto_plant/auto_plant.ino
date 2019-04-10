/* \\==========================//
 * // Josh Watson              \\
 * \\ Automated Plant Workshop //
 * // UNB Makerspace           \\
 * \\==========================// */

// Thinking it might be a good idea to create an array for 50 samples or so 
// and then take the average of the samples and use that as our h2o val
// Hopefully this might reduce noise and avoid spikes and bad readings 


// ===== ===== Variables ===== ===== \\

void water();
void light();


const unsigned int t1m = 60000;
//const unsigned short t1s = 6000; 

uint8_t pump = 2; // hooked up to 2n2222a npn transistor
uint8_t lights = 3; // 2n2222a npn transistor (driving 3 LEDs)
uint8_t sensor_pwr = 3; // turns the sensor on/off when not in use to save power and avoid oxidization of the leads  
uint8_t meter = A0; // hygrometer

uint16_t h2o_readings[60] = {0};
uint16_t h2o_goal = 500; // this is how moist you want the soil to be for the plant

unsigned long pump_time = 0; // Time since the pump last turned on (to prevent it from turning on too often) 

// Can use current time minus this to get the time it's been off
unsigned long light_time = 0; // used to track how long the light has been on for


unsigned long h24 = 8.64e7; // 24 h hours in ms 
unsigned long day = 4.32e7; // duration for the light to be on in 12 h = 43200000 ms

unsigned long previous_ms = millis();

bool debug = false;

// ===== ===== Setup ===== ===== \\

void setup() {
  pinMode(pump, INPUT_PULLUP);
  pinMode(lights, INPUT_PULLUP);
  pinMode(pump, OUTPUT);
  pinMode(lights, OUTPUT);
  pinMode(sensor_pwr, OUTPUT);
  if(debug){Serial.begin(9600);}
}


// ===== ===== Loop ===== ===== \\

void loop() {
  
  unsigned long current_ms = millis();
  
  unsigned long h2o_val = 0;

  
  // Takes a reading every 0.1 s over 6 seconds 
  for(int i = 0 ; i < 60 ; i++){
    int reading = analogRead(meter);
    h2o_readings[i] = reading;
    h2o_val += reading;
    delay(100);
  }
  h2o_val = h2o_val/60; // mean of all the readings
 
  if(debug){Serial.println(h2o_val);}
  // Light timing control 
    
  if( light_time < day ) // if it's daytime and we haven't hit our light goal then turn on lights
      light(); 
  
  else if( (light_time - previous_ms) >= h24 ) // new day
        light_time = 0;
  
  else{ // night time
      digitalWrite(lights, LOW);
      light_time = millis();
    }
    
  // Pump timing control
  // Checks if soil is wet enough and if it's been longer than 1 min since last watered 
  if( h2o_val > h2o_goal){ // && (( millis() - pump_time) > t1m) ){
 
      if( digitalRead(lights) ){  // if the lights are one turn them off before watering
        digitalWrite(lights, LOW);
        water();
        digitalWrite(lights, HIGH);
      }
      else{ water(); }
    //  delay(10*t1m);
  } // if hygrometer check

  if( (millis() - previous_ms) > h24 ) { previous_ms = millis(); } 
  
  delay(60000); // wait for 1 minute before checking again

} // loop()



// ===== ===== Functions ===== ===== \\

void water(){
  delay(100);
  digitalWrite(pump, HIGH);
  delay(3000); // pumps water for 5 seconds
  //while(h2o_val < (h2o_goal - 24)){ // loops until the soil value raises to the desired level -24 to account for saturation time }
  digitalWrite(pump, LOW);
  delay(100);
  pump_time = millis();
} 


void light(){
  delay(100);
  digitalWrite(lights, HIGH);
  light_time = millis();
  delay(100);
} // light()
