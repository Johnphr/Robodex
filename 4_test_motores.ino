/*
  Test de 4 motores
  - Control con 4 pines (dos por cada motor)
*/
int motorA1 = 2, motorA2 = 3;
int motorB1 = 4, motorB2 = 5;
int motorC1 = 6, motorC2 = 7;
int motorD1 = 8, motorD2 = 9;

void adelante() {
  digitalWrite(motorA1, HIGH); digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, HIGH); digitalWrite(motorB2, LOW);
  digitalWrite(motorC1, HIGH); digitalWrite(motorC2, LOW);
  digitalWrite(motorD1, HIGH); digitalWrite(motorD2, LOW);
}

void atras() {
  digitalWrite(motorA1, LOW); digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, LOW); digitalWrite(motorB2, HIGH);
  digitalWrite(motorC1, LOW); digitalWrite(motorC2, HIGH);
  digitalWrite(motorD1, LOW); digitalWrite(motorD2, HIGH);
}

void parar() {
  digitalWrite(motorA1, LOW); digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW); digitalWrite(motorB2, LOW);
  digitalWrite(motorC1, LOW); digitalWrite(motorC2, LOW);
  digitalWrite(motorD1, LOW); digitalWrite(motorD2, LOW);
}

void setup() {
  int pins[] = {motorA1,motorA2,motorB1,motorB2,motorC1,motorC2,motorD1,motorD2};
  for (int i=0;i<8;i++) pinMode(pins[i], OUTPUT);
}

void loop() {
  adelante(); delay(1000); parar(); delay(500);
  atras(); delay(1000); parar(); delay(500);
}
