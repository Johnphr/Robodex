/*
  Base Pista C - Laberinto
  - Estrategia de seguir pared izquierda usando ultrasonico
  - Detecta color y enciende LED
*/
int trigFront = 6, echoFront = 7;
int trigLeft = 8, echoLeft = 9;
int ledAzul=10, ledAmarillo=11, ledRosa=12;

long medirDistancia(int trig, int echo){
  digitalWrite(trig,LOW); delayMicroseconds(2);
  digitalWrite(trig,HIGH); delayMicroseconds(10);
  digitalWrite(trig,LOW);
  long d = pulseIn(echo,HIGH);
  return d*0.034/2;
}

void setup(){
  Serial.begin(9600);
  pinMode(trigFront,OUTPUT); pinMode(echoFront,INPUT);
  pinMode(trigLeft,OUTPUT); pinMode(echoLeft,INPUT);
  pinMode(ledAzul,OUTPUT); pinMode(ledAmarillo,OUTPUT); pinMode(ledRosa,OUTPUT);
}

void loop(){
  long front = medirDistancia(trigFront,echoFront);
  long left = medirDistancia(trigLeft,echoLeft);

  if(left>10){ // libre a izquierda
    Serial.println("Girar Izquierda");
  } else if(front>10){
    Serial.println("Avanzar");
  } else {
    Serial.println("Girar Derecha");
  }

  // Simular detección de color
  int color=random(0,3);
  if(color==0){digitalWrite(ledAzul,HIGH); delay(200); digitalWrite(ledAzul,LOW);}
  if(color==1){digitalWrite(ledAmarillo,HIGH); delay(200); digitalWrite(ledAmarillo,LOW);}
  if(color==2){digitalWrite(ledRosa,HIGH); delay(200); digitalWrite(ledRosa,LOW);}
  delay(1000);
}
