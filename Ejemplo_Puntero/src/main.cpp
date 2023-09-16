#include <Arduino.h>

int Numero = 10 ;
void Duplicar(int *punteroNumero);

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.print("En loop(): Numero = ");
  Serial.println(Numero);
  Duplicar(&Numero);
  delay(1000);
}

void Duplicar(int *punteroNumero) {
  *punteroNumero = *punteroNumero * 2 ;
  Serial.print("En duplicar(): PunteroNumero = ");
  Serial.println(*punteroNumero);
}