#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <splash.h>

c

#include <Bounce2.h>
#include <Wire.h>   
#include <DHT.h>

#define DHTTYPE DHT11

// Thong so WiFi nha ban
const char ssid[] PROGMEM = "vantoan";
const char password[] PROGMEM = "toan8888";

// Tao server
WiFiServer server(80);

Bounce debouncer = Bounce(); // Tạo một đối tượng Bounce

#define sensor 7
#define motor 6 //10
#define in3 5   //9 
#define in4 4   //8

int Led1 = 13;
int Led2 = 11;

int button = 10;
int Mode = 0;  // Gán giá trị ban đầu cho Mode
int previousMode = 0; // Biến lưu trữ Mode trước đó
int previousMysensor = 0;  // Sử dụng biến này để lưu trạng thái trước đó của mysensor

const int DHTPIN = 3;       // sử dụng chân số 6
DHT dht(DHTPIN, DHTTYPE, 15);

Adafruit_SSD1306 display(4);

void displayTemperature(int temperature) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print(F("Nhiet do: "));
    display.print(temperature);
    display.print(F(" *C"));
    display.display();
}

void setup() {
    Serial.begin( 115200);
    delay(10);

    // Ket noi toi mang WiFi
    Serial.println();
    Serial.println();
    Serial.print("Ket noi toi mang ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("Da ket noi WiFi");

    // Khoi dong server
    server.begin();
    Serial.println("Khoi dong Server");
  
    // In ra dia chi IP
    Serial.println(WiFi.localIP());

    // Try reducing buffer size
    if (!display.begin( 0x3C, -1)) {
        Serial.println(F("Không tìm thấy màn hình OLED"));
        
       
for (;;);
    }
}

void loop() {
    // Kiem tra khi co client ket noi
    WiFiClient client = server.available();
    if (!client) {
        return;
    }

    // Doi client gui ket noi
    Serial.println("Co mot client moi ket noi xem du lieu");
    while (!client.available()) {
        delay(1);
    }

    int t = dht.readTemperature();  // nhiệt độ

    // Doc dong dau tien cua yeu cau gui len.
    String req = client.readStringUntil('\r');
    Serial.println(req);
    client.flush();

    // Chuan bi tao web de phan hoi
    String s = F("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
    s += F("<head>");
    s += F("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
    s += F("<meta http-equiv=\"refresh\" content=\"60\" />");
    s += F("<script src=\"https://code.jquery.com/jquery-2.1.3.min.js\"></script>");
    s += F("<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.4/css/bootstrap.min.css\">");
    s += F("<style>body{font-size: 24px;} .voffset {margin-top: 30px;}</style>");
    s += F("</head>");
  
    s += F("<div class=\"container\">");
    s += F("<h1>Theo doi nhiet do va do am</h1>");
    s += F("<div class=\"row voffset\">");
    s += F("<div class=\"col-md-3\">Nhiet do: </div><div class=\"col-md-3\">");
    s += String(t);
    s += F("</div>");
    s += F("</div>");

    // Gui phan hoi toi client (o day la giao dien web)
    client.print(s);
    delay(1);
    Serial.println("Client da thoat");

    // Sau khi nhan duoc thong tin thi se tu dong ngat ket noi 
    if (isnan(t)) {
        Serial.println(F("Failed to read from DHT sensor!"));
        return;
    }

    displayTemperature(t);
}