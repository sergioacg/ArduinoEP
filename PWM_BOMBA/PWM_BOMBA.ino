#define BOMBA 3 // PIN 13 as LED
const int POT = A0; //Potenciometro

void setup() {
  // put your setup code here, to run once:
  pinMode(BOMBA,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(BOMBA,analogRead(POT)/4);
}
