#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP32Servo.h>

// Inicializar LCD I2C
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Inicializar Servomotores (Pestillos de las tapas)
Servo servo_A, servo_B, servo_C, servo_D;

// Pines de entrada
const int POT_SELECTOR = 34;      // Potenciómetro para elegir casillero
const int BTN_CONFIRMAR = 23;     // Único botón para abrir la tapa

// Pines de servomotores
const int SERVO_A_PIN = 13;
const int SERVO_B_PIN = 14;
const int SERVO_C_PIN = 15;
const int SERVO_D_PIN = 16;

// Pines de LEDs y Buzzer
const int LED_VERDE = 2;
const int LED_ROJO = 4;
const int LED_AZUL = 5;
const int BUZZER = 12;

// Variables globales
int medicamento_actual = -1; // Inicia en -1 para forzar la actualización de pantalla en el primer ciclo
String medicamentos[4] = {"Acetaminofen", "Dolex Gripa", "Ibuprofeno", "Otro"};

// Declaración de funciones
bool botonPresionado(int pin);
void abrirCompartimento(int indice);
void actualizarPantalla(int indice);

void setup() {
  Serial.begin(115200);
  Serial.println("Iniciando Destapador Inteligente...");
  
  Wire.begin(21, 22);  // SDA=21, SCL=22
  lcd.init();
  lcd.backlight();
  lcd.print("   DESTAPADOR   ");
  lcd.setCursor(0, 1);
  lcd.print("  INTELIGENTE   ");
  delay(2000); 
  
  // Configurar el único botón con resistencia Pull-Up interna
  pinMode(BTN_CONFIRMAR, INPUT_PULLUP);
  
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_ROJO, OUTPUT);
  pinMode(LED_AZUL, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_ROJO, LOW);
  digitalWrite(BUZZER, LOW);
  
  // El LED Azul encendido indica que el sistema está en espera (Standby)
  digitalWrite(LED_AZUL, HIGH); 
  
  // Configurar servos
  servo_A.attach(SERVO_A_PIN);
  servo_B.attach(SERVO_B_PIN);
  servo_C.attach(SERVO_C_PIN);
  servo_D.attach(SERVO_D_PIN);
  
  // Posición 0 grados = Pestillos cerrados (Tapas bloqueadas)
  servo_A.write(0);
  servo_B.write(0);
  servo_C.write(0);
  servo_D.write(0);
}

void loop() {
  // 1. Leer potenciómetro (valores de 0 a 4095)
  int valor_pot = analogRead(POT_SELECTOR);
  
  // 2. Convertir el valor a 4 opciones exactas (0, 1, 2 o 3)
  // Dividimos 4096 / 4 = 1024 (Cada bloque de 1024 cambia el casillero)
  int seleccion = valor_pot / 1024; 
  if (seleccion > 3) seleccion = 3; // Límite de seguridad
  
  // 3. Actualizar la pantalla solo si el usuario movió el potenciómetro
  if (seleccion != medicamento_actual) {
    medicamento_actual = seleccion;
    actualizarPantalla(medicamento_actual);
  }

  // 4. Si presiona el botón, se abre la tapa seleccionada
  if (botonPresionado(BTN_CONFIRMAR)) {
    abrirCompartimento(medicamento_actual);
    // Tras cerrar la tapa, devolvemos la pantalla a la selección actual
    actualizarPantalla(medicamento_actual);
  }
}

// ---- FUNCIÓN DE ANTIRREBOTE PARA EL BOTÓN ----
bool botonPresionado(int pin) {
  if (digitalRead(pin) == LOW) {     
    delay(50);                       
    if (digitalRead(pin) == LOW) {   
      while (digitalRead(pin) == LOW) { 
        delay(10);                   
      }
      delay(50);                     
      return true;                   
    }
  }
  return false;
}

// ---- ACTUALIZAR LCD ----
void actualizarPantalla(int indice) {
  lcd.clear();
  lcd.print("Elegir medicina:");
  lcd.setCursor(0, 1);
  lcd.print("> ");
  lcd.print(medicamentos[indice]);
  
  Serial.print("Casillero seleccionado: ");
  Serial.println(medicamentos[indice]);
}

// ---- ABRIR COMPARTIMENTO (DESTAPADOR) ----
void abrirCompartimento(int indice) {
  // Indicadores visuales y sonoros
  digitalWrite(LED_AZUL, LOW);
  digitalWrite(LED_VERDE, HIGH);
  
  digitalWrite(BUZZER, HIGH);
  delay(150); // Pitido corto
  digitalWrite(BUZZER, LOW);
  
  // Seleccionar cuál servo debe moverse
  Servo* servo_seleccionado;
  if (indice == 0) servo_seleccionado = &servo_A;
  else if (indice == 1) servo_seleccionado = &servo_B;
  else if (indice == 2) servo_seleccionado = &servo_C;
  else servo_seleccionado = &servo_D;
  
  // Mensaje de apertura
  lcd.clear();
  lcd.print("Abriendo tapa...");
  lcd.setCursor(0, 1);
  lcd.print(medicamentos[indice]);
  
  Serial.println("\n*** ACCION DEL SISTEMA ***");
  Serial.print("Abriendo casillero de: ");
  Serial.println(medicamentos[indice]);
  
  // Mueve el servo a 90 grados para liberar el pestillo
  servo_seleccionado->write(90);
  
  // Espera 5 segundos para que el usuario retire la pastilla
  delay(5000); 
  
  // Regresa el servo a 0 grados para volver a bloquear
  servo_seleccionado->write(0);
  
  // Mensaje de cierre
  lcd.clear();
  lcd.print("Tapa cerrada.");
  Serial.println("Casillero cerrado.\n");
  delay(2000); 
  
  // Restaurar estado de espera
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AZUL, HIGH);
}