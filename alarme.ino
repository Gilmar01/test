#include <Wire.h>
#include "RTClib.h"
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
RTC_DS1307 rtc;

int hora = 0;
int minuto = 0;
int segundo = 0;
void setup () {
Wire.begin();
rtc.begin();

// set up the LCD's number of columns and rows:
lcd.begin(16, 2);

Serial.begin(9600);
pinMode(13, OUTPUT);
digitalWrite(13, LOW);
pinMode(6, OUTPUT);
digitalWrite(6, LOW);
if (!rtc.isrunning()) {
lcd.print("RTC parado, vou ajustar com a hora da compilacao...");
rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}
}

void printnn(int n) {
// imprime um numero com 2 digitos
// acrescenta zero `a esquerda se necessario
String digitos = String(n);
if (digitos.length() == 1) {
digitos = "0" + digitos;
}
lcd.print(digitos);
}

void loop () {
// Obtem a data e hora correntes e armazena em tstamp
DateTime tstamp = rtc.now();
hora = (tstamp.hour());
minuto = (tstamp.minute());
segundo = (tstamp.second());
// Mostra no monitor serial a data e hora correntes
lcd.setCursor(3, 0);
printnn(tstamp.day());
lcd.print('/');
printnn(tstamp.month());
lcd.print('/');
lcd.print(tstamp.year(), DEC);
lcd.setCursor(3, 1);
lcd.print (' ');
printnn(tstamp.hour());
lcd.print(':');
printnn(tstamp.minute());
lcd.print(':');
printnn(tstamp.second());
delay(1000);
lcd.clear();
//lcd.println();
Serial.print (hora);
Serial.print (":");
Serial.print (minuto);
Serial.print (":");
Serial.println (segundo);
// Periodo da manha
if (hora == 7 && minuto == 35 && segundo == 0) {
alarme();
}
if (hora == 9 && minuto == 35 && segundo == 0) {
alarme();
}
if (hora == 9 && minuto == 50 && segundo == 0) {
alarme();
}
if (hora == 11 && minuto == 35 && segundo == 0) {
alarme();
}
//periodo da tarde
if (hora == 13 && minuto == 20 && segundo == 0) {
alarme();
}
if (hora == 15 && minuto == 35 && segundo == 0) {
alarme();
}
if (hora == 15 && minuto == 50 && segundo == 0) {
alarme();
}
if (hora == 17 && minuto == 20 && segundo == 0) {
alarme();
}
}
void alarme() {
digitalWrite(13, HIGH);
digitalWrite(6, HIGH);
lcd.setCursor(6, 0);
lcd.print ("CURSO");
lcd.setCursor(3, 1);
lcd.print ("PROGRAMACAO");
delay(10000);
digitalWrite(13, LOW);
digitalWrite(6, LOW);
lcd.clear();
}
