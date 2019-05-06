//Delcaração dos LED
byte led1=2;
byte led2=3;
byte led3=4;
byte led4=5;
byte led5=6;
byte led6=7;
byte led7=8;
byte led8=9;
byte Pizq=10; //botao esquerdo
byte Pder=11; //botao direito

int i; //Contador para o FOR
long vel=40; //Velocidade das Luzes
byte valor=1; //Armacena o dado do botao

void setup() {
  // put your setup code here, to run once:
  //Configura os 8 Pinos digitais como SAIDAS
  for(i=led1;i<=led8;i++){
    pinMode(i,OUTPUT);
  }
  // Configura os PINOS 10 e 11 Como Entradas
  pinMode(Pizq,INPUT); 
  pinMode(Pder,INPUT);
}

void loop() {
  //Se "valor" é Zero gire para direita
  if(valor==0){
   //Ascende os LEDs da Esquerda a Direita
    for(i=led1;i<=led8+3;i++){
      if(i<=led8){
        digitalWrite(i,HIGH); //Ascende o LED
      }
      
      if(i>led3){
        digitalWrite(i-3,LOW); //Desliga o LED
      }
      delay(vel);           //Atraso (Espera o valor de vel)
      
      //Le os dois botoes
      if(digitalRead(Pizq)){
        valor=1;i=led8+3; //Cambia o valor e sai do FOR
      }
      if(digitalRead(Pder)){
        valor=0;i=led8+3; //Cambia o valor e sai do FOR
      }
    }  
  }

  //Se "valor" é Zero gire para ESQUERDA
  if(valor==1){
   //Ascende os LEDs da Direita a Esquerda 
    for(i=led8;i>=led1-3;i--){
      if(i>=led1){
        digitalWrite(i,HIGH); //Ascende o LED
      }
      
      if(i<led6){
        digitalWrite(i+3,LOW); //Desliga o LED
      }
      delay(vel);           //Atraso (Espera o valor de vel)

      //Le os dois botoes
      if(digitalRead(Pizq)){
        valor=1;i=led1-3; //Cambia o valor e sai do FOR
      }
      if(digitalRead(Pder)){
        valor=0;i=led1-3; //Cambia o valor e sai do FOR
      }
    }  
  }
}
