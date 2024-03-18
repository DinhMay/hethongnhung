#include <LiquidCrystal_I2C.h>
#include <DHT.h>

LiquidCrystal_I2C lcd (0x27,16,2);
const int DHTPIN = 3;       // sử dụng chân số 4 
const int DHTTYPE = DHT11;   // loại cảm biến được sử dụng là dht11
DHT dht(DHTPIN, DHTTYPE);

byte degree[8] = {        // tạo kí hiệu độ C
  0B01110,
  0B01010,
  0B01110,
  0B00000,
  0B00000,
  0B00000,
  0B00000,
  0B00000
};

void setup() {
  Serial.begin( 9600);
  lcd.init();  
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Nhiet do: ");
  lcd.setCursor(0,1);
  lcd.print("Do am: ");
  lcd.createChar(1, degree);
  dht.begin();  
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  lcd.setCursor(10,0);
  lcd.print(round(t));
    Serial.print(round(t));
    Serial.write(1);
    Serial.print("C");

    lcd.setCursor(10,1);
    lcd.print(round(h));
    lcd.print(" %");    
}

