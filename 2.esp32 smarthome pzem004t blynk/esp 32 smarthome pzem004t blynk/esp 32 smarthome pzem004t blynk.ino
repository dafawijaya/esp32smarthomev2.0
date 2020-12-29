#include <PZEM004Tv30.h>
#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp32.h>

int relay1       = 32;
int relay2       = 27;
int relay3       = 14;
int relay4       = 13;


#include <WiFi.h>
#include <WiFiClient.h>
char auth[] = "Fhqe-hOxDP-PlWrqOlINijwt09Z_w9Ll";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Kelg_Hadie"; // isi nama network
char pass[] = "Vitri1972" ; // isi pass wifi, kalau open network isi ""

PZEM004Tv30 pzem(&Serial2);

void setup() {
  Serial.begin(115200);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  pinMode(relay1, HIGH);
  pinMode(relay2, HIGH);
  pinMode(relay3, HIGH);
  pinMode(relay4, HIGH);
  Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
}

void loop() {
  float voltage = pzem.voltage();
  if (!isnan(voltage)) {
    Serial.print("Voltage: "); Serial.print(voltage); Serial.println("V");
  } else {
    Serial.println("Error reading voltage");
    Blynk.notify ("tidak ada tegangan");
  }

  float current = pzem.current();
  if (!isnan(current)) {
    Serial.print("Current: "); Serial.print(current); Serial.println("A");
  } else {
    Serial.println("Error reading current");
  }

  float power = pzem.power();
  if (!isnan(power)) {
    Serial.print("Power: "); Serial.print(power); Serial.println("W");
  } else {
    Serial.println("Error reading power");
  }

  float energy = pzem.energy();
  if (!isnan(energy)) {
    Serial.print("Energy: "); Serial.print(energy, 3); Serial.println("kWh");
  } else {
    Serial.println("Error reading energy");
  }

  float frequency = pzem.frequency();
  if (!isnan(frequency)) {
    Serial.print("Frequency: "); Serial.print(frequency, 1); Serial.println("Hz");
  } else {
    Serial.println("Error reading frequency");
  }

  float pf = pzem.pf();
  if (!isnan(pf)) {
    Serial.print("PF: "); Serial.println(pf);
  } else {
    Serial.println("Error reading power factor");
  }

  Serial.println();

  Blynk.virtualWrite (V5, power);
  Blynk.virtualWrite (V6, energy);
  Blynk.virtualWrite (V7, voltage);
  Blynk.virtualWrite (V8, current);
  Blynk.virtualWrite (V9, frequency);
  Blynk.virtualWrite (V10, pf);
  Blynk.run();


  delay(1000);
}
