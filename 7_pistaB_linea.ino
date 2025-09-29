/*
  Base Pista B - Seguidor de línea simple con 3 sensores IR
*/
int IR_L = A0, IR_C = A1, IR_R = A2;
int motorA1 = 2, motorA2 = 3;
int motorB1 = 4, motorB2 = 5;

void adelante() {
  digitalWrite(motorA1,HIGH); digitalWrite(motorA2,LOW);
  digitalWrite(motorB1,HIGH); digitalWrite(motorB2,LOW);
}
void izquierda() {
  digitalWrite(motorA1,LOW); digitalWrite(motorA2,HIGH);
  digitalWrite(motorB1,HIGH); digitalWrite(motorB2,LOW);
}
void derecha() {
  digitalWrite(motorA1,HIGH); digitalWrite(motorA2,LOW);
  digitalWrite(motorB1,LOW); digitalWrite(motorB2,HIGH);
}
void parar() {
  digitalWrite(motorA1,LOW); digitalWrite(motorA2,LOW);
  digitalWrite(motorB1,LOW); digitalWrite(motorB2,LOW);
}

void setup() {
  pinMode(IR_L,INPUT); pinMode(IR_C,INPUT); pinMode(IR_R,INPUT);
  pinMode(motorA1,OUTPUT); pinMode(motorA2,OUTPUT);
  pinMode(motorB1,OUTPUT); pinMode(motorB2,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int L = analogRead(IR_L);
  int C = analogRead(IR_C);
  int R = analogRead(IR_R);

  if (C < 500) adelante();
  else if (L < 500) izquierda();
  else if (R < 500) derecha();
  else parar();
}
