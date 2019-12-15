#define L_PIN     9  // Pin for Left LEDs
#define M_PIN     10 // Pin for Middle LEDs
#define R_PIN     11 // Pin for Right LEDs
#define PUMP      3  // Pin to control PUMP
#define SNSR_PWR  2 // Pin to turn on power to the sensor to take readings
#define SNSR      A0 // Pin for hygrometer (moisture sensor)

void setup() {
  // Seting up pins to used as outputs to turn on MOSFETS
  pinMode(L_PIN, OUTPUT);
  pinMode(M_PIN, OUTPUT);
  pinMode(R_PIN, OUTPUT);
  pinMode(PUMP, OUTPUT);
  pinMode(SNSR_PWR, OUTPUT);
  Serial.begin(9600);
  
}

void loop() {
  
  // put your main code here, to run repeatedly:
  digitalWrite(SNSR_PWR, HIGH);
  delay(0);
  Serial.println(analogRead(SNSR));
  delay(0);
  digitalWrite(SNSR_PWR, LOW);
  
  digitalWrite(L_PIN, HIGH);
  delay(10);
  digitalWrite(L_PIN, LOW);

  
  digitalWrite(M_PIN, HIGH);
  delay(50);
  digitalWrite(M_PIN, LOW);
  
  digitalWrite(R_PIN, HIGH);
  delay(50);
  digitalWrite(R_PIN, LOW);
  
  digitalWrite(PUMP, HIGH);
  delay(0);
  digitalWrite(PUMP, LOW);



  for(int i = 0 ; i < 3 ; i++){
      for(int j = 9 ; j <= 11 ; j++){
        for(int k = 0 ; j < 3 ; k++){
           digitalWrite(j, HIGH);
           delay(420);
           digitalWrite(j, LOW);
            
          } //k 
      } // j
  } // i
  
  digitalWrite(R_PIN, HIGH);
  digitalWrite(M_PIN, HIGH);
  digitalWrite(L_PIN, HIGH);
  delay(50);
  digitalWrite(R_PIN, LOW);
  digitalWrite(M_PIN, LOW);
  digitalWrite(L_PIN, LOW);
  delay(50);
}
