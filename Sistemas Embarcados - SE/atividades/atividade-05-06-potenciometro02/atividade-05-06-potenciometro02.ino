const int PinoPotenciometro = A2;
int ValorPot = 0;
int ADClido = 0;
int controle = 0;
const int LED[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
int SLED[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
float voltage, porcentagem;

void setup() {
  analogReference(INTERNAL1V1);
  Serial.begin(9600);
  for (int x = 0; x < 10; x++) {
    pinMode(LED[x], OUTPUT);
  }
}

unsigned long interval1 = 700;
unsigned long previousMillis1 = 0;

int tempo1(int t)
{
  unsigned long currentMillis1 = millis();
  interval1 = 500 + t;
  if ((unsigned long)((currentMillis1 - previousMillis1) >= interval1)) {
    previousMillis1 = millis();
    return 1;
  }
  else
  {
    return 0;
  }
}


unsigned long interval2 = 4500;
unsigned long previousMillis2 = 0;

int tempo2()
{
  unsigned long currentMillis2 = millis();
  if ((unsigned long)(currentMillis2 - previousMillis2) >= interval2) {
    previousMillis2 = millis();
    return 1;
  }
  else
  {
    return 0;
  }
}

void loop() {
  ValorPot = analogRead(PinoPotenciometro);
  voltage = ValorPot * (5.0 / 1023.0);
  porcentagem = (100*voltage)/5;
  Serial.print("Valor Pot: ");
  Serial.print(ValorPot);
  Serial.print(" | Voltage ");
  Serial.print(voltage);
  Serial.print(" | Porcentagem: ");
  Serial.println(porcentagem);
  if (porcentagem >= 10.00) {
    digitalWrite(LED[0], HIGH);
    SLED[0] = 1;
  }
  else {
    digitalWrite(LED[0], LOW);
    SLED[0] = 0;
  }
  if (porcentagem >= 20.00) {
    digitalWrite(LED[1], HIGH);
    SLED[1] = 1;
  }
  else {
    digitalWrite(LED[1], LOW);
    SLED[1] = 0;
  }
  if (porcentagem >= 30.00) {
    digitalWrite(LED[2], HIGH);
    SLED[2] = 1;
  }
  else {
    digitalWrite(LED[2], LOW);
    SLED[2] = 0;
  }
  if (porcentagem >= 40.00) {
    digitalWrite(LED[3], HIGH);
    SLED[3] = 1;
  }
  else {
    digitalWrite(LED[3], LOW);
    SLED[3] = 0;
  }
  if (porcentagem >= 50.00) {
    digitalWrite(LED[4], HIGH);
    SLED[4] = 1;
  }
  else {
    digitalWrite(LED[4], LOW);
    SLED[4] = 0;
  }
  if (porcentagem >= 60.00) {
    digitalWrite(LED[5], HIGH);
    SLED[5] = 1;
  }
  else {
    digitalWrite(LED[5], LOW);
    SLED[5] = 0;
  }
  if (porcentagem >= 70.00) {
    digitalWrite(LED[6], HIGH);
    SLED[6] = 1;
  }
  else {
    digitalWrite(LED[6], LOW);
    SLED[6] = 0;
  }
  if (porcentagem >= 80.00) {
    digitalWrite(LED[7], HIGH);
    SLED[7] = 1;
  }
  else {
    digitalWrite(LED[7], LOW);
    SLED[7] = 0;
  }
  if (porcentagem >= 90.00) {
    digitalWrite(LED[8], HIGH);
    SLED[8] = 1;
  }
  else {
    digitalWrite(LED[8], LOW);
    SLED[8] = 0;
  }
  if (porcentagem >= 100.00) {
    digitalWrite(LED[9], HIGH);
    SLED[9] = 1;
  }
  else {
    digitalWrite(LED[9], LOW);
    SLED[9] = 0;
  }
}

