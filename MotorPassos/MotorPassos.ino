
//Botões
byte PHorario = 2;     //horario
byte PAntiHorario = 3; //anti horario
byte PPassos = 4;       //passos
byte PVel = 5;         //velocidade


// PINOS do Driver
byte IN1=8;  // 28BYJ48 In1
byte IN2=9;  // 28BYJ48 In2
byte IN3=10; // 28BYJ48 In3
byte IN4=11; // 28BYJ48 In4

int horario=1;

int passo=4; //Variável que indica o número de passos 
int Cpasso=0; //Contador de passos

int vel[5]={5,10,30,100,500}; //Vector de velocidade
int Cvel=0; //Contador de Velocidade

int conf=1; //Variável que configura a sequencia de passos

//1 passo
const int UmPasso[4] = {      B1000, 
                             B0100, 
                             B0010, 
                             B0001 };
 
//2 passos
const int DoisPassos[4] = {    B1100, 
                             B0110, 
                             B0011, 
                             B1001 };

// meio passo
byte const  MeioPasso[8] = { B1000,
                             B1100,
                             B0100, 
                             B0110, 
                             B0010, 
                             B0011, 
                             B0001, 
                             B1001 };

//Função que coloca nos pinos de saida os bits comenzando
// desde o pino ini até o pino fin
void pinos(int bits,int ini,int fin){
  for(int i=ini;i<=fin;i++)
  {
    digitalWrite(i,bitRead(bits,i-ini));
  }
}

void setup() {
  
  //Configura ENTRADAS
  for(int i=2;i<=5;i++){
    pinMode(i,INPUT);
  }
  //Configura  SAIDAS
  for(int i=IN1;i<=IN4;i++){
    pinMode(i,OUTPUT);
  }

}

void loop() {

  //******************************************************************************//
  //***********         Pergunta pelos botões    *********************************//
  //******************************************************************************//
  
  // Giro no Sentido Horario
  if(digitalRead(PHorario))  // Pergunta se o botão horario foi presionado
  {
    delay(100); //debounce
    horario=1;
    Cpasso=-1;
  }

  // Giro no Sentido Anti-Horario
  if(digitalRead(PAntiHorario))  // Pergunta se o botão antihorario foi presionado
  {
    delay(100); //debounce
    horario=0;
    Cpasso=passo;
  }

  // Troca a sequencia de passos
  if(digitalRead(PPassos))  // Pergunta se o botão PPassos foi presionado
  {
    delay(100); //Anti-Rebote
    while(digitalRead(PPassos)); //Espera até soltar o botão
    delay(100); //debounce
    conf++;
    //Se já usou as 3 configurações reinicie
    if(conf>3)
      conf=1;
    if(horario==1)
      Cpasso=-1;
    else
      Cpasso=passo;

    pinos(B0000,IN1,IN4);
  }

  // Velocidade del Motor
  if(digitalRead(PVel))  
  {
    delay(100); //Anti-Rebote
    while(digitalRead(PVel)); 
    delay(100); //Anti-Rebote
    Cvel++;
    //Se já usou as 5 velocidades reinicie
    if(Cvel>4)
      Cvel=0;
  }

  //******************************************************************************//
  //***********    Logica dos contadores      *********************************//
  //******************************************************************************//
  if(horario==1)
  {
    Cpasso++;                        //Incremente a variável cont
    if(Cpasso>=passo)
       Cpasso=0;                          //coloca Contador de passos em zero 
  } 
  else{
    Cpasso--;                        //Decrementa a variável cont
    if(Cpasso<0)
       Cpasso=passo-1;                  //coloca Contador igual a passo
  }
  

  //******************************************************************************//
  //***********    Sequencia de Moviminto do Motor   ***************************//
  //******************************************************************************//

       switch(conf){
       case 1:
                pinos(UmPasso[Cpasso],IN1,IN4); //Envía nos pinos a informação da tabela
                passo=4;
                break;
       case 2:
                pinos(DoisPassos[Cpasso],IN1,IN4); //Envía nos pinos a informação da tabela
                passo=4;
                break;
       case 3:
                pinos(MeioPasso[Cpasso],IN1,IN4); //Envía nos pinos a informação da tabela
                passo=8;
                break;
       }
        delay(vel[Cvel]);                      //Atraso de 100 milisegundos
  
}
