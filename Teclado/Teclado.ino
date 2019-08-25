#include <Keypad.h>

byte pinosLinhas[]  = {9,8,7,6};

byte pinosColunas[] = {5,4,3,2};

char teclas[4][4] = {{'1','2','3','A'},
                     {'4','5','6','B'},
                     {'7','8','9','C'},
                     {'*','0','#','D'}};

Keypad teclado1 = Keypad( makeKeymap(teclas), pinosLinhas, pinosColunas, 4, 4);  

void setup() {
  Serial.begin(9600);
  Serial.println("Teclado 4x4 com Biblioteca Keypad");
  Serial.println("Aguardando acionamento das teclas...");
  Serial.println();
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
