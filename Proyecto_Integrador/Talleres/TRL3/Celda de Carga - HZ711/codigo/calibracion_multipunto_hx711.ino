#include <Arduino.h>
#include <math.h>
#include <stdlib.h>
#include "HX711.h"

// LIGURA | TRL 3 | Calibracion multipunto ESP32 + HX711
// Firmware del procedimiento experimental del 05/11/2026.
// Las lecturas ADC se registran relativas a la tara.

#define HX_DOUT 32
#define HX_SCK  33

HX711 celda;
const int NUM_MUESTRAS = 30;
const int MAX_PUNTOS = 20;

float masas[MAX_PUNTOS];
float lecturas[MAX_PUNTOS];
int numPuntos = 0;
float pendiente = 0;
float intercepto = 0;
float r2 = 0;
bool calibrado = false;
bool disponible = false;

void registrarPunto(float masa) {
  if (numPuntos >= MAX_PUNTOS) {
    Serial.println("ERROR: limite de puntos alcanzado.");
    return;
  }
  if (!celda.wait_ready_timeout(3000)) {
    Serial.println("ERROR: HX711 no disponible.");
    return;
  }
  Serial.println("----------------------------");
  Serial.print("Masa de referencia: ");
  Serial.print(masa, 2);
  Serial.println(" g");
  Serial.print("Tomando ");
  Serial.print(NUM_MUESTRAS);
  Serial.println(" muestras...");
  // La biblioteca de bogde devuelve el promedio del valor corregido por la tara.
  // get_value(n) redondea el promedio a un entero (long).
  float lectura = celda.get_value(NUM_MUESTRAS);
  masas[numPuntos] = masa;
  lecturas[numPuntos] = lectura;
  numPuntos++;
  calibrado = false;
  Serial.print("Lectura ADC promedio: ");
  Serial.println(lectura, 3);
  Serial.print("Punto registrado: ");
  Serial.println(numPuntos);
  Serial.println("----------------------------");
}

void calcularCalibracion() {
  if (numPuntos < 3) {
    Serial.println("Se requieren al menos 3 puntos.");
    return;
  }
  double sx = 0, sy = 0, sxx = 0, sxy = 0;
  for (int i = 0; i < numPuntos; i++) {
    double x = masas[i], y = lecturas[i];
    sx += x;
    sy += y;
    sxx += x*x;
    sxy += x*y;
  }
  double denominador = numPuntos*sxx - sx*sx;
  if (fabs(denominador) < 1e-9) {
    Serial.println("ERROR: masas insuficientemente distintas.");
    return;
  }
  pendiente = (numPuntos*sxy - sx*sy) / denominador;
  intercepto = (sy - pendiente*sx) / numPuntos;
  if (fabs(pendiente) < 1e-6) {
    Serial.println("ERROR: pendiente invalida.");
    return;
  }
  double promedioY = sy / numPuntos;
  double ssTotal = 0, ssError = 0;
  Serial.println("==================================");
  Serial.println("RESULTADOS DE CALIBRACION");
  Serial.println("==================================");
  for (int i = 0; i < numPuntos; i++) {
    double estimada = (lecturas[i] - intercepto) / pendiente;
    double error = estimada - masas[i];
    double yEstimada = intercepto + pendiente*masas[i];
    ssTotal += pow(lecturas[i]-promedioY,2);
    ssError += pow(lecturas[i]-yEstimada,2);
    Serial.print("Real: "); Serial.print(masas[i],2);
    Serial.print(" g | Estimada: "); Serial.print(estimada,3);
    Serial.print(" g | Error: "); Serial.print(error,3);
    Serial.println(" g");
  }
  r2 = ssTotal > 0 ? 1.0 - ssError/ssTotal : 0;
  calibrado = true;
  Serial.print("Pendiente (ADC/g): "); Serial.println(pendiente,6);
  Serial.print("Intercepto (ADC): "); Serial.println(intercepto,6);
  Serial.print("R2: "); Serial.println(r2,6);
  Serial.println("Ecuacion: masa=(ADC-intercepto)/pendiente");
  Serial.println("CALIBRACION FINALIZADA");
}

void verificarMedicion() {
  if (!calibrado) {
    Serial.println("Primero ejecuta CAL.");
    return;
  }
  if (!celda.wait_ready_timeout(3000)) {
    Serial.println("HX711 no responde.");
    return;
  }
  float adc = celda.get_value(NUM_MUESTRAS);
  float masa = (adc - intercepto) / pendiente;
  Serial.println("=== VERIFICACION ===");
  Serial.print("ADC: "); Serial.println(adc,3);
  Serial.print("Masa: "); Serial.print(masa,3); Serial.println(" g");
  Serial.print("Fuerza equivalente: ");
  Serial.print(masa*0.00980665f,5);
  Serial.println(" N");
}

void listarPuntos() {
  Serial.println("=== PUNTOS REGISTRADOS ===");
  for (int i = 0; i < numPuntos; i++) {
    Serial.print(i+1); Serial.print(" | ");
    Serial.print(masas[i],2); Serial.print(" g | ADC: ");
    Serial.println(lecturas[i],3);
  }
}

void reiniciar() {
  if (!celda.wait_ready_timeout(3000)) {
    Serial.println("HX711 no responde.");
    return;
  }
  Serial.println("Retira todas las pesas.");
  Serial.println("Realizando tara...");
  delay(2000);
  celda.set_scale(1.0f);
  celda.tare(NUM_MUESTRAS);
  numPuntos = 0;
  calibrado = false;
  registrarPunto(0);
  Serial.println("Tara completada.");
}

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(1000);
  delay(1000);
  celda.begin(HX_DOUT,HX_SCK);
  Serial.println("LIGURA - CALIBRACION MULTIPUNTO");
  Serial.println("Celda de carga: 1 kg");
  disponible = celda.wait_ready_timeout(5000);
  if (!disponible) {
    Serial.println("ERROR: HX711 no detectado; reinicia tras revisar cableado.");
    return;
  }
  reiniciar();
  Serial.println("COMANDOS: masa en gramos; CAL; VER; LIST; RESET");
  Serial.println("Ejemplo: coloca 5 g, envia 5, espera el promedio.");
}

void loop() {
  if (!disponible || !Serial.available()) return;
  String comando = Serial.readStringUntil('\n');
  comando.trim();
  comando.toUpperCase();
  if (comando == "CAL") calcularCalibracion();
  else if (comando == "VER") verificarMedicion();
  else if (comando == "LIST") listarPuntos();
  else if (comando == "RESET") reiniciar();
  else {
    char *fin = nullptr;
    float masa = strtof(comando.c_str(), &fin);
    if (fin != comando.c_str() && *fin == '\0' && isfinite(masa)
        && masa > 0 && masa <= 1000) registrarPunto(masa);
    else Serial.println("Comando no valido.");
  }
}
