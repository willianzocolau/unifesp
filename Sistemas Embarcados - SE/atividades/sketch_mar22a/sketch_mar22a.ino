const int LM35 = 0;
const int Buzzer = 12;
const int btn = 2;
const int ledPin1 = 8;
const int ledPin2 = 9;
const int ledPin3 = 10;
const int ledPin4 = 11;

float temperatura = 0;
int ADClido = 0;
int state = 0;
int counter = 0;
int counter_reset = -1;
int bin[5];
long start = 0;  

void intToBin(int dec, int bin[], int numBits){
  for(int i = 0; i < numBits; i++){
    bin[i] = 1 & (dec >> i);
  }
}

void setup() {
  Serial.begin(9600);
  analogReference(INTERNAL);
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
  Serial.print("Counter: ");
  Serial.println(counter);
  intToBin(counter, bin, 5);
  if (counter > 15 && counter_reset == -1) {//Sinaliza que precisa entrar no reset( 
    counter = 0;
    counter_reset = 0;
  }
  else if (state == 1 && counter_reset == -1) {//Incrementa        
    delay(200);  
    counter++;
  }
  else if (counter_reset > -1 && counter_reset <= 5) {//Piscar os leds a cada 0,5s
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);        
    digitalWrite(ledPin4, LOW);
    delay(500);
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, HIGH);        
    digitalWrite(ledPin4, HIGH);
    counter_reset++;
  }
  else if(counter_reset > 5)//Reseta tudo
  {
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);        
    digitalWrite(ledPin4, LOW);
    counter = 0;
    counter_reset = -1;
  }

  //Acender leds
  if(bin[0] == 1) {//Maior
    digitalWrite(ledPin1, HIGH);
  }
  else {
    digitalWrite(ledPin1, LOW);
  }
  if(bin[1] == 1) {
    digitalWrite(ledPin2, HIGH);
  }
  else {
    digitalWrite(ledPin2, LOW);
  }

  if(bin[2] == 1) {
    digitalWrite(ledPin3, HIGH);
  }
  else {
    digitalWrite(ledPin3, LOW);
  }

  if(bin[3] == 1) {
    digitalWrite(ledPin4, HIGH);
  }
  else {
    digitalWrite(ledPin4, LOW);
  }

  unsigned long current = millis();
  int resto = current % 500;//Mudar
  if(resto >= 480)//Mudar
  {
    if (temperatura > 25) {
      digitalWrite(Buzzer, HIGH);
      delay(100);//Mudar
      digitalWrite(Buzzer, LOW);
    }    
  } 
}



