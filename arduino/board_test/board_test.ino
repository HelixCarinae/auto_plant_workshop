#define L_PIN     9  // Pin for Left LEDs
#define M_PIN     10 // Pin for Middle LEDs
#define R_PIN     11 // Pin for Right LEDs
#define PUMP      3  // Pin to control PUMP
#define SNSR_PWR  2 // Pin to turn on power to the sensor to take readings
#define SNSR      A0 // Pin for hygrometer (moisture sensor)

void setup() {
  // Seting up pins to used as outputs to turn on MOSFETS
  pinMode(L_PIN, INTERNAL);
  pinMode(M_PIN, OUTPUT);
  pinMode(R_PIN, OUTPUT);
  pinMode(PUMP, OUTPUT);
  pinMode(SNSR_PWR, OUTPUT);
  Serial.begin(9600);
  
}

void loop() {
  
  // put your main code here, to run repeatedly:
  digitalWrite(SNSR_PWR, HIGH);
  delay(20);
  Serial.println(analogRead(SNSR));
  delay(20);
  digitalWrite(SNSR_PWR, LOW);
  
  digitalWrite(L_PIN, HIGH);
  delay(1000);
  digitalWrite(L_PIN, LOW);

  
  digitalWrite(M_PIN, HIGH);
   delay(1000);
  digitalWrite(M_PIN, LOW);
  
  digitalWrite(R_PIN, HIGH);
  delay(1000);
  digitalWrite(R_PIN, LOW);
  
  delay(1000);

}
