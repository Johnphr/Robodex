#include <Servo.h>
/*
  Base Pista A - Pelota
  - Detectar pelota con ultrasonico
  - Agarrar con servo garra
  - Detectar color y decidir drop/kick
*/

Servo garra, kicker;
int trigFront = 6, echoFront = 7;

long medirDistancia() {
  digitalWrite(trigFront, LOW); delayMicroseconds(2);
  digitalWrite(trigFront, HIGH); delayMicroseconds(10);
  digitalWrite(trigFront, LOW);
  long duracion = pulseIn(echoFront, HIGH);
  return duracion * 0.034 / 2;
}

void setup() {
  Serial.begin(9600);
  garra.attach(10);
  kicker.attach(11);
  pinMode(trigFront, OUTPUT); pinMode(echoFront, INPUT);
}

void loop() {
  long d = medirDistancia();
  if (d < 8) {
    garra.write(90); // cerrar garra
    Serial.println("Pelota capturada");
    delay(1000);

    // Simular color (random)
    int color = random(0,2); // 0=celeste, 1=amarillo
    if (color == 0) {
      garra.write(0); Serial.println("DROP ball");
    } else {
      kicker.write(90); delay(300); kicker.write(0);
      Serial.println("KICK ball");
    }
    delay(2000);
  }
}
