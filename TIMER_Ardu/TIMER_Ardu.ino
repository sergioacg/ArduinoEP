#define LED 13 //Declara o PINO 13 como LED

//Chama as librarías
#include <LiquidCrystal.h>     
#include <TimerOne.h>    

//Variavéis para a interrupção
volatile long int Time=0;

//Configuração do LCD
LiquidCrystal lcd(9, 8, 5, 4, 3, 2); //(RS, E, D4,D5, D6, D7)
 
void setup()
{
   pinMode(LED,OUTPUT);          //LED como Saída
   lcd.begin(20, 4);            // Inicia o LCD 20x04 (colunas, linhas)   
   lcd.setCursor(2, 0);         // Coloca o cursor nas coordenadas (2,0)   
   lcd.print("TIMER COM ARDUINO"); // Escreve no LCD   
   lcd.setCursor(0, 1);         // Coloca o cursor nas coordenadas (0,1) 
   lcd.print("Temporizador:");      // Escreve no LCD
   Timer1.initialize(1000000);      //Configura o TIMER em 1 Segundo
   Timer1.attachInterrupt(Temporizador) ; //Configura a interrupção do Timer 1
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED,HIGH);
  delay(2000);
  digitalWrite(LED,LOW);
  delay(2000);
}

//Função da Interrupção quando se executa o TIMER
void Temporizador(void)
{
  //Incrementa o timer
  Time++;
  //Reinicia o contador quando chega a 1000 segundos
  if(Time>1000){
    Time=0;
  }
  //Mostra no LCD o valor atual do temporizador
  lcd.setCursor(14, 2);
  lcd.print("    ");
  lcd.setCursor(14, 2);
  lcd.print(Time);
}
