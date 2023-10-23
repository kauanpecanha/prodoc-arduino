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
File myFile = SD.open("DADOS.txt", FILE_WRITE); // declaração dp arquivo para fazer gravação no txt dentro do cartão sd

// -------------------------------------------------- declaração da função de conversão de valores -------------------------------------------

float convert(int value){ // função para conversão de valores
  return map(value, 1023, 0, 0, 100);
}

// -------------------------------------------------- declaração da função de impressão de valores -------------------------------------------
void valuesPercent(float v, int key){ // função com o intuito de imprimir a faixa de valores dos sensores tanto no monitor serial quanto no visor lcd
  
  if(key == 0){  // caso a key de identificação seja 0 (monitor serial), ele executa as Serial.println()
    
    if (v <= 10){
      Serial.println("0% e 10%");
    }
    else if(v > 10 && v <=20){
      Serial.println("10% a 20%");
    }
    else if(v > 20 && v <=30){
      Serial.println("20% a 30%");
    }
    else if(v > 30 && v <40){
      Serial.println("30% a 40%");
    }
    else if(v > 40 && v <=50){
      Serial.println("40% a 50%");
    }
    else if(v > 50 && v <=60){
      Serial.println("50 a 60%");
    }
    else if(v > 60 && v <=70){
      Serial.println("60% a 70%");
    }
    else if(v > 70 && v <=80){
      Serial.println("70% a 80%");
    }
    else if(v > 80 && v <=90){
      Serial.println("80% a 90%");
    }
    else if(v > 90 && v <=100){
      Serial.println("90% a 100%");
    }
    else{
      Serial.println("Error");
    }
  }
  
  if(key == 1){  // caso a key de identificação seja 1(visor lcd), ele executa as lcd.print()
    if (v <= 10){
      lcd.print("0%-10%");
    }
    else if(v > 10 && v <=20){
      lcd.print("10%-20%");
    }
    else if(v > 20 && v <=30){
      lcd.print("20%-30%");
    }
    else if(v > 30 && v <40){
      lcd.print("30%-40%");
    }
    else if(v > 40 && v <=50){
      lcd.print("40%-50%");
    }
    else if(v > 50 && v <=60){
      lcd.print("50%-60%");
    }
    else if(v > 60 && v <=70){
      lcd.print("60%-70%");
    }
    else if(v > 70 && v <=80){
      lcd.print("70%-80%");
    }
    else if(v > 80 && v <=90){
      lcd.print("80%-90%");
    }
    else if(v > 90 && v <=100){
      lcd.print("90%-100%");
    }
    else{
      lcd.print("Error");
    }
  }
}

// -------------------------------------------------- declaração da função de impressão padrão -------------------------------------------

void printSerial(float v1, float v2, int k){ // função responsável por imprimir os valores no monitor serial
  Serial.print("Sensor 1: "); // impressão da faixa de valores no primeiro sensor
  valuesPercent(v1, k); // chamada da função
  Serial.print("Sensor 2: "); // impressão da faixa de valores no segundo sensor
  valuesPercent(v2, k); // chamada da função
}

void writeSD(float v1, float v2, int key){
  
  String str = "";
  if(key == 0){
    
    if(SD.begin(10)){
      Serial.println("Cartão Inicializado.");

      if(SD.exists("DADOS.txt")){
        Serial.println("Arquivo envontrado com sucesso.");
      }
      else{
        Serial.println("Arquivo não encontrado.");
      }
    }
    else{
      Serial.println("Falha na leitura da porta 10");
    }

  }

  if(key == 1){
    
    if(SD.begin(10)){

      if(SD.exists("DADOS.txt")){
        myFile = SD.open("DADOS.txt", FILE_WRITE);

        str = "Sensor 1: " + String(v1) + "\t" + "Sensor 2: " + String(v2);
        Serial.println(str);
        myFile.println(str);
        myFile.close();
        Serial.println("Dados escritos.");

      }
      else{
        Serial.println("Arquivo não encontrado.");
      }
    }
    else{
      Serial.println("Falha na leitura da porta 10");
    }

  }
}

// ------------------------------------------------- função setup ----------------------------------------------------------------------------

void setup() {

  Serial.begin(9600); // serial monitor na porta 9600

  pinMode(sensorUmidade1, INPUT); // definição do primeiro sensor como entrada de dados
  pinMode(sensorUmidade2, INPUT); // definição do segundo sensor como entrada de dados

  lcd.init(); // inicialização do lcd
  lcd.clear(); // limpeza prévia de quaisquer informações que estejam visíveis no seu visor
  lcd.setBacklight(HIGH); // luz traseira do lcd ligada

  pinMode(CS, OUTPUT);


  // if(SD.begin(10)){ // estrutura para detectar o leitor de cartão sd na porta 10
  //   Serial.println("Cartão inicializado.\n"); // mensagem de sucesso
  // }
  // else{ // do contrário
  //   Serial.println("Falha na leitura.\n"); // mensagem de falha
  // }

  // if (SD.exists("DADOS.txt")){
  //   myFile = SD.open("DADOS.txt", FILE_WRITE); // o arquivo deverá estar interligado com um txt dentro do leitor de cartão sd, sendo, neste caso, dados.txt
  //   Serial.println("Arquivo envontrado com sucesso.");
  //   myFile.close();
  // }
  // else{
  //   Serial.println("Arquivo inexistente.");
  // }

  writeSD(0, 0, 0);

}

// ------------------------------------------------- função loop -----------------------------------------------------------------------------

void loop() {

  readValue1 = analogRead(sensorUmidade1); // variável de captura do valor analógico retornado pelo primeiro sensor de umidade do solo
  readValue2 = analogRead(sensorUmidade2); // variável de captura do valor analógico retornado pelo segundo sensor de umidade do solo

  finalValue1 = convert(readValue1); // variável de armazenamento do primeiro valor depois de transformado
  finalValue2 = convert(readValue2); // variável de armazenamento do segundo valor depois de transformado

  myFile.println(finalValue1); // gravação da informação do primeiro sensor de umidade
  myFile.println(finalValue2); // gravação da informação do segundo sensor de umidade
  
  printSerial(finalValue1, finalValue2, 0); // impressão das informações no monitor serial
  lcd.setCursor(0, 0); // posicionamento do cursor na localização 3, 0 do lcd
  lcd.print("Umidade1:");
  valuesPercent(finalValue1, 1); // exibição do valor do sensor 1, no lcd

  lcd.setCursor(0, 1); // posicionamento do cursor na localização 3, 1 do lcd
  lcd.print("Umidade2:");
  valuesPercent(finalValue2, 1); // exibição do valor do sensor 2, no lcd

  writeSD(finalValue1, finalValue2, 1); // gravação dos dados no cartão sd
 
  delay(1000);

}