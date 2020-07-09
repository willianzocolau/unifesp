const int LM35 = 0;
const int btn1 = 2;
const int btn2 = 3;
const int btn3 = 4;
const int ledPin0 = 7;
const int ledPin1 = 8;
const int ledPin2 = 9;
const int ledPin3 = 10;
const int ledPin4 = 11;
const int ledPin5 = 12;
const int Buzzer = 5;

float temperatura = 0;
float min_temp = 3000;
float max_temp = -3000;
float avg_temp = 0;
float avg = 0;
int ADClido = 0;
int bin[7];
int bind[7];
float temps[30];
int count = 0;
int count_avg = 0;
int controle = 0;
int state1 = 0;
int state2 = 0;
int state3 = 0;

unsigned long interval = 1000;
unsigned long previousMillis = 0;

int tempo()
{
  unsigned long currentMillis = millis();
  if ((unsigned long)(currentMillis - previousMillis) >= interval) {
    previousMillis = millis();
    return 1;
  }
  else
  {
    return 0;
  }
}

void intToBin(int dec, int bin[], int numBits) {
  for (int i = 0; i < numBits; i++) {
    bin[i] = 1 & (dec >> i);
  }
}

void printArr(int bin[], int numBits) {
  for (int i = numBits - 1; i >= 0; i--) {
    Serial.print(bin[i]);
  }
}

void apagar()
{
  setLed(ledPin0, 0);
  setLed(ledPin1, 0);
  setLed(ledPin2, 0);
  setLed(ledPin3, 0);
  setLed(ledPin4, 0);
  setLed(ledPin5, 0);
}

void setLed(int pin, int v)
{
  if (v == -1)
  {
    if (digitalRead(pin) == HIGH)
    {
      digitalWrite(pin, LOW);
    }
    else {
      digitalWrite(pin, HIGH);
    }
  }
  else
  {
    digitalWrite(pin, LOW);
    if (v == 1)
    {
      digitalWrite(pin, HIGH);
    }
  }
}

void leds(int arr[], int mantem, int tempo)
{
  if (mantem == 1) //Inverte
  {
    if (arr[5] == 1) {
      setLed(ledPin0, -1);
    }
    if (arr[4] == 1) {
      setLed(ledPin1, -1);
    }
    if (arr[3] == 1) {
      setLed(ledPin2, -1);
    }
    if (arr[2] == 1) {
      setLed(ledPin3, -1);
    }
    if (arr[1] == 1) {
      setLed(ledPin4, -1);
    }
    if (arr[0] == 1) {
      setLed(ledPin5, -1);
    }
  }
  else
  {
    setLed(ledPin0, arr[5]);
    setLed(ledPin1, arr[4]);
    setLed(ledPin2, arr[3]);
    setLed(ledPin3, arr[2]);
    setLed(ledPin4, arr[1]);
    setLed(ledPin5, arr[0]);
  }
}

void calc(float temp)
{
  if (temp < min_temp)
  {
    min_temp = temp;
  }

  if (temp >  max_temp)
  {
    max_temp = temp;
  }

  if (tempo() == 1) //Deu 1s
  {
    temps[count_avg] = temp;
    float sum = 0;
    int c = 0;
    for (int i = 0; i < 30; i++) {
      sum = sum + temps[i];
      c++;
    }
    avg = sum / c;
    count_avg++;
  }
  
  if (count_avg >= 30)
  {
    count_avg = 0;
  }
}

void setup() {
  Serial.begin(9600);
  analogReference(INTERNAL);
  pinMode(btn1, INPUT);
  pinMode(btn2, INPUT);
  pinMode(btn3, INPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(ledPin0, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  pinMode(ledPin5, OUTPUT);
}

void loop() {
  ADClido = analogRead(LM35);
  state1 = digitalRead(btn1);
  state2 = digitalRead(btn2);
  state3 = digitalRead(btn3);
  delay(200);
  temperatura = ADClido * 0.1075268817;
  Serial.print("Temperatura ");
  Serial.print(temperatura);
  Serial.print(" C | ");
  intToBin(temperatura, bind, 6);
  printArr(bind, 6);
  calc(temperatura);
  if (temperatura > 200)
  {
    digitalWrite(Buzzer, HIGH);
    if (controle == 0)
    {
      intToBin(temperatura, bin, 6);
      count++;
      controle = 1;
      leds(bin, 0, 1000);
    }
    leds(bin, 1, 1000);
    delay(1000);
    digitalWrite(Buzzer, LOW);
  }
  else
  {
    digitalWrite(Buzzer, LOW);
    controle = 0;
    leds(bind, 0, 1000);
  }
  if (state1)
  {
    Serial.print(" | Mín Temp: ");
    Serial.print(min_temp);
  }
  else if (state2)
  {
    Serial.print(" | Avg Temp: ");
    Serial.print(avg);
  }
  else if (state3)
  {
    Serial.print(" | Max Temp: ");
    Serial.print(max_temp);
  }
  Serial.println("");
}
