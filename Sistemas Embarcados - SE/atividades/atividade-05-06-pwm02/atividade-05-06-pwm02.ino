int controle = 0;
const int btn1 = 12;
const int btn2 = 13;
const int LED[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
int SLED[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int PWMLED[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
float voltage;
int inverte = 0;
float t = 0;
int c = 0;

const int PinoPotenciometro = A2; // Define como uma constante inteira
int ValorPot = 0;
int pwm = 0;

void setup() {
  Serial.begin(9600);
  for (int x = 0; x < 10; x++) {
    pinMode(LED[x], OUTPUT);
  }
  pinMode(btn1, OUTPUT);
  pinMode(btn2, OUTPUT);
}

void loop() {
  c = controle;
  if (controle == 0)
  {
    //Ida
    aumenta(LED[0], LED[9]);
    diminui(LED[0], LED[9]);
    aumenta(LED[1], LED[8]);
    diminui(LED[1], LED[8]);
    aumenta(LED[2], LED[7]);
    diminui(LED[2], LED[7]);
    aumenta(LED[3], LED[6]);
    diminui(LED[3], LED[6]);
    aumenta(LED[4], LED[5]);
    diminui(LED[4], LED[5]);
    //Volta
    aumenta(LED[3], LED[6]);
    diminui(LED[3], LED[6]);
    aumenta(LED[2], LED[7]);
    diminui(LED[2], LED[7]);
    aumenta(LED[1], LED[8]);
    diminui(LED[1], LED[8]);
    aumenta(LED[0], LED[9]);
    diminui(LED[0], LED[9]);
  }
  else
  {
    //Ida
    aumenta(LED[0], LED[0]);
    diminui(LED[0], LED[0]);
    aumenta(LED[0], LED[2]);
    diminui(LED[0], LED[2]);
    aumenta(LED[2], LED[4]);
    diminui(LED[2], LED[4]);
    aumenta(LED[4], LED[6]);
    diminui(LED[4], LED[6]);
    aumenta(LED[6], LED[8]);
    diminui(LED[6], LED[8]);
    aumenta(LED[8], LED[8]);
    diminui(LED[8], LED[8]);
    //Volta
    aumenta(LED[6], LED[8]);
    diminui(LED[6], LED[8]);
    aumenta(LED[4], LED[6]);
    diminui(LED[4], LED[6]);
    aumenta(LED[2], LED[4]);
    diminui(LED[2], LED[4]);
    aumenta(LED[0], LED[2]);
    diminui(LED[0], LED[2]);
  }
}

void apagar()
{
  for (int x = 0; x < 10; x++) {
    analogWrite(LED[x], 0);
  }
}
void aumenta(int led, int led2)
{
  if (c == controle) {
    for (int x = 1; x <= 255; x++)
    {
      analogWrite(led, x);
      analogWrite(led2, x);
      processar();
      delay((t*1000)/255);
    }
  }
  else
  {
    apagar();
  }
}


void diminui(int led, int led2)
{

  if (c == controle) {
    for (int x = 255; x >= 0; x--)
    {
      analogWrite(led, x);
      analogWrite(led2, x);
      processar();
      delay((t*1000)/255);
    }
  }
  else
  {
    apagar();
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

void processar()
{
  ValorPot = analogRead(PinoPotenciometro);
  int a = digitalRead(btn1);
  int b = digitalRead(btn2);
  float x = ValorPot / 4.0117;
  float z = x / 255;
  t = 5 * z;
  if (a == 1)
  {
    controle = 0;
  }

  if (b == 1)
  {
    controle = 1;
  }


  t = (t / 2.5);
  if(t < 0.5)
  {
    t = t/5 + 0.5;
  }
  if (tempo())
  {
    Serial.print("Potenciometro: ");
    Serial.print(ValorPot);
    Serial.print(" | T: ");
    Serial.println(t);
  }
}
