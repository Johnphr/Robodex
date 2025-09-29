/*
  Base Sube y baja
  - Detecta rampa con ultrasonico
  - Avanza lento para cruzar, luego acelera
*/
int trigFront=6, echoFront=7;
int motorA1=2,motorA2=3,motorB1=4,motorB2=5;

void adelante(int vel){
  analogWrite(motorA1,vel); analogWrite(motorA2,0);
  analogWrite(motorB1,vel); analogWrite(motorB2,0);
}

long medirDistancia(){
  digitalWrite(trigFront,LOW); delayMicroseconds(2);
  digitalWrite(trigFront,HIGH); delayMicroseconds(10);
  digitalWrite(trigFront,LOW);
  long d=pulseIn(echoFront,HIGH);
  return d*0.034/2;
}

void setup(){
  Serial.begin(9600);
  pinMode(trigFront,OUTPUT); pinMode(echoFront,INPUT);
  pinMode(motorA1,OUTPUT); pinMode(motorA2,OUTPUT);
  pinMode(motorB1,OUTPUT); pinMode(motorB2,OUTPUT);
}

void loop(){
  long d=medirDistancia();
  if(d>30){ // no hay suelo cercano (rampa detectada)
    adelante(100); // despacio
    Serial.println("Subiendo rampa");
  } else {
    adelante(200); // normal
    Serial.println("Avanzando normal");
  }
  delay(500);
}
