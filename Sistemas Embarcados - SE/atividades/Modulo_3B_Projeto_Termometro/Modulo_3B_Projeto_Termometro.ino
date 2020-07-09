const int PinoPotenciometro = A1;
const int Led = 13;
int ValorPot = 0;
void setup() {  // Note que a função analogReference(INTERNAL1V1) não está sendo usada, assim o conversor ADC irá utiliza a referência padrão de 5V.
  Serial.begin(9600);
}
void loop() {
  ValorPot = analogRead(PinoPotenciometro);
  Serial.println(ValorPot);
}
