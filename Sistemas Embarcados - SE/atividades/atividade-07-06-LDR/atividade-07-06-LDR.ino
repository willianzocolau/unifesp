const int LDR = 3;
int ValorLido = 0;
int led = 2;
int flag = 0;
void setup()
{
  Serial.begin(9600);
  for (int x = 0; x < 10; x++) {
    pinMode(x + 2, OUTPUT);
  }
}

void loop()
{
  ValorLido = analogRead(LDR);
  delay(1000);
 if(ValorLido  <= 30)
  {
     apaga();
  }
  else if(ValorLido >= 300)
  {
    acende();
  }
  else
  {
    Serial.println("Fora do intervalo.");
  }
}

void apaga()
{
  if (led == 11)
  {
    digitalWrite(led, LOW);
    Serial.print("Apagou: ");
    Serial.println(led - 2);
    led--;
    flag = 1;
  }
  else if (flag == 1)
  {
    digitalWrite(led, LOW);
    Serial.print("Apagou: ");
    Serial.println(led - 2);
    flag = 0;
  }
  else if (led > 2)
  {
    led--;
    digitalWrite(led, LOW);
    Serial.print("Apagou: ");
    Serial.println(led - 2);
  }
  else if (led == 2)
  {
    digitalWrite(led, LOW);
    Serial.print("Apagou: ");
    Serial.println(led - 2);
  }
}

void acende()
{
  Serial.print("Acendeu: ");
  Serial.println(led - 2);
  digitalWrite(led, HIGH);
  if (led < 11)
  {
    led++;
  }
}
