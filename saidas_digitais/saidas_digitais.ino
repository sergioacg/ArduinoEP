//Delcaración de Los Pines de los LED
byte led1=2;
byte led2=3;
byte led3=4;
byte led4=5;
byte led5=6;
byte led6=7;
byte led7=8;
byte led8=9;

int i; //Variable del Contador del FOR
long vel=100; //Velocidad de las Luces

void setup() {
  // put your setup code here, to run once:
  //Configura los 8 Pines digitales como SALIDAS
  for(i=led1;i<=led8;i++){
    pinMode(i,OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
 //Enciende los LED de Izquierda a Derecha
  for(i=led1;i<=led8;i++){
    digitalWrite(i,HIGH); //Enciende el LED
    delay(vel);           //Retardo (Espera el valor de vel)
  }

  //Apaga los LED de Derecha a Izquierda
  for(i=9;i>=2;i--){
    digitalWrite(i,LOW); //Apaga el LED
    delay(vel);          //Retardo (Espera el valor de vel)
  }

  //Enciende los dos LEDs del Medio
  digitalWrite(led4,1);
  digitalWrite(led5,1);
  delay(1000);     //Retardo de 1000ms (1 segundo)

  //Enciende los LEDs desde el MEDIO hacia los LADOS
  for(i=6;i<=8;i++){
    digitalWrite(i,LOW);
    digitalWrite(i+1,HIGH);
    digitalWrite(11-i,LOW);
    digitalWrite(10-i,HIGH);
    delay(vel*2);  //Espera el Doble del valor de vel
  }
  
}
