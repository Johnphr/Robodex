// ----- Motores -----
#define ENA 5
#define IN1 6
#define IN2 7
#define ENB 9
#define IN3 10
#define IN4 11

// ----- IR Sensors -----
#define IR_LEFT   2
#define IR_CENTER 3
#define IR_RIGHT  4

// ----- Sensor de color (ejemplo TCS34725) -----
#include <Adafruit_TCS34725.h>
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

// ----- Variables de control -----
int baseSpeed = 120;
bool invertedMode = false; // false = negro sobre blanco, true = blanco sobre negro
bool bonusMode = true;     // activa camino alterno en bifurcación

// PID constants
float Kp = 40;   // proporcional
float Ki = 0;    // integral (puede quedar en 0)
float Kd = 25;   // derivativo

float error = 0, lastError = 0, integral = 0;

// ----- Funciones de motores -----
void setMotor(int leftSpeed, int rightSpeed) {
  // Asegurar límites
  leftSpeed = constrain(leftSpeed, -255, 255);
  rightSpeed = constrain(rightSpeed, -255, 255);

  // Motor A
  if (leftSpeed >= 0) {
    digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
    analogWrite(ENA, leftSpeed);
  } else {
    digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
    analogWrite(ENA, -leftSpeed);
  }

  // Motor B
  if (rightSpeed >= 0) {
    digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
    analogWrite(ENB, rightSpeed);
  } else {
    digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
    analogWrite(ENB, -rightSpeed);
  }
}

// ----- Color detection -----
String detectColor() {
  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);

  if (r > 300 && g > 300 && b < 150) return "YELLOW"; // bifurcación
  if (r < 200 && g < 200 && b < 200) return "BLACK";
  if (r > 600 && g > 600 && b > 600) return "WHITE";
  return "OTHER";
}

// ----- Setup -----
void setup() {
  pinMode(ENA, OUTPUT); pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT); pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);

  pinMode(IR_LEFT, INPUT);
  pinMode(IR_CENTER, INPUT);
  pinMode(IR_RIGHT, INPUT);

  Serial.begin(9600);
  if (tcs.begin()) Serial.println("Color sensor listo");
  else { Serial.println("ERROR: no se detecta sensor de color"); while (1); }
}

// ----- Loop -----
void loop() {
  // Leer sensores IR
  int left = digitalRead(IR_LEFT);
  int center = digitalRead(IR_CENTER);
  int right = digitalRead(IR_RIGHT);

  // Ajustar a modo normal/invertido
  if (invertedMode) {
    left = !left;
    center = !center;
    right = !right;
  }

  // Determinar error (posición relativa de la línea)
  if (left == 0 && center == 1 && right == 0) error = 0;     // centro
  else if (left == 1 && center == 1 && right == 0) error = -0.5; // ligeramente izquierda
  else if (left == 1 && center == 0 && right == 0) error = -1;   // izquierda fuerte
  else if (left == 0 && center == 1 && right == 1) error = 0.5;  // ligeramente derecha
  else if (left == 0 && center == 0 && right == 1) error = 1;    // derecha fuerte
  else if (left == 1 && center == 1 && right == 1) error = 0;    // intersección
  else error = 0; // perdido → recto

  // PID
  integral += error;
  float derivative = error - lastError;
  float correction = Kp * error + Ki * integral + Kd * derivative;
  lastError = error;

  int leftSpeed = baseSpeed - correction;
  int rightSpeed = baseSpeed + correction;

  setMotor(leftSpeed, rightSpeed);

  // Checar color lateral
  String color = detectColor();
  if (color == "YELLOW") {
    Serial.println("Bifurcación detectada");

    if (bonusMode) {
      invertedMode = true; // cambia a blanco sobre negro
      Serial.println("Activando modo bonus: línea blanca");
    } else {
      invertedMode = false; // seguir normal
      Serial.println("Modo normal: línea negra");
    }

    delay(300); // estabilizar
  }
}