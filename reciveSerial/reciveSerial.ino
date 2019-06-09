//Criamos a variável contador
int contador=0;
 
void setup(){
  //Configuramos o porto serie
  Serial.begin(9600);
}
 
void loop(){
  //Imprimimos o valor do contador no monitor serial
  Serial.print("Contador: ");
  Serial.println(contador);  
  //incrementamos o contador e esperamos meio segundo
  contador++;
  delay(500);
}
