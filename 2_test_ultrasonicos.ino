/*
  Test de sensores ultrasónicos
  - Mide distancia con dos HC-SR04
  - Muestra valores en cm
*/
#define trigFront 6
#define echoFront 7
#define trigBack 8
#define echoBack 9

long medirDistancia(int trig, int echo) {
  digitalWrite(trig, LOW); delayMicroseconds(2);
  digitalWrite(trig, HIGH); delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long duracion = pulseIn(echo, HIGH);
  return duracion * 0.034 / 2;
}

void setup() {
  Serial.begin(9600);
  pinMode(trigFront, OUTPUT); pinMode(echoFront, INPUT);
  pinMode(trigBack, OUTPUT); pinMode(echoBack, INPUT);
}

void loop() {
  long dFront = medirDistancia(trigFront, echoFront);
  long dBack = medirDistancia(trigBack, echoBack);
  Serial.print("Frente: "); Serial.print(dFront); Serial.print(" cm | ");
  Serial.print("Atras: "); Serial.print(dBack); Serial.println(" cm");
  delay(500);
}
