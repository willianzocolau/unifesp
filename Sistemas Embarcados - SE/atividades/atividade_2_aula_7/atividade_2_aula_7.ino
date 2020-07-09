const int LM35 = 0;
const int ledPin0 = 7;
const int ledPin1 = 8;
const int ledPin2 = 9;
const int ledPin3 = 10;
const int ledPin4 = 11;
const int ledPin5 = 12;

float temperatura = 0;
int ADClido = 0;
int bin[7];
int bind[7];
int count = 0;
int controle = 0;

void intToBin(int dec, int bin[], int numBits){
  for(int i = 0; i < numBits; i++){
    bin[i] = 1 & (dec >> i);
  }
}

void printArr(int bin[], int numBits){
  for(int i = numBits-1; i >= 0; i--){
    Serial.print(bin[i]);
  }
}

int controlTime(long t, long interval)
{
  int resto = t % interval;
  if(resto >= interval - 20)
  {
    return 1;
  } 
  else
  {
    return 0;
  }
}
void apagar()
{
  setLed(ledPin0, 0);
  setLed(ledPin1,0);
  setLed(ledPin2,0);
  setLed(ledPin3, 0);
  setLed(ledPin4, 0);
  setLed(ledPin5, 0);
}
void setLed(int pin, int v)
{
  if(v == -1)
  {
    if(digitalRead(pin) == HIGH) 
    {
      digitalWrite(pin, LOW);
    }
    else{
      digitalWrite(pin, HIGH);
    }
  }
  else
  {
    digitalWrite(pin, LOW); 
    if(v == 1)
    {
      digitalWrite(pin, HIGH);
    }
  }
}

void leds(int arr[], int mantem, int tempo)
{
  if(mantem == 1)//Inverte
  {
    if(arr[5] == 1) {
      setLed(ledPin0, -1);
    }
    if(arr[4] == 1) {
      setLed(ledPin1, -1);
    }      
    if(arr[3] == 1) {
      setLed(ledPin2, -1);
    }  
    if(arr[2] == 1) {
      setLed(ledPin3, -1);
    }  
    if(arr[1] == 1) {
      setLed(ledPin4, -1);
    } 
    if(arr[0] == 1) {
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
  delay(tempo);
}

void setup() {
  Serial.begin(9600);
  analogReference(INTERNAL1V1);
  pinMode(ledPin0, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  pinMode(ledPin5, OUTPUT);
}
void loop() {
  ADClido = analogRead(LM35);
  temperatura = ADClido * 0.1075268817;
  Serial.print("Temperatura ");
  Serial.print(temperatura);
  Serial.print(" C | ");
  intToBin(temperatura, bind, 6);
  printArr(bind, 6);
  Serial.print(" | ");
  Serial.print(count);
  Serial.println("");
  if(temperatura > 25)
  {
    if(controle == 0)
    {
      intToBin(temperatura, bin, 6);
      count++;
      controle = 1;
      leds(bin, 0, 1000);
    }
    leds(bin, 1, 1000);
  }
  else
  {
    controle = 0;
    leds(bind, 0, 1000);
  }
}










