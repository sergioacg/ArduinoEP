//Tensão de Referencia no PINO AREF com Arduino

//Definições
const int POT = A3; // Define o pino Analógico (Potenciometro)
int value;
float volt;

//Bibliotecas
#include <LiquidCrystal.h> 
LiquidCrystal lcd(10, 8, 5, 4, 3, 2); //(RS, E, D4,D5, D6, D7)
 
 
//Função que será executada uma vez quando ligar ou resetar o Arduino
void setup() {
 lcd.begin(16, 2);   // Inicia o LCD 16x02 (colunas,linhas)
 analogReference (DEFAULT);    //Referencia analógica default (5v ou 3.3v)
 //analogReference (EXTERNAL); //Referencia analógica do pino AREF
} 
 
//Função que será executada continuamente
void loop() {
  
  //Leitura do Pino A3 (ADC)
  value=analogRead(POT); // Armazena o valor inteiro.
  //Converte o valor inteiro em Tensão
  //volt=(value*3.3/1023.0);
  volt=(value*5/1023.0);

  //Visualiza no LCD
  lcd.home();         // Coloca el cursor en las coordenadas (0,0)
  lcd.print("POT Int: ");   // Escreve no LCD 
  lcd.print(value);   // Escreve no LCD
  lcd.setCursor(0,1);         // Coloca el cursor en las coordenadas (0,0)
  lcd.print("POT (V): ");   // Escreve no LCD  
  lcd.print(volt);   // Escreve no LCD
  delay(1000);
  lcd.clear();     //Limpa todo o LCD
}
