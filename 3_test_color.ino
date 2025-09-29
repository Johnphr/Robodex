/*
  Test de sensor de color (ejemplo TCS3200 o similar)
  - Requiere librería del sensor
  - Aquí mostramos pseudocódigo simple con Serial
*/
void setup() {
  Serial.begin(9600);
  // Inicialización específica depende del sensor usado (TCS3200, TCS34725, etc.)
  Serial.println("Test Sensor de Color iniciado");
}

void loop() {
  // Simular detección
  int R = random(0,255);
  int G = random(0,255);
  int B = random(0,255);
  Serial.print("R: "); Serial.print(R);
  Serial.print(" G: "); Serial.print(G);
  Serial.print(" B: "); Serial.println(B);
  delay(500);
}
