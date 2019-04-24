#include <SoftwareSerial.h>
SoftwareSerial mySerial(9, 10);
int sensor = 7;
int buzzer = 8;
int gas_value = LOW;
int sms_count = 0;

void setup()
{

  pinMode(sensor, INPUT);
  pinMode(buzzer, OUTPUT);
  mySerial.begin(9600);

}

void loop()
{
  checkGas();
}

void checkGas() {
  gas_value = digitalRead(sensor);
  if (gas_value == LOW) {
    Serial.println(gas_value);
    digitalWrite(buzzer, HIGH);
    sendTextMessage();
  } else {
    digitalWrite(buzzer, LOW);
  }
}

void sendTextMessage() {
  mySerial.println("AT+CMGF=1");    //To send SMS in Text Mode
  delay(1000);
  mySerial.println("AT+CMGS=\"+91XXXXXXXXXX\"\r");
  delay(1000);
  mySerial.println("Gas Leaking!");//the content of the message
  delay(200);
  mySerial.println((char)26);//the stopping character
  delay(1000);
  sms_count++;
}