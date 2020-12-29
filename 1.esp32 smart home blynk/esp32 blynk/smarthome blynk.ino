#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
BlynkTimer timer;


int relay1       = 32;
int relay2       = 27;
int relay3       = 14;
int relay4       = 13;

#define LED1 2
#define LED2 4
#define LED3 25
#define LED4 26
#define Buzzer 33
int MODE = 0;

char ssid[] = "Kelg_Hadie"; // isi nama network
char pass[] = "Vitri1972" ; // isi pass wifi, kalau open network isi ""

char auth[] = "Fhqe-hOxDP-PlWrqOlINijwt09Z_w9Ll"; // auth dari blynk

void checkBlynk() { // memanggil setiap 3 seconds by SimpleTimer

  bool isconnected = Blynk.connected();
  if (isconnected == false) {
    MODE = 1;
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    Blynk.notify ("wifi mati");
  }
  if (isconnected == true) {
    MODE = 0;
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, HIGH);
  }
}


void setup() {


  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  pinMode(relay1, HIGH);
  pinMode(relay2, HIGH);
  pinMode(relay3, HIGH);
  pinMode(relay4, HIGH);
  Serial.begin(115200);

  delay(10);
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);
  int wifi_ctr = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");

  Blynk.begin(auth, ssid, pass);
  timer.setInterval(3000L, checkBlynk); // check if connected to Blynk server every 3 seconds
}

void loop() {
  Blynk.run();
  timer.run();
}
