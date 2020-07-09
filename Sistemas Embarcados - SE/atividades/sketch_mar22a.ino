const int LM35 = 0;
const int Buzzer = 12;
const int btn = 2;
const int ledPin1 = 8;
const int ledPin2 = 9;
const int ledPin3 = 10;
const int ledPin3 = 11;

float temperatura = 0;
int ADClido = 0;
int state = 0;
int counter = 0;
int counter_reset = -1;

void setup() {
  Serial.begin(9600);
  analogReference(INTERNAL1V1);
  pinMode(Buzzer, OUTPUT);
  pinMode(btn, INPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
}
void loop() {
  ADClido = analogRead(LM35);
  temperatura = ADClido * 0.1075268817;
  state = digitalRead(btn);
  if(counter_reset == -1) {//Tirar delay 5 segundos
    delay(200);  
  }
  if (counter > 15 && counter_reset == -1) {//Reseta apenas se não tiver nos 5 segundos
    counter = 0;
    counter_reset = 0;
  }
  else if (state == 1 && reset == 0) {
    counter++;
  }
  else if (counter_reset > -1 && counter_reset <= 5) {
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, HIGH);
    delay(1000);
    counter_reset
  }
  Serial.println(" *C");
  if (temperatura > 25) {
    digitalWrite(Buzzer, HIGH);

  }
  else {
    digitalWrite(Buzzer, LOW);
  }
}
