//*************************************************************//
//Display 7 Segmentos Cathode Comúm
int display7c[10]= {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x67};

//Display 7 Segmentos Anode Comúm
int display7a[10]= {0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x18};

//Delcaração dos Pinos do Display
byte a=2;
byte b=3;
byte c=4;
byte d=5;
byte e=6;
byte f=7;
byte g=8;
// Pinos dos Transistors
byte t1=9;
byte t2=10;
byte t3=11;
byte t4=12;
//Contadores do Temporizador
long tempor=0,contret=0;

//Função Display 7 Segmentos
// desde el pin ini hasta el pin fin
void display7seg(int bits,int a,int b,int c,int d,int e,int f,int g){

  //Mostra o numero bits no display 7 segmentos
  digitalWrite(a,bitRead(bits,0));
  digitalWrite(b,bitRead(bits,1));
  digitalWrite(c,bitRead(bits,2));
  digitalWrite(d,bitRead(bits,3));
  digitalWrite(e,bitRead(bits,4));
  digitalWrite(f,bitRead(bits,5));
  digitalWrite(g,bitRead(bits,6));
}

//Função da multiplexação
void mostrar( ) 
{
   int dig[4];   //Vetor dos digitos
   //Dígito Milhar
   dig[0]=tempor/1000;
   //Dígito Centena
   dig[1]=(tempor-dig[0]*1000)/100;
   //Dígito Dezena
   dig[2]=(tempor-dig[0]*1000-dig[1]*100)/10;
   //Dígito Unidade
   dig[3]=(tempor-dig[0]*1000-dig[1]*100-dig[2]*10);

   //Rutina de Multiplexación
   for(int i=t1;i<=t4;i++){ 
     //Chama a Função Display 7 Segmentos
     display7seg(display7c[dig[i-t1]],a,b,c,d,e,f,g); 
     digitalWrite(i,HIGH);  //Liga um display
     delay(1);               //espera um tempinho
     digitalWrite(i,LOW);   //desliga o display
   }                      
}

//Função de tempo do temporizador
void temporizacao() 
{
   contret=50;       //Carregua com 50 a variável CONTRET
   while (contret>0) //Se maior que cero
   {
      mostrar();        //chama a função MOSTRAR
      contret--;        // Decremente a variável CONTRET
   }
}

//Configura os pinos como Saidas
void setup() {
  //Configura os 8 Pinos digitais como SAIDAS
  for(int i=a;i<=t4;i++){
    pinMode(i,OUTPUT);
  }
}

//Programa Principal
void loop() {
   tempor=0;  //Inicializa o temporizador em zero
      while(tempor<9999) //enquanto TEMPOR for menor que 9999
      {
         temporizacao(); //chama função Temporizador
         tempor++;        //Incrementa o tempor 
      }
}
