#include <Arduino.h>
#include <math.h>

// ========================================
// LIGURA - PRUEBA ACUSTICA COMPARATIVA
// ESP32 + AD9833 + PIEZO RECEPTOR
// ========================================

// AD9833
const int PIN_SDATA = 13;
const int PIN_SCLK  = 14;
const int PIN_FSYNC = 26;

// Receptor
const int PIN_ADC = 34;

// Frecuencias
const double MCLK = 25000000.0;
const double F_EMISION = 2000.0;

// Muestreo nominal a 8000 Hz
const int N = 256;
const uint32_t PERIODO_US = 125;

uint16_t muestras[N];

bool emisorEncendido = false;

// ========================================
// CONTROL AD9833
// ========================================

void escribirAD9833(uint16_t dato) {
  digitalWrite(PIN_FSYNC, LOW);

  for (int i = 15; i >= 0; i--) {
    digitalWrite(PIN_SCLK, HIGH);
    digitalWrite(PIN_SDATA, (dato >> i) & 1);
    delayMicroseconds(2);
    digitalWrite(PIN_SCLK, LOW);
    delayMicroseconds(2);
  }

  digitalWrite(PIN_FSYNC, HIGH);
  digitalWrite(PIN_SCLK, HIGH);
}

void configurarAD9833(double frecuencia) {
  uint32_t registro = (uint32_t)(
    frecuencia * 268435456.0 / MCLK + 0.5
  );

  // Configurar mientras esta en RESET
  escribirAD9833(0x2100);

  escribirAD9833(
    0x4000 | (registro & 0x3FFF)
  );

  escribirAD9833(
    0x4000 | ((registro >> 14) & 0x3FFF)
  );

  escribirAD9833(0xC000);

  // Mantener salida desactivada inicialmente
  escribirAD9833(0x2100);
}

void controlarEmisor(bool encender) {
  emisorEncendido = encender;

  if (encender) {
    escribirAD9833(0x2000);
  } else {
    // RESET activado: salida sinusoidal detenida
    escribirAD9833(0x2100);
  }
}

// ========================================
// ADQUISICION
// ========================================

float adquirirMuestras() {
  uint32_t inicio = micros();

  for (int i = 0; i < N; i++) {
    uint32_t objetivo =
      inicio + i * PERIODO_US;

    while ((int32_t)(micros() - objetivo) < 0) {
    }

    muestras[i] = analogRead(PIN_ADC);
  }

  uint32_t duracion = micros() - inicio;

  return (N - 1) * 1000000.0f / duracion;
}

// ========================================
// GOERTZEL
// ========================================

float goertzel(float frecuencia, float fs) {
  float omega = 2.0f * PI * frecuencia / fs;
  float coef = 2.0f * cosf(omega);

  float promedio = 0;

  for (int i = 0; i < N; i++) {
    promedio += muestras[i];
  }

  promedio /= N;

  float s0 = 0;
  float s1 = 0;
  float s2 = 0;

  for (int i = 0; i < N; i++) {
    float ventana = 0.5f * (
      1.0f - cosf(2.0f * PI * i / (N - 1))
    );

    float x = (muestras[i] - promedio) * ventana;

    s0 = x + coef * s1 - s2;
    s2 = s1;
    s1 = s0;
  }

  float potencia =
    s1 * s1 + s2 * s2 - coef * s1 * s2;

  return 4.0f * sqrtf(fmaxf(potencia, 0.0f))
         / (N - 1);
}

// ========================================
// PROGRAMA PRINCIPAL
// ========================================

void setup() {
  Serial.begin(115200);

  pinMode(PIN_SDATA, OUTPUT);
  pinMode(PIN_SCLK, OUTPUT);
  pinMode(PIN_FSYNC, OUTPUT);

  digitalWrite(PIN_SDATA, LOW);
  digitalWrite(PIN_SCLK, HIGH);
  digitalWrite(PIN_FSYNC, HIGH);

  analogReadResolution(12);
  analogSetPinAttenuation(PIN_ADC, ADC_11db);

  delay(500);

  configurarAD9833(F_EMISION);
  controlarEmisor(false);

  Serial.println();
  Serial.println("================================");
  Serial.println("LIGURA - PRUEBA ACUSTICA");
  Serial.println("================================");
  Serial.println("Frecuencia objetivo: 2000 Hz");
  Serial.println("Comandos:");
  Serial.println("  1 = Encender emisor");
  Serial.println("  0 = Apagar emisor");
  Serial.println();
}

void loop() {

  // Comandos del Monitor Serie
  while (Serial.available()) {
    char comando = Serial.read();

    if (comando == '1') {
      controlarEmisor(true);
    }

    if (comando == '0') {
      controlarEmisor(false);
    }
  }

  float fs = adquirirMuestras();

  int minimo = 4095;
  int maximo = 0;

  for (int i = 0; i < N; i++) {
    if (muestras[i] < minimo) minimo = muestras[i];
    if (muestras[i] > maximo) maximo = muestras[i];
  }

  float nivel2000 = goertzel(2000.0f, fs);
  float nivel1500 = goertzel(1500.0f, fs);
  float nivel2500 = goertzel(2500.0f, fs);
  float nivel60 = goertzel(60.0f, fs);

  Serial.println("------------------------------");

  Serial.print("Emisor: ");
  Serial.println(
    emisorEncendido ? "ENCENDIDO" : "APAGADO"
  );

  Serial.print("Muestreo aprox.: ");
  Serial.print(fs, 1);
  Serial.println(" Hz");

  Serial.print("ADC pico-pico: ");
  Serial.println(maximo - minimo);

  Serial.print("Nivel 2000 Hz: ");
  Serial.println(nivel2000, 2);

  Serial.print("Nivel 1500 Hz: ");
  Serial.println(nivel1500, 2);

  Serial.print("Nivel 2500 Hz: ");
  Serial.println(nivel2500, 2);

  Serial.print("Nivel 60 Hz: ");
  Serial.println(nivel60, 2);

  delay(500);
}
