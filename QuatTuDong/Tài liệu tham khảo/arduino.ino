#include <Wire.h>;
#include <LiquidCrystal_I2C.h>;
#include <Servo.h>      // Thư viện điều khiển servo
#include <ArduinoJson.h>
#include<SPI.h>
#include<MFRC522.h>

Servo myservo;  
MFRC522 mfrc522(10,9); // Create MFRC522 instance.
LiquidCrystal_I2C lcd(0x27,16,2);

const int servoPin = A3;       // Khai báo chân điều khiển servo
const int trig = A1;     // chân trig của HC-SR04
const int echo = A2;     // chân echo của HC-SR04
unsigned long duration; // biến đo thời gian
int distance;           // biến lưu khoảng cách

unsigned long start_time; 
unsigned long timed_event;
unsigned long current_time;

bool isOpenDoor = false;
bool isOpenDoorSerial = false;
bool isOpenStatusLCD = false;


// Thay đổi chế độ
int statusRemote = 3; // 1 = tự động, 2 = điều khiển từ xa bằng app, 3 = mở bằng thẻ từ, 4 = hẹn giờ mở / đóng

const int pinRedLed = 7;
const int pinGreenLed = 6;
const int pinSpeaker = 5;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(5);
  lcd.init();       //Khởi động màn hình. Bắt đầu cho phép Arduino sử dụng màn hình
  lcd.backlight();   //Bật đèn nền

  myservo.attach(servoPin); 
  pinMode(trig,OUTPUT);   // chân trig sẽ phát tín hiệu
  pinMode(echo,INPUT);    // chân echo sẽ nhận tín hiệu
  pinMode(pinRedLed,OUTPUT);   // chân trig sẽ phát tín hiệu
  pinMode(pinGreenLed,OUTPUT);    // chân echo sẽ nhận tín hiệu
  pinMode(pinSpeaker,OUTPUT);    // chân echo sẽ nhận tín hiệu
  digitalWrite(pinRedLed,LOW);
  digitalWrite(pinGreenLed,LOW);
  digitalWrite(pinSpeaker,LOW);

  SPI.begin();     // Initiate  SPI bus
  mfrc522.PCD_Init(); // Initiate MFRC522
 
  timed_event = 1000; // after 1000 ms trigger the event
  current_time = millis();
  start_time = current_time; 
  int servoPos = map(0, 0, 1023, 0, 90);
  myservo.write(servoPos);
}

void displayLCD(){
  lcd.clear();
  if(statusRemote == 1){
    lcd.setCursor(0, 0);
    lcd.print("(1): tu dong");
    lcd.setCursor(0,1);
    lcd.print("Trang thai 123: " + String(isOpenStatusLCD ? "Mo" : "Dong"));
  }else if(statusRemote == 2){
    lcd.setCursor(0, 0);
    lcd.print("(2): App remote");
    lcd.setCursor(0,1);
    lcd.print("Trang thai: " + String(isOpenStatusLCD ? "Mo" : "Dong"));
  }else if(statusRemote == 3){
    lcd.setCursor(0, 0);
    lcd.print("(3): The tu");
    lcd.setCursor(0,1);
    lcd.print("Trang thai: " + String(isOpenStatusLCD ? "Mo" : "Dong"));
  }else if(statusRemote == 4){
    lcd.setCursor(0, 0);
    lcd.print("(4): Hen gio");
    lcd.setCursor(0,1);
    lcd.print("Trang thai: " + String(isOpenStatusLCD ? "Mo" : "Dong"));
  }
  digitalWrite(pinRedLed,!isOpenStatusLCD ? HIGH : LOW);
  digitalWrite(pinGreenLed,isOpenStatusLCD ? HIGH : LOW);
}

void calculateDistance(){
  /* Phát xung từ chân trig */
  digitalWrite(trig,0);   // tắt chân trig
  delayMicroseconds(2);
  digitalWrite(trig,1);   // phát xung từ chân trig
  delayMicroseconds(5);   // xung có độ dài 5 microSeconds
  digitalWrite(trig,0);   // tắt chân trig
  
  /* Tính toán thời gian */
  // Đo độ rộng xung HIGH ở chân echo. 
  duration = pulseIn(echo,HIGH);  
  // Tính khoảng cách đến vật.
  distance = int(duration/2/29.412);
  
}

void changeDoor(bool isOpen){
  isOpenStatusLCD = isOpen;
  displayLCD();
  
  if(isOpen){
    if(isOpenDoor != isOpen){
      for(int pos = 0 ; pos < 1023; pos ++){
        // Chuyển giá trị analog (0-1023) đọc được từ biến trở sang số đo độ (0-180độ)
        // dùng để điều khiển góc quay cho servo
        int servoPos = map(pos, 0, 1023, 0, 90);
        
        // Cho servo quay một góc là servoPos độ
        myservo.write(servoPos);
        delay(1);
      }
      isOpenDoor = true;
      digitalWrite(pinSpeaker, HIGH);
      delay(200);
      digitalWrite(pinSpeaker, LOW);
      delay(200);
      digitalWrite(pinSpeaker, HIGH);
      delay(200);
      digitalWrite(pinSpeaker, LOW);
    }
    
  }else{
    if(isOpenDoor != isOpen){
      for(int pos = 1023 ; pos >= 0; pos --){
        // Chuyển giá trị analog (0-1023) đọc được từ biến trở sang số đo độ (0-180độ)
        // dùng để điều khiển góc quay cho servo
        int servoPos = map(pos, 0, 1023, 0, 90);
        
        // Cho servo quay một góc là servoPos độ
        myservo.write(servoPos);
        delay(1);
      }
      isOpenDoor = false;
      digitalWrite(pinSpeaker, HIGH);
      delay(500);
      digitalWrite(pinSpeaker, LOW);
    }
    
  }
  
  
}

void readSerial(){
  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming:
    String incoming = Serial.readString();
    incoming.trim();
    Serial.println(incoming);

    DynamicJsonBuffer jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(incoming);

    String getter = root["getter"];
    
    if(getter.equals("arduino")){
      String statusDoor = root["status_door"];
      if(statusDoor.equals("1")){
        statusRemote = 1;
      }else if(statusDoor.equals("2")){
        statusRemote = 2;
      }else if(statusDoor.equals("3")){
        statusRemote = 3;
      }else if(statusDoor.equals("4")){
        statusRemote = 4;
      }

      String isOpenDoorStr = root["is_open_door"];
      if(isOpenDoorStr.equals("1")){
        isOpenDoorSerial = true;
      }else{
        isOpenDoorSerial = false;
      }
    }

    Serial.flush(); 
  }
}

bool isApproveCard(){
  // Look for new cards
 if(!mfrc522.PICC_IsNewCardPresent()){
   return false;
 }
 // Select one of the cards
 if(!mfrc522.PICC_ReadCardSerial()){
   return false;
 }
 //Show UID on serial monitor
 Serial.print("UID tag :");
 String content="";
 byte letter;
 for(byte i=0;i<mfrc522.uid.size;i++)
 {
     Serial.print(mfrc522.uid.uidByte[i]<0x10?" 0":" ");
     Serial.print(mfrc522.uid.uidByte[i],HEX);
     content.concat(String(mfrc522.uid.uidByte[i]<0x10?" 0":" "));
     content.concat(String(mfrc522.uid.uidByte[i],HEX));
 }
 Serial.println();
 Serial.print("Message : ");
  content.toUpperCase();
 if(content.substring(1)=="54 67 5B 85") //change here the UID of the card/cards that you want to give access


 {
   Serial.println("Authorized access");
   return true;
 }else {
   Serial.println(" Access denied");
   return false;
 }
}

void loop() {
  readSerial();

  current_time = millis(); // update the timer every cycle


  if (current_time - start_time >= timed_event) {
         timed_event = 1000;
    if(statusRemote == 1){
      calculateDistance();
      if(distance > 0){
        changeDoor(distance < 10);
        if(distance < 10){
         timed_event = 5000;
        }
      }
    }else if(statusRemote == 2){
      changeDoor(isOpenDoorSerial);
      if(isOpenDoorSerial){
         timed_event = 5000;
      }
    }else if(statusRemote == 3){
      if (isApproveCard()) {
         changeDoor(true);
         timed_event = 5000;
      }else{
         changeDoor(false);
      }
    }else if(statusRemote == 4){
      changeDoor(isOpenDoorSerial);
      if(isOpenDoorSerial){
         timed_event = 5000;
      }else{
         changeDoor(false);
      }
    }
    displayLCD();
    start_time = current_time;  // reset the timer
  }
  
}
