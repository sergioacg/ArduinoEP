#include <Servo.h>  //Include the Servo Library

int degree=0;
String words;       
Servo servo1;   // "Servos" objects are created

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Servos - Arduino");
  //servo1.attach(5); //Default
  servo1.attach(5,600,2400);
  servo1.write(0);
}

void loop() {
  // put your main code here, to run repeatedly:
 
  while (Serial.available()) {    // Read the value sent by the Serial Port
    delay(5);
    char c  = Serial.read();     // Read the characters
    words += c;              // Convert Characters to character string
  }  
  if (words.length()>0){       
        degree = words.toInt();   // Convert character string to integers
        Serial.print(degree);         //Send value in Degrees
        Serial.println(" Grados");
        delay(5);
        servo1.write(degree); // Ajuste de 512 vueltas a los 360 grados
        while(servo1.read()<degree-3)
        {Serial.println("Desplazando...");}
  }  

  words = "";   // Initialize the string of characters received 
  
}
