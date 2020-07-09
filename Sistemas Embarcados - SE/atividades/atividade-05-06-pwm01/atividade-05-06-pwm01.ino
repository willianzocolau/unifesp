int controle = 0;
const int LED[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
int SLED[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int PWMLED[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
float TENSAOMEDIA[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
float voltage, porcentagem;
int inverte = 0;
int index = 0;
float media = 0;
float z;

const int PinoPotenciometro = A2; // Define como uma constante inteira
const int Led1 = 13; // Define como uma constante inteira
int ValorPot = 0;
int pwm = 0;

void setup() {
  Serial.begin(9600);
  for (int x = 0; x < 10; x++) {
    pinMode(LED[x], OUTPUT);
  }
  pinMode(Led1, OUTPUT);
}

void loop() {
   if (inverte == 0)
  {
    aumenta(LED[0]);
    aumenta(LED[1]);
    aumenta(LED[2]);
    aumenta(LED[3]);
    aumenta(LED[4]);
    aumenta(LED[5]);
    aumenta(LED[6]);
    aumenta(LED[7]);
    aumenta(LED[8]);
    aumenta(LED[9]);
    inverte = 1;
  }
  else
  {
    diminui(LED[9]);
    diminui(LED[8]);
    diminui(LED[7]);
    diminui(LED[6]);
    diminui(LED[5]);
    diminui(LED[4]);
    diminui(LED[3]);
    diminui(LED[2]);
    diminui(LED[1]);
    diminui(LED[0]);
    inverte = 0;
  }
}

void aumenta(int led)
{
  for (int x = 1; x <= 255; x++)
  {
    analogWrite(led, x);
    tensao();
    delay(4);
  }
}


void diminui(int led)
{
  for (int x = 255; x >= 0; x--)
  {
    analogWrite(led, x);
    tensao();
    delay(4);
  }
}


unsigned long interval1 = 2000;
unsigned long previousMillis1 = 0;

int tempo()
{
  unsigned long currentMillis1 = millis();
  if ((unsigned long)((currentMillis1 - previousMillis1) >= interval1)) {
    previousMillis1 = millis();
    return 1;
  }
  else
  {
    return 0;
  }
}

void tensao()
{
  ValorPot = analogRead(PinoPotenciometro);
  pwm = map(ValorPot, 0, 1023, 0, 255);
  analogWrite(Led1, pwm); 
  float x = ValorPot / 4.0117;
  float z = x / 255;
  float t = 5 * z;
  TENSAOMEDIA[index] = t;
  index++;
  float soma = 0;
  for (int x = 0; x < 10; x++)
  {
    soma = soma + TENSAOMEDIA[x];
  }
  media = soma / 10;
  if (index == 10)
  {
    index  = 0;
  }

  if (tempo())
  {
    Serial.print("Potenciometro: ");
    Serial.print(ValorPot);
    Serial.print(" | Duty Cicle: ");
    Serial.print(x);
    Serial.print(" | Tensão média: ");
    Serial.print(media);
    Serial.print(" | Porcentagem: ");
    Serial.println(z * 100);
  }
}
