#include <Bounce2.h>
#include <Wire.h>   
#include <DHT.h>
#include <LiquidCrystal_I2C.h>    // khai bao thu vien lcd sử dụng i2c
LiquidCrystal_I2C lcd(0x27,16,2);

Bounce debouncer = Bounce(); // Tạo một đối tượng Bounce

#define sensor 7
#define motor 6 //10
#define in3 5   //9 
#define in4 4   //8

int Led1= 13;
int Led2= 11;
int i;

int button = 10;
int Mode;  // Gán giá trị ban đầu cho Mode
bool modeChanged = false;
int previousMode = 0; // Biến lưu trữ Mode trước đó
int previousMysensor = 0;  // Sử dụng biến này để lưu trạng thái trước đó của mysensor

int mysensor;

const int DHTPIN = 3;       // sử dụng chân số 6
const int DHTTYPE = DHT11;   // loại cảm biến được sử dụng là dht11
DHT dht(DHTPIN, DHTTYPE);

byte degree[8] = {     
  0B01110,
  0B01010,
  0B01110,
  0B00000,
  0B00000,
  0B00000,
  0B00000,
  0B00000
};

void setup()
{
  lcd.init();           // khoi tạo lcd
  dht.begin();
  lcd.backlight();     // bật đèn lcd
  lcd.createChar( 0, degree);
  pinMode( Led1, OUTPUT);
  pinMode( Led2,OUTPUT);
  pinMode(button, INPUT);
  pinMode( motor, OUTPUT);
  pinMode( in3, OUTPUT);
  pinMode( in4, OUTPUT);
  digitalWrite( in3, LOW);
  digitalWrite( in4, HIGH);

  debouncer.attach(button); // Gắn nút bấm với đối tượng Bounce
  debouncer.interval( 50); // Đặt thời gian chờ giữa các lần đọc nút bấm( là nhấn giữ nút nhấn với khoảng tgian là 50)
  
}

void loop()
{
   int t = dht.readTemperature();  // nhiệt độ
   //int reading = analogRead(A0); 
   //float temperature = ( 5.0* reading* 100.0/ 1024.0); 
   int value = map( analogRead(A0), 0, 1023, 0, 255); 

   mysensor= digitalRead( sensor);
 
   debouncer.update(); // Cập nhật trạng thái nút bấm
  
  if (debouncer.fell()) {
    Mode++; // Tăng Mode lên một đơn vị
    if (Mode > 2) Mode = 0; // Nếu Mode lớn hơn 3, trở về Mode 0
  }

  if( mysensor!= previousMysensor) {
    previousMysensor= mysensor;  
  
    if( mysensor== 0) {
      if ( round( t) >= 10 && round( t) < 40) {
        if (previousMode != 1) {
          Mode = 1;
          previousMode = 1;
        }
      } 
      else if ( round( t) >= 40) {
         if (previousMode != 2) {
           Mode = 2;
           previousMode = 2;
         }
       } 
       else if ( round( t) < 10) {
         if (previousMode != 0) {
           Mode = 0;
           previousMode = 0;
         }
       }  
    }
    else {
//      lcd.clear();
//      analogWrite( motor, 0);
//      digitalWrite( Led1, LOW);
//      digitalWrite( Led2, LOW);
//      lcd.setCursor( 0, 0);
//      hienthichuoi( "khong co nguoi");
//      delay(500);
        Mode= 0;
        /*
         * khi sử dụng đoạn code trên, mô hình sẽ bị nhảy giữa hai chế độ "không có người" và "Mode== 0";
        */
    }
  }

   if (Mode == 0) {
    lcd.clear();
    analogWrite( motor, 0);
    digitalWrite( Led1, LOW);
    digitalWrite( Led2, LOW);
    lcd.print( "Quat tat");
    lcd.setCursor( 0, 1);
    lcd.print( "Temp:");
    lcd.setCursor( 5, 1);
    lcd.print( round( t));
    lcd.write( byte( 0));
    lcd.print( "C");
    delay(500);
  }
  else if (Mode == 1) {
    lcd.clear();
    analogWrite( motor, 150);
    digitalWrite( Led1, HIGH);
    digitalWrite( Led2, LOW);
    lcd.print( "Mode1-");
    lcd.setCursor( 6, 0);
    lcd.print( "Temp:");
    lcd.setCursor( 11, 0);
    lcd.print( round( t));
    lcd.write( byte( 0));
    lcd.print( "C");
    delay( 500);
  }
  else if (Mode == 2) {
    lcd.clear();
    analogWrite( motor, 100);
    digitalWrite( Led1, LOW);
    digitalWrite( Led2, HIGH);
    lcd.print( "Mode2-");
    lcd.setCursor( 6, 0);
    lcd.print( "Temp:");
    lcd.setCursor( 11, 0);
    lcd.print( round( t));
    lcd.write( byte( 0));
    lcd.print( "C");
    delay( 500);
  }
}
