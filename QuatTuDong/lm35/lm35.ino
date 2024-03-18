#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Wire.h>   
#include "html.h"

#define lm35 d1

ESP8266WebServer server( 80);
//WiFiServer server( 80);

const String tenwifi= "PHONG 204.D2_5G";
const String mkwifi= "hoangcung204";

int reading;
float nhietdo;

void ketnoi() {
  String s= MAIN_page;
  server.send( 200, "text/html", s);
}

void docdulieunhietdo() {
  reading = analogRead(A0); 
  nhietdo = ( 5.0* reading* 100.0/ 1024.0)- 85;
  String snhietdo= String ( nhietdo);
  if( isnan( nhietdo) ) {
    server.send( 200, "text/plain", "cam bien khong hoat dong");
  }
  else {
    server.send( 200, "text/plain", snhietdo);
  }
}

void setup()
{
  Serial.begin( 9600);

  WiFi.begin( tenwifi, mkwifi);
  Serial.print( tenwifi);
  while( WiFi.status()!= WL_CONNECTED) {
    delay( 500);
    Serial.print( "."); 
  }
  Serial.println( "");
  Serial.println( "wifi da duoc ket noi");
  server.begin();
  Serial.println( "dia chi ip: ");
  Serial.println( WiFi.localIP());

  server.on( "/docnhietdo", docdulieunhietdo);
 // server.begin;
}

void loop()
{
     server.handleClient();
}
