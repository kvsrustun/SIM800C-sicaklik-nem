#include <Wire.h>
#include <Deneyap_SicaklikNemOlcer.h>
#include <SoftwareSerial.h>

TempHum sensor;
SoftwareSerial mySerial(D8, D14);  

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  sensor.begin();

  // SIM800 ayarları
  delay(1000);
  mySerial.println("AT");
  delay(1000);
  mySerial.println("AT+CMGF=1"); 
  delay(1000);
}

void loop() {
  float sicaklik = sensor.getTempValue();
  float nem = sensor.getHumValue();

  String mesaj = "Sicaklik: " + String(sicaklik) + "C\nNem: " + String(nem) + "%";

  sendSMS("905386226808", mesaj); 

  delay(5000); 
}

void sendSMS(String numara, String mesaj) {
  mySerial.println("AT+CMGF=1");
  delay(500);
  mySerial.println("AT+CMGS=\"" + numara + "\"");
  delay(500);
  mySerial.print(mesaj);
  mySerial.write(26); // CTRL+Z -> SMS gönder
  delay(2000);
}
