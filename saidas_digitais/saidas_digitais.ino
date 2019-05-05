//Delcaração dos LED
byte led1=2;
byte led2=3;
byte led3=4;
byte led4=5;
byte led5=6;
byte led6=7;
byte led7=8;
byte led8=9;

int i; //Contador para o FOR
long vel=100; //Velocidade das Luzes

void setup() {
  // put your setup code here, to run once:
  //Configura os 8 Pinos digitais como SAIDAS
  for(i=led1;i<=led8;i++){
    pinMode(i,OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
 //Ascende os LEDs da esquierda para Direita
  for(i=led1;i<=led8;i++){
    digitalWrite(i,HIGH); //Ascende o LED
    delay(vel);           //Atraso (Espera o valor de vel)
  }

  //Desliga os LEDs de Direita para esquerda
  for(i=9;i>=2;i--){
    digitalWrite(i,LOW); //Desliga o LED
    delay(vel);          //Atraso (Espera o valor de vel)
  }

  //Ascende os dois LEDs do Meio
  digitalWrite(led4,1);
  digitalWrite(led5,1);
  delay(1000);     //Atraso de 1000ms (1 segundo)

  //Ascende os LEDs desde o MEIO até os LADOS
  for(i=6;i<=8;i++){
    digitalWrite(i,LOW);
    digitalWrite(i+1,HIGH);
    digitalWrite(11-i,LOW);
    digitalWrite(10-i,HIGH);
    delay(vel*2);  //aguarda o valor de vel veces 2
  }
  
}
