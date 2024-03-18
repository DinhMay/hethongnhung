#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "e3b9d0be608e4a44b41c3955747646d2";

char ssid[] = "SANTAK-TG";
char pass[] = "tg3955395tg";

WidgetLED LedConnect(V0);
WidgetLED StatusD1(V1);

BlynkTimer timer;

void blinkLedWidget()
{
  if (LedConnect.getValue()) {
    LedConnect.off();
  } else {
    LedConnect.on();
  }
}

BLYNK_WRITE(V2)
{
  int pinValue = param.asInt(); 
  digitalWrite(D1,pinValue);
  if (!digitalRead(D1)) {
    StatusD1.on();
  } else {
    StatusD1.off();
  }
}

void setup()
{
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, blinkLedWidget);

  pinMode(D1,OUTPUT);
  digitalWrite(D1,HIGH);
}

void loop()
{
  Blynk.run();
  timer.run();
}
