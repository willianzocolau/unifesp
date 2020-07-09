#include <EEPROM.h> //Carrega a biblioteca

int endereco = 50;
String a = "Willian";
float v = 3.14;

void setup()
{
  Serial.begin(9600);
  Serial.println("Gravando nome e número float na memória: " + a + " - " + v);
  for(int i = 0; i < a.length(); i++)
  {
    EEPROM.write(i, byte(a.charAt(i)));
  }
  eeprom_write_block(endereco, &v, sizeof(v));
  //EEPROM.put(endereco, v);
  delay(2000);
}

void loop() 
{ 
  Serial.print("Lendo nome e número float da memoria EEPROM: ");
  for(int i = 0; i < a.length(); i++)
  {
    Serial.print(char(EEPROM.read(i)));
  }
  float b;
  eeprom_read_block(&b, endereco, sizeof(v));
  Serial.print(" - ");
  Serial.println(b);
  delay(2000);
}

