#include<Wire.h>
#include<LiquidCrystal_I2C.h>

// 0x38H -> endereço do lcd
const int sensorUmidade1 = A0;
const int sensorUmidade2 = A1;
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  pinMode(sensorUmidade1, INPUT);
  pinMode(sensorUmidade2, INPUT);
  
  lcd.init();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Umidade1: ");
  lcd.setCursor(0, 1);
  lcd.print("Umidade2: ");
  lcd.setBacklight(HIGH);
}

float convert(int value){
  return map(value, 0, 1023, 0, 100);
}

void loop() {

  int readValue1 = analogRead(sensorUmidade1);
  int readValue2 = analogRead(sensorUmidade2);

  float finalValue1 = convert(readValue1);
  float finalValue2 = convert(readValue2);

  lcd.setCursor(9, 0);
  lcd.print(finalValue1, 2);

  lcd.setCursor(9, 1);
  lcd.print(finalValue2, 2);

  delay(1000);
}
