#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//Cria o objeto lcd com direção 0x27, 16 columnas x 2 linhas
LiquidCrystal_I2C lcd(0x27,16,2);  //

void setup() {
  // Inicializa o LCD
  lcd.init();
  
  //Ascende a luz do fundo.
  lcd.backlight();
  
  //Menssagem
  lcd.setCursor(10, 0);
  lcd.print("CURSO DE ARDUINO");
  lcd.setCursor(7, 1);
  lcd.print("Uso da Tela LCD via I2C");
}

void loop() {
  //deslocamento pra esquerda
  lcd.scrollDisplayLeft(); 
  delay(500);
}
