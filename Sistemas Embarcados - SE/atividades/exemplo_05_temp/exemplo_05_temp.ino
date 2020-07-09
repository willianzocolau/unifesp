const int LM35 = 0; // label que define o pino ADC usado.
float temperatura = 0; // inicializa a variável usada para armazenar o valor de temperatura
int ADClido = 0; // inicializa a variável usada para armazenar o valor convertido pelo ADC
const int Buzzer = 12;

void setup() {
  Serial.begin(9600);
  analogReference(INTERNAL1V1); // Se estiver usando Arduino Mega, use INTERNAL
  pinMode(Buzzer, OUTPUT);

}
void loop() {
  ADClido = analogRead(LM35); // converte e armaneza valores entre 0 e 1023.
  temperatura = ADClido * 0.1075268817; // define o valor de temperatura para o valor convertido
  Serial.print("Temperatura = ");
  Serial.print(temperatura);
  Serial.println(" *C");
  if (temperatura > 25) { // setei como 25ºC
    digitalWrite(Buzzer, HIGH);
  }
  else {
    digitalWrite(Buzzer, LOW);
  }
  delay(1000);
}
