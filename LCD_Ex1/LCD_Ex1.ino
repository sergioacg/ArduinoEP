//Exemplo 1 - Utilização do Display LCD

#include <LiquidCrystal.h>         
 
LiquidCrystal lcd(10, 9, 8, 5, 4, 3, 2); //(RS, RW, E, D4,D5, D6, D7)
 
void setup()
{
   lcd.begin(16, 2);   // Inicia o LCD 16x02 (colunas,linhas)   
   lcd.setCursor(5, 0);   // Coloca o cursor nas coordenadas (5,0)   
   lcd.print("Escola");   // Escreve no LCD   
   lcd.setCursor(5, 1);   // Coloca o cursor nas coordenadas (5,1) 
   lcd.print("Piloto");   // Escreve no LCD 
}
 
void loop()
{
   //Desligar o cursor
   lcd.noCursor();
   delay(500);
   
   //Ligar o cursor
   lcd.cursor();
   delay(500);
}
