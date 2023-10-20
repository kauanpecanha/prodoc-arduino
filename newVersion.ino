#include<Wire.h>
#include<LiquidCrystal_I2C.h>
#include<SD.h>

// Link: https://docs.google.com/document/d/18BcFedbnAYJMPPw6hZ3jfEvPRNKD3i2-enMv52Jnmac/edit?usp=sharing

// ------------------------------------------------- declaração e definição dos sensores de umidade ------------------------------------------

const int sensorUmidade1 = A0; // declaração do primeiro sensor de umidade na porta A0
const int sensorUmidade2 = A1; // declaração do primeiro sensor de umidade na porta A1

int readValue1 = 0;
int readValue2 = 0;
int finalValue1 = 0;
int finalValue2 = 0;

// ------------------------------------------------- declaração e definição do lcd -----------------------------------------------------------
LiquidCrystal_I2C lcd(0x27,16,2); // declaração do display lcd, sendo o primeiro argumento o endereço, o segundo, a quantidade de colunas, e o terceiro, a quantidade de linhas

// ------------------------------------------------- declaração e definição do cartão sd -----------------------------------------------------
int CS = 10;
File myFile; // declaração dp arquivo para fazer gravação no txt dentro do cartão sd

// -------------------------------------------------- declaração da função de conversão de valores -------------------------------------------

float convert(int value){ // função para conversão de valores
  return map(value, 0, 1023, 0, 100);
}

// ------------------------------------------------- função setup ----------------------------------------------------------------------------

void setup() {

  Serial.begin(9600); // serial monitor na porta 9600

  pinMode(sensorUmidade1, INPUT); // definição do primeiro sensor como entrada de dados
  pinMode(sensorUmidade2, INPUT); // definição do segundo sensor como entrada de dados

  lcd.init(); // inicialização do lcd
  lcd.clear(); // limpeza prévia de quaisquer informações que estejam visíveis no seu visor
  lcd.setCursor(0, 0);
  // lcd.print("S1:");
  lcd.setCursor(0, 1);
  // lcd.print("S2:");
  lcd.setBacklight(HIGH); // luz traseira do lcd ligada

  pinMode(CS, OUTPUT);

  myFile = SD.open("dados.txt"); // o arquivo deverá estar interligado com um txt dentro do leitor de cartão sd, sendo, neste caso, dados.txt

  if(SD.begin(10)){ // estrutura para detectar o leitor de cartão sd na porta 10
    Serial.println("Cartão inicializado.\n"); // mensagem de sucesso
  }
  else{ // do contrário
    Serial.println("Falha na leitura.\n"); // mensagem de falha
  }

}

// ------------------------------------------------- função loop -----------------------------------------------------------------------------

void loop() {

  readValue1 = analogRead(sensorUmidade1); // variável de captura do valor analógico retornado pelo primeiro sensor de umidade do solo
  readValue2 = analogRead(sensorUmidade2); // variável de captura do valor analógico retornado pelo segundo sensor de umidade do solo

  finalValue1 = convert(readValue1); // variável de armazenamento do primeiro valor depois de transformado
  finalValue2 = convert(readValue2); // variável de armazenamento do segundo valor depois de transformado

  myFile.println(finalValue1); // gravação da informação do primeiro sensor de umidade
  myFile.println(finalValue2); // gravação da informação do segundo sensor de umidade
  
  Serial.println(finalValue1); // impressão do valor no monitor serial
  Serial.println(finalValue2); // impressão do valor no monitor serial

  lcd.setCursor(0, 0); // posicionamento do cursor na localização 3, 0 do lcd
  lcd.print("Umidade1: ");
  lcd.print(finalValue1); // impressão do valor nesta localização

  lcd.setCursor(0, 1); // posicionamento do cursor na localização 3, 1 do lcd
  lcd.print("Umidade2: ");
  lcd.print(finalValue2); // impressão do valor nesta localização

  delay(1000);

}