#include <Keypad.h>

byte pinosLinhas[]  = {5,4,3,2};

byte pinosColunas[] = {9,8,7,6};

char teclas[4][4] = {{'S','E','R','G'},
                     {'I','O','6','B'},
                     {'7','8','9','C'},
                     {'*','0','#','D'}};

Keypad teclado1 = Keypad( makeKeymap(teclas), pinosLinhas, pinosColunas, 4, 4);  

void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println("Teclado 4x4 com Biblioteca Keypad");
  Serial.println("Aguardando acionamento das teclas...");
  }

void loop() {
  //Verifica se alguma tecla foi pressionada
  char tecla_pressionada = teclado1.getKey();
  
  //Mostra no serial monitor o caracter da matriz,
  //referente a tecla que foi pressionada
  if (tecla_pressionada)
  {
    Serial.print("Tecla: ");
    Serial.println(tecla_pressionada);
  } 
}
