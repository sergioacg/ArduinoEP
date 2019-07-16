//Interrupções 

//Declara os PINO do Arduino
const byte push = 2;
byte led = 12;
volatile int ISR_Cont = 0; //Variável da interrupção deve ser volatile
int Cont = 0;

const int Banda = 250;
long Time = 0;
 
void setup()
{
   pinMode(led, OUTPUT);          //PINO 12 (Led) como saída
   pinMode(push, INPUT_PULLUP);   //PINO 2 (push) como entrada com resistência PullUp
   Serial.begin(9600);            //Comunicação Serial a 9600 Baudios
   //Configuração da Interrupção do Arduino, define o PINO 2 (push) como evento de interrupção
   //define a função (InterContador) a ser executado na interrupção
   //e configura que se ative quando o PINO 2 pasa de alto para baixo (FALLING)
   attachInterrupt(digitalPinToInterrupt(push), InterContador, FALLING);
}
 
void loop()
{
   //Coloca Piscar o LED fazendo retardos muito grandes
   digitalWrite(led, HIGH);
   delay(3000);
   digitalWrite(led, LOW);
   delay(3000);
 
   //Instrução para colocar a conta no contador e mostrar no Serial
   if (Cont != ISR_Cont)
   {
      Cont = ISR_Cont;
      Serial.print("Contador: ");
      Serial.println(Cont);
   }
}

//Função Interrupção
void InterContador()
{
  // Aumenta o Contador
  ISR_Cont++;
  
   /*/// Debounce 
   if (millis() - Time > Banda)
   {
      ISR_Cont++;
      Time = millis();
   }*/
}
