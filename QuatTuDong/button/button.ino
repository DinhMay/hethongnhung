#include <Bounce2.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
Bounce debouncer = Bounce(); // Tạo một đối tượng Bounce

int button = 10;
int Ledpin[] = {13, 11};
int i;
int Mode= 0;

#define motor 6
#define in3 5
#define in4 4

bool modeChanged = false;

void setup() {
  lcd.begin();
  lcd.backlight();
  pinMode(motor, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  pinMode(button, INPUT);
  for (i = 0; i < 2; i++) {
    pinMode(Ledpin[i], OUTPUT);
  }

  debouncer.attach(button);
  debouncer.interval(50); // Thời gian chờ giữa các lần đọc nút bấm (50ms)
}

void hienthichuoi(String chuoi) {
  for (int j = 0; j < chuoi.length(); j++) {
    lcd.print(chuoi[j]);
  }
}

void loop() {
  debouncer.update(); // Cập nhật trạng thái nút bấm

  if (debouncer.fell() && !modeChanged) {
    Mode++; // Tăng Mode lên một đơn vị
    if (Mode > 2) Mode = 0; // Nếu Mode lớn hơn 2, trở về Mode 0
    modeChanged = true; // Đánh dấu rằng đã thay đổi Mode
  }
  if (debouncer.rose()) {
    // Nếu nút bấm được thả ra
    modeChanged = false; // Đặt lại biến cờ
  }

  if (Mode == 0) {
    digitalWrite(Ledpin[0], LOW);
    digitalWrite(Ledpin[1], LOW);

    lcd.clear();
    lcd.setCursor(0, 0);
    hienthichuoi("Quat tat");
    analogWrite(motor, 0);
    delay(500);
  }
  if (Mode == 1) {
    digitalWrite(Ledpin[0], HIGH);
    digitalWrite(Ledpin[1], LOW);

    lcd.clear();
    analogWrite(motor, 40);
    lcd.setCursor(0, 0);
    hienthichuoi("Mode1-");
    delay(500);
  }
  if (Mode == 2) {
    digitalWrite(Ledpin[0], LOW);
    digitalWrite(Ledpin[1], HIGH);

    lcd.clear();
    analogWrite(motor, 50);
    lcd.setCursor(0, 0);
    hienthichuoi("Mode2-");
    delay(500);
  }
}
