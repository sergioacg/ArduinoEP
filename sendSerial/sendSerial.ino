//Display 7 Segmentos Cathod3 Comúm
int display7c[10]= {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x67};

//Display 7 Segmentos Anode Comúm
int display7a[10]= {0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x18};

//Pinos do Display
byte a=2;
byte b=3;
byte c=4;
byte d=5;
byte e=6;
byte f=7;
byte g=8;

int dado=0;
byte led = 13;

//Função Display 7 Segmentos
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

void setup(){
   //Configura os 8 Pinos digitais como SAIDAS
  for(int i=a;i<=g;i++){
    pinMode(i,OUTPUT);
  }
  Serial.begin(9600);
  pinMode(led, OUTPUT); 
  //Inicializa o display 7 segmentos
  display7seg(display7c[0],a,b,c,d,e,f,g);
}
 
void loop(){
  //se existe dados disponiveis no barramento serial
  if (Serial.available()){
    //lemos o dado enviado
    dado=Serial.read();
    if(dado=='l') { //letra   l - ligar
      digitalWrite(led, HIGH);
      Serial.println("LED ON");
    }
    if(dado=='d') { //letra d - desligar
      digitalWrite(led, LOW);
      Serial.println("LED OFF");
    }

    if(dado>='0' && dado<='9') { 
      display7seg(display7c[dado-48],a,b,c,d,e,f,g);
      Serial.print("DADO: ");
      Serial.println(dado-48);
    }
  }
}
