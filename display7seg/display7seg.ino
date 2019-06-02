
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
byte inc=9;    //Botão Incremento (Resistencia pulldown)
byte dec=10;   //Botão Decremento (Resistencia pullup)
int contador=0;

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

void setup() {
  //Configura os 8 Pinos digitais como SAIDAS
  for(int i=a;i<=g;i++){
    pinMode(i,OUTPUT);
  }
  pinMode(inc,INPUT);
  pinMode(dec,INPUT_PULLUP); //ConfiguraResistencia PULLUP
}

void loop() {
    //Incremento do Contador
    if(digitalRead(inc)){
      delay(100);
      while(digitalRead(inc)); //Anti-Bounce
      delay(100);
      contador++;
    }

    //Decremento do Contador
    if(!digitalRead(dec)){
      delay(100);
      while(!digitalRead(dec)); //Anti-Bounce
      delay(100);
      contador--;
    }

    //Se contador é maior que 9 quando incrementando
    if(contador>9){
      contador=0;
    }

    //Se contador é menor que 0 quando decrementando
    if(contador<0){
      contador=9;
    }
    
    //Chama a Função Display 7 Segmentos
    display7seg(display7c[contador],a,b,c,d,e,f,g);
}
