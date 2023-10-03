#include <LiquidCrystal_I2C.h> // de Frank Barbender

// https://docs.google.com/document/d/1Mnh3N63yQ0H5WcuVrR8jICamCW0bwn2av7KG0pzVjfY/edit?usp=sharing
//Programa: Display LCD 16x2 e modulo I2C
//Autor: Arduino e Cia

#include <Wire.h>

//Inicializa o display no endereco 0x27
LiquidCrystal_I2C lcd(0x27,16,2);
const int sensor1 = A0;
const int sensor2 = A1;

int analog1 = 0;
int analog2 = 0;
int value1 = 0;
int value2 = 0;

float convert(int value){ // função para conversão de valores
  return map(value, 1023, 0, 0, 100);
}

void setup()
{
  Serial.begin(9600);
  lcd.init();
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
}
void loop()
{
  lcd.setBacklight(HIGH);
  lcd.setCursor(0, 1);
  lcd.print("Olá mundo");
  analog1 = analogRead(sensor1);
  analog2 = analogRead(sensor2);

  value1 = convert(analog1);
  value2 = convert(analog2);

  Serial.println(value1);
  Serial.println(value2);

  delay(500);
}