/*----------------------------------------------------------------------------------------
  https://maxpromer.github.io/LCD-Character-Creator/ trang web tạo ký tự đặc biệt
  lcd.init()  : Khởi tạo Màn hình Màn hình
  lcd.clear() : Xóa màn hình, đưa con trỏ về vị trí 0,0
  lcd.home()  : Đưa con trỏ về vị trí 0
  lcd.setCursor(x,y)  : Đưa con trỏ về vị trí cột thứ x, hàng thứ y
  lcd.noDisplay() : Không hiển thị gì trên màn hình cả
  lcd.display() : Hiển thị lên màn hình
  lcd.noBlink() : Không nhấp nháy con trỏ
  lcd.blink() : Nhấp nháy con trỏ
  lcd.scrollDisplayLeft() : Cuộn màn hình bên trái
  lcd.scrollDisplayRight()  : Cuộn màn hình bên phải
  lcd.leftToRight() : Kí tự sẽ hiển thị từ phía bên trái sang phải
  lcd.rightToLeft() : Kí tự sẽ hiển thị từ phía phải sang trái
  lcd.noBacklight() : Tắt đèn nền
  lcd.backlight() : Có đèn nền
  lcd.write(x)  : Màn hình sẽ in ra kí tự thứ x 
  lcd.createChar(location,charmap[])  : Hiển thị một kí tự charmap[] bất kì
  ----------------------------------------------------------------------------------------
  Channel M&E Automation:https://bit.ly/3uz3Bt8
  Vui lòng đăng ký kênh https://bit.ly/34a2of1 cảm ơn các bạn rất nhiều!
  Danh sách phát Arduino : https://bit.ly/34BUDlU
  ---------------------------------------------------------------------------------------- */

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int _LM35 = A0; //the analog pin the LM35 Vout
int Val_LM35;
float Volt;
float TempC;
float TempF;  

//Create Special character
 byte C[] = {
  B11000,
  B11000,
  B00111,
  B01000,
  B01000,
  B01000,
  B00111,
  B00000
};
byte F[] = {
  B11000,
  B11000,
  B00111,
  B00100,
  B00111,
  B00100,
  B00100,
  B00100
};
byte va[] = {
  B00000,
  B01100,
  B10010,
  B10100,
  B01000,
  B10101,
  B10010,
  B01101
};
                        
void setup()
{
  Serial.begin(9600);  //Start the serial connection with the computer
  lcd.init();
  lcd.backlight();    //to view the result open the serial monitor 
  lcd.createChar(0, C); // Create Special character *C
  lcd.createChar(1, F); // Create Special character *F
  lcd.createChar(2, va); // Tạo ký tự đặc biệt &
}
 
void loop()          
{
 lcd.clear();
 Val_LM35 = analogRead(_LM35);  //getting the Volt Val_LM35 from the temperature sensor
  //5000mV ↔ 1024
  //Volt ↔ Val_LM35

 Volt = (Val_LM35 * 5000.0)/1024.0; // converting that Val_LM35 to mVolt
 Serial.print(Volt); Serial.println(" volts");
 //The resolution is 10 mV / degree centigrade with a
 // 1*C ↔ 10mV
 //TempC ↔Volt
 TempC =Volt/10.0;
 Serial.print(TempC); Serial.println(" degrees C");
 
 TempF = (TempC * 9.0 / 5.0) + 32.0; // now convert to Fahrenheit
 Serial.print(TempF); Serial.println(" degrees F");
 // Display the Text "M&E Automation" 
  lcd.setCursor(1, 0); 
  lcd.print("M");
  lcd.setCursor(2, 0); 
  lcd.write(byte(3)); // Call Special character was create &.
  lcd.setCursor(3, 0);
  lcd.print("E");
  lcd.setCursor(5, 0);
  lcd.print("Automation");
  delay(100);
  
  lcd.setCursor(2,1);
  lcd.print("Temp: "); 
  lcd.setCursor(8,1);
  lcd.print(TempC); 
  lcd.setCursor(13,1);
  lcd.write(byte(0)); // Call Special character was create *C.
 delay(10000);
 
 lcd.clear();
 
  lcd.setCursor(1, 0); 
  lcd.print("M");
  lcd.setCursor(2, 0); 
  lcd.write(byte(3)); // Call Special character was create &.
  lcd.setCursor(3, 0);
  lcd.print("E");
  lcd.setCursor(5, 0);
  lcd.print("Automation");
  
  lcd.setCursor(2,1);
  lcd.print("Temp: "); 
  lcd.setCursor(8,1);
  lcd.print(TempF); 
  lcd.setCursor(13,1);
  lcd.write(byte(1)); // Call Special character was create *F.
  delay(10000); 
}
