#include <Servo.h>
/*
  Test de 2 servos: garra y kicker
*/
Servo garra, kicker;

void setup() {
  garra.attach(10);
  kicker.attach(11);
}

void loop() {
  // Garra abre y cierra
  garra.write(0); delay(500);
  garra.write(90); delay(500);
  garra.write(180); delay(500);

  // Kicker movimiento
  kicker.write(0); delay(500);
  kicker.write(90); delay(500);
}
