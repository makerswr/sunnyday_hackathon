#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal.h>
#include "DHT.h"
#define DHTTYPE DHT11
#define enA 9
#define in11 6
#define in12 7
#define btn1 11
#define btn2 12
#define btn3 13
LiquidCrystal_I2C lcd(0x3F, 16, 2);
uint8_t DHTPin = 8;
DHT dht(DHTPin, DHTTYPE);
float Temperature;
float Humidity;
int fanSpeed=200;
int fanLCD;
void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(enA,OUTPUT);
  pinMode(in11,OUTPUT);
  pinMode(in12,OUTPUT);
  pinMode(btn1,INPUT_PULLUP);
  pinMode(btn2,INPUT_PULLUP);
  pinMode(btn3,INPUT_PULLUP);
  pinMode(DHTPin,INPUT);
  digitalWrite(in12, LOW);
  digitalWrite(in11, HIGH);
}
void loop() {
  if (digitalRead(btn1)==HIGH){
    ecoMode();
  }
  if (digitalRead(btn2)==HIGH){
    optiMode();
  }
  if (digitalRead(btn3)==HIGH){
    boostMode();
  }
  Temperature = dht.readTemperature();
  Serial.println(Temperature);
  Humidity = dht.readHumidity();
  analogWrite(enA,fanSpeed);
  lcd.print("TEMP: ");
  lcd.print("26");      // display the temperature
  lcd.print("C ");
  lcd.setCursor(0,1);   // move cursor to next line
  lcd.print("FANS: ");
  fanLCD = int((fanSpeed*100)/255);
  lcd.print(fanLCD);    // display the fan speed
  lcd.print("%");
  delay(200);
  lcd.clear();
  
}
void ecoMode(){
  fanSpeed = 135;
  Serial.println("e");
}
void optiMode(){
  fanSpeed = int((Temperature*255)/40);
  Serial.println("o");
}
void boostMode(){
  fanSpeed = 255;
  Serial.println("b");
}
