#include <StackArray.h>

StackArray <int> stack;
const int ledPin1 = 13;
const int ledPin2 = 12;
const int ledPin3 = 11;
const int Botao4 = 4;
const int Botao3 = 3;
const int Botao2 = 2;
const int Buzzer = 10; //O buzzer está colocado no pino 10
int EstadoBotao2 = 0;
int EstadoBotao3 = 0;
int EstadoBotao4 = 0;
int Tom = 0; //Variavel para armazenar a nota musical
int acerto_miseravi = 0;
int counter = 0;
int reset = 1;
void setup() {
  pinMode(Buzzer, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(Botao2, INPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(Botao3, INPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(Botao4, INPUT);
  Serial.begin(9600);
}
void loop() {
  EstadoBotao2 = digitalRead(Botao2);
  EstadoBotao3 = digitalRead(Botao3);
  EstadoBotao4 = digitalRead(Botao4);
  delay(250);
  if (EstadoBotao2 == 1) {
    int v = stack.pop();
    Serial.println(v);
    if (v != 1) {
      acerto_miseravi = 0;
    }
  }
  else if (EstadoBotao3 == 1) {
    int v = stack.pop();
    Serial.println(v);
    if (v != 2) {
      acerto_miseravi = 0;
    }
  }
  else if (EstadoBotao4 == 1) {
    int v = stack.pop();
    Serial.println(v);
    if (v != 3) {
      acerto_miseravi = 0;
    }
  }

  if (stack.isEmpty())
  {
    if (acerto_miseravi == 1) //Acertou
    {
      digitalWrite(Buzzer, HIGH);
      delayMicroseconds(200);
      delay(1000);
      digitalWrite(Buzzer, LOW);
      digitalWrite(ledPin1, HIGH);
      digitalWrite(ledPin2, HIGH);
      digitalWrite(ledPin3, HIGH);
      delay(1000);
      digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin2, LOW);
      digitalWrite(ledPin3, LOW);
      delay(1000);
      digitalWrite(ledPin1, HIGH);
      digitalWrite(ledPin2, HIGH);
      digitalWrite(ledPin3, HIGH);
      delay(1000);
      digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin2, LOW);
      digitalWrite(ledPin3, LOW);
      delay(1000);
      digitalWrite(ledPin1, HIGH);
      digitalWrite(ledPin2, HIGH);
      digitalWrite(ledPin3, HIGH);
      delay(1000);
      digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin2, LOW);
      digitalWrite(ledPin3, LOW);
      reset = 1;
    }
    else if (reset == 0){//Erroou!!!
      digitalWrite(ledPin1, HIGH);
      delay(1000);
      digitalWrite(ledPin1, LOW);
      delay(1000);
      digitalWrite(ledPin1, HIGH);
      delay(1000);
      digitalWrite(ledPin1, LOW);
      reset = 1;
    }

    if (reset == 1)
    {
      stack.push(1);
      stack.push(2);
      stack.push(3);

      acerto_miseravi = 1;
      reset = 0;
    }
  }
}

