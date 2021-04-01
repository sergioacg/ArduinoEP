/******************************************************
 * ****************************************************
 * ****  CONTROL PID DE TEMPERATURA               *****
 * ****  By: SERGIO ANDRES CASTAÑO GIRALDO        *****
 * ****  https://controlautomaticoeducacion.com/  *****
 * ****                                           *****
 * ****************************************************
 */


#include <TimerOne.h> 


// Definiciones componentes de la tarjeta
#define sensor1 A0  //TMP36
#define sensor2 A2  //TMP36
#define heater1 3   //TIP31C
#define heater2 5   //TIP31C
#define hot     9   //Led

//Variables Globales
float T1,aux;       //Temperatura del Heater 1
float r1=0.0;  //Referencia del Heater 1
volatile float u=0.0,u_1=0.0;    //Acción de Control
byte Ts = 8; //Periodo de muestreo
//Parámetros del PID
float kp,ti,td;
volatile float q0,q1,q2;  
volatile float e=0.0,e_1=0.0,e_2=0.0;
      
float k=1.04,tau=160,theta=10+Ts/2;   //Parámetros del Modelo del sistema
float Tlc,eps,Wn,P1,P2,tau_d;            //Parámetros del diseño por asignación de polos


String dato;

bool Matlab = false; // 0: Usa el Serial Plotter; 1: Usa la interfaz de Matlab

/* Tipo de Control:
 *  1: Control por Asignación de Polos
 *  2: Control por Cancelamiento de polos
 *  3: Control por Ziegler y Nichols
 */
byte type = 3;
/*===========================================================================*/
/*=======================    FUNCION DEL CONTROL PID  =======================*/
/*===========================================================================*/
void PID(void)
{
    
    e=(r1-T1);
    // Controle PID
      u = u_1 + q0*e + q1*e_1 + q2*e_2; //Ley del controlador PID discreto
    
    if (u >= 100.0)        //Saturo la accion de control 'uT' en un tope maximo y minimo
     u = 100.0;
    
    if (u <= 0.0 || r1==0)
     u = 0.0;
     
     
     
     //Retorno a los valores reales
     e_2=e_1;
     e_1=e;
     u_1=u;
     
     //La accion calculada la transformo en PWM
     
     analogWrite(heater1,map(u, 0,100, 0,255));
     
}

//Función del Periodo de Muestreo (Timer 1)
void SampleTime(void)
{
  digitalWrite(hot, !digitalRead(hot)); //Led Toggle
  PID();
}

void setup() {
  pinMode(hot,OUTPUT);  //Led "Caliente" como salida
  digitalWrite(hot,LOW);
  analogReference (EXTERNAL); //Referencia analógica PIN AREF (3,3v)
  //Configuramos el puerto serial
  Serial.begin(9600);

  //Espera 10 segundos en Stand by cuando es energizado la primera vez
  if(!Matlab){
    delay(10000);
    r1=40.0;
  }
    
  //Valor máximo del Timer es 8.3 Segundos
  Timer1.initialize(8000000);      //Configura el TIMER en 8 Segundos
  Timer1.attachInterrupt(SampleTime) ; //Configura la interrupción del Timer 1

  switch (type){
    
  case 1:
  //*************************************************************************//
  //*************  DISEÑO POR ASIGNACIÓN DE 2 POLOS   ****************//
  //*************************************************************************//
   
   Tlc=220.0;                   //Tiempo de establecimiento deseado en Lazo Cerrado 
   eps = 0.6901;                //Factor de Amortiguamiento   
   Wn=4.0/(eps*Tlc);            //Frecuencia natural del sistema
   
   //Ubicación de 2 Polos 
   P1=2.0*eps*Wn;
   P2=Wn*Wn;
   
   kp=(P1*tau-1.0)/k;        //Calculo de Kc
   ti=(k*kp)/(P2*tau);     //Calculo de ti
   td=0.0;
   break;
   
   case 2:
   //*************************************************************************//
   //*****************   DISEÑO POR CANCELACIÓN DE POLOS    *******************//
   //*************************************************************************//
   
   tau_d=45.0;                  //Constante de Tiempo Deseada
   kp=(tau)/(tau_d*k);         //Calculo de Kc
   ti=tau;                   //Calculo de Ti (Igual a la constante de tiempo)
   td=0;
   break;

   case 3:
   //*************************************************************************//
   //*****************   SINTONIA POR ZIEGLER y NICHOLS    *******************//
   //*************************************************************************//

   kp=(1.2*tau)/(k*theta);
   ti=2.0*theta;
   td=0.5*theta;
   break;
  }

   //*************************************************************************//
   //*****************           PID DIGITAL               *******************//
   //*************************************************************************//

  // Calculo do controle PID digital
   q0=kp*(1+Ts/(2.0*ti)+td/Ts);
   q1=-kp*(1-Ts/(2.0*ti)+(2.0*td)/Ts);
   q2=(kp*td)/Ts;
}

void loop() {
  int i,ini=0,fin=0;
  String degC;

  //Filtro de promedio movil en la lectura ADC
  aux=0;
  for(i=0;i<10;i++){
    aux = aux + (float(analogRead(sensor1))*3.3/1023.0-0.5)/0.01; //TMP36
    //delay(5);
  }
  T1 = aux/10.0;

  //T1= (float(analogRead(sensor1))*5.0/1023.0-0.5)/0.01; //TMP36

  if(Matlab){ //Usar la interfaz de Matlab

  //___________________________________________
    if (Serial.available()){
      //leemos el dato enviado
      dato=Serial.readString();
      //Busco el valor del escalon en los datos recibidos
      for(i=0;i<10;i++){
        if(dato[i]=='S'){
          ini=i+1;
          i=10;
        }
       }
       for(i=ini;i<10;i++){
        if(dato[i]=='$'){
          fin=i;
          i=10;
        }
       }
       // salvo en degC el caracter con el escalon
        degC=dato.substring(ini, fin);
      r1 = degC.toInt();   // Convert character string to integers
    }
  //____________________________________________
  
      Serial.print("I");
      Serial.print(T1);
      Serial.print("F");
      Serial.print("I");
      Serial.print(T1);
      Serial.print("F");
  
      Serial.print("C");
      Serial.print(u);
      Serial.print("R");
      Serial.print("C");
      Serial.print(u);
      Serial.print("R");
  }
  else{  //Usar el Serial Plotter
    Serial.println("Temperatura_1,Setpoint_1");
    Serial.print(T1);
    Serial.print(","); 
    Serial.println(r1); 
  }
  
  delay(1000);
}
