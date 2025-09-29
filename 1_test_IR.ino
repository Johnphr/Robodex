/*
  Test de Sensores IR (3 reflectivos)
  - Lee izquierda, centro, derecha
  - Muestra valores en Serial Monitor
  - Enciende LED según detección
*/
int IR_L = A0;
int IR_C = A1;
int IR_R = A2;

int ledL = 10;
int ledC = 11;
int ledR = 12;

void setup() {
  Serial.begin(9600);
  pinMode(IR_L, INPUT);
  pinMode(IR_C, INPUT);
  pinMode(IR_R, INPUT);
  pinMode(ledL, OUTPUT);
  pinMode(ledC, OUTPUT);
  pinMode(ledR, OUTPUT);
}

void loop() {
  int valL = analogRead(IR_L);
  int valC = analogRead(IR_C);
  int valR = analogRead(IR_R);

  Serial.print("L: "); Serial.print(valL);
  Serial.print(" C: "); Serial.print(valC);
  Serial.print(" R: "); Serial.println(valR);

  digitalWrite(ledL, valL < 500 ? HIGH : LOW);
  digitalWrite(ledC, valC < 500 ? HIGH : LOW);
  digitalWrite(ledR, valR < 500 ? HIGH : LOW);

  delay(200);
}
