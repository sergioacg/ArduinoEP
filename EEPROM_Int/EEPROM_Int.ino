#include <Keypad.h>
#include <LiquidCrystal.h>   
#include <EEPROM.h>

const byte rows = 4; 
const byte col = 4;
const int POT = A3; // Define o pino Analógico (Potenciometro)
int value,PW,CurrentPW=1234;
float volt;
char Key;

byte pRows[]  = {3,2,1,0};
byte pCol[] = {7,6,5,4};
char teclas[4][4] = {{'1','2','3','A'},
                     {'4','5','6','B'},
                     {'7','8','9','C'},
                     {'*','0','#','D'}};

Keypad teclado = Keypad( makeKeymap(teclas), pRows, pCol, rows, col); 
LiquidCrystal lcd(13, 12, 11, 10, 9, 8); //(RS, E, D4,D5, D6, D7)

void setup() {
  lcd.begin(16, 2);   // Inicia o LCD 16x02 (colunas,linhas)
  teclado.setHoldTime(1000); //Tempo de espera para o teclado
  EEPROM.get( 0, PW );
  if(PW!=CurrentPW && PW>0){
    CurrentPW=PW;
  }
  //lcd.print("PW: ");
  //lcd.print(CurrentPW);
  //delay(5000);
}

int password(void){
  int pass,i=0;
  String KeyWord;
  //Pergunta por os 4 digitos da senha
  lcd.setCursor(0, 1);
  while(i<4){
    Key=teclado.waitForKey(); //Espera até presionar botão
    if(Key>='0' && Key<='9'){
      lcd.print('*');
      KeyWord += Key;   //Armazena os caracteres
      i++;
    }
    if(Key=='D'){ 
      i=4;
    }
  }
  if(KeyWord.length()>0){
    pass=KeyWord.toInt(); //Converte para Inteiro
  }else{
    pass=0;
  }
  
  return(pass);
}
void loop() {
  char KeyOp;
  int i,j;
  float vEE[4];
  //Leitura do Pino A3 (ADC)
  value=analogRead(POT); // Armazena o valor inteiro.
  //Converte o valor inteiro em Tensão
  volt=(value*5/1023.0);

  lcd.home();         // Coloca el cursor en las coordenadas (0,0)
  lcd.print("LEITURA VOLTAGEM");   // Escreve no LCD  
  lcd.setCursor(0,1);         // Coloca el cursor en las coordenadas (0,0)
  lcd.print("POT (V): ");   // Escreve no LCD  
  lcd.print(volt);   // Escreve no LCD
  
  Key=teclado.getKey();
  if(Key>='A' && Key<='C'){
    KeyOp=Key;
    lcd.clear();
    lcd.home();         // Coloca el cursor en las coordenadas (0,0)   
    lcd.print("Digite a Senha:"); // Escribe no LCD   
    PW=password();
    //Valida a senha
    if(PW == CurrentPW){
      if(KeyOp=='A'){ //Gravar 4 valores de Voltagem
        lcd.clear();
        lcd.home();         // Coloca el cursor en las coordenadas (0,0)   
        lcd.print("Salvando..."); // Escribe no LCD 
        //Incrementa o for de 4 em 4 até pegar 4 valores 
        for(i=2;i<2+ 4*sizeof(float);i+= sizeof(float)){
          value=analogRead(POT); // Armazena o valor inteiro.
          volt=(value*5/1023.0);
          EEPROM.put( i, volt );  //Grava na EEPROM
          delay(1000);
        }
      }

      if(KeyOp=='B'){ //Trocar a Senha
        lcd.clear();
        lcd.home();         // Coloca el cursor en las coordenadas (0,0)   
        lcd.print("Nova Senha:"); // Escribe no LCD 
        PW=password();
        EEPROM.put( 0, PW );  //Grava na EEPROM
        lcd.clear();
        lcd.home();         // Coloca el cursor en las coordenadas (0,0)   
        lcd.print("Senha Salvada!!!"); // Escribe no LCD
        CurrentPW=PW;
        delay(2000);
      }

      if(KeyOp=='C'){ //Gravar 4 valores de Voltagem
        lcd.clear();
        lcd.home();         // Coloca el cursor en las coordenadas (0,0)   
        j=0;
        //Incrementa o for de 4 em 4 até pegar 4 valores 
        for(i=2;i<2+ 4*sizeof(float);i+= sizeof(float)){
          EEPROM.get( i, vEE[j] );  //le na EEPROM
          j++;
        }
    lcd.setCursor(0,0);
        for(j=0;j<2;j++){         
          lcd.print(j+1);
          lcd.print(')');
          lcd.print(vEE[j]);
          lcd.print("; ");
        }
        lcd.setCursor(0,1);
        for(j=2;j<4;j++){         
          lcd.print(j+1);
          lcd.print(')');
          lcd.print(vEE[j]);
          lcd.print("; ");
        }
        
        delay(10000);
        lcd.clear();
      }
       
    }else{
      lcd.clear();
      lcd.home();         // Coloca el cursor en las coordenadas (0,0)   
      lcd.print("Senha ERRADA!!"); // Escribe no LCD  
      delay(2000); 
    }
  } 
}
