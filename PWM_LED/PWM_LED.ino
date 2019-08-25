#define LED 3 // PIN 3 as LED
const int POT = A0; //Potenciometro

void setup() {
  // put your setup code here, to run once:
  pinMode(LED,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(LED,analogRead(POT)/4);
}
