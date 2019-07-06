//Sensor de temperatura usando o LM35 e LCD
//Pratica para o aprendizado das entradas analogicas do Arduino (ADC)

//Definições
const int LM35 = A0; // Define o pino que lera a saída do LM35
float temperatura; // Variável que armazenará a temperatura medida
int value;

//Bibliotecas
#include <LiquidCrystal.h> 
LiquidCrystal lcd(10, 9, 8, 5, 4, 3, 2); //(RS, RW, E, D4,D5, D6, D7)
 
 
//Função que será executada uma vez quando ligar ou resetar o Arduino
void setup() {
 lcd.begin(16, 2);   // Inicia o LCD 16x02 (colunas,linhas)
 lcd.home();         // Coloca el cursor en las coordenadas (0,0)
  lcd.print("ADC Arduino");   // Escreve no LCD 
  lcd.setCursor(0,1);         // Coloca el cursor en las coordenadas (0,0)
  lcd.print("Temp: ");   // Escreve no LCD  
} 
 
//Função que será executada continuamente
void loop() {
  
  //Leitura do Pino A0 (ADC)
  value=analogRead(LM35); // Armazena o valor inteiro.
  //Converte o valor inteiro em Temperatura
  temperatura=(value*5/1023.0) / 0.010;
  
  //temperatura = (float(analogRead(LM35))*5/1023)/0.01;     //LM35
  //temperatura = (float(analogRead(LM35))*5/1023-0.5)/0.01; //TMP36

  lcd.setCursor(7,1);
  lcd.print(temperatura);   // Escreve no LCD
  lcd.print(" C");
  delay(1000);
}
