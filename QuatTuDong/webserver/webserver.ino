#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DHT.h>
#include <Wire.h>

#define motor D6
#define in4 D7
#define in3 D8
#define DHTPIN D5
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

const char *ssid = "Galaxy A235A0C";
const char *password = "12345678";

ESP8266WebServer server(80);

boolean autoMode = false;

void handleRoot() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  String html = "<html style='font-family: Arial, Helvetica, sans-serif; margin: 0px auto; text-align: center;'>";
  html += "<head><title> WEBSERVER </title>";
  html += "</head>";
  html += "<body style='margin-top: 50px;'>";

  html += "<div style='background-color: darkred; width: 400px; border-radius: 10px; margin: auto; padding: 10px;'>";
  html += "<H1 style='color: white; margin: 30px 30px;'> ESP8266 WEBSERVER </H1>";
  html += "<H2 style='color: white; margin-bottom: 30px;'> Nhom hoc phan IOT </H2>";
  html += "<H3 style='color: white; margin-bottom: 50px;'> He thong dieu khien quat tu dong </H3>";
  html += "<B style='font-size: 20px; color: white; margin-bottom: 10px;'> Temperature: ";
  html += "<span id='temperature'>" + String(temperature) + "</span> *C</B><br>";
  html += "<B style='font-size: 20px; color: white; margin-bottom: 10px;'> Humidity: ";
  html += "<span id='humidity'>" + String(humidity) + "</span> %</B><br></B><br><br>";

  html += "<button type='button' id='autoBtn' class='mode-btn' style='width: 70px; border: none; color: #191970; padding: 10px 20px; text-decoration: none; font-size: 15px; margin: 0px auto 35px; cursor: pointer; border-radius: 4px; margin-right: 10px;' onclick='motorControl(\"auto\")'> auto </button>";

  html += "<br><br>";
  html += "<button type='button' id='mode1Btn' class='mode-btn' style='width: 70px; border: none; color: #191970; padding: 10px 20px; text-decoration: none; font-size: 15px; margin: 0px auto 35px; cursor: pointer; border-radius: 4px; margin-right: 10px;' onclick='motorControl(\"mode1\")'> mode-1 </button>";
  html += "<button type='button' id='mode2Btn' class='mode-btn' style='width: 70px; border: none; color: #191970; padding: 10px 20px; text-decoration: none; font-size: 15px; margin: 0px auto 35px; cursor: pointer; border-radius: 4px; margin-right: 10px;' onclick='motorControl(\"mode2\")'> mode-2 </button>";
  html += "<button type='button' id='mode3Btn' class='mode-btn' style='width: 70px; border: none; color: #191970; padding: 10px 20px; text-decoration: none; font-size: 15px; margin: 0px auto 35px; cursor: pointer; border-radius: 4px; margin-right: 10px;' onclick='motorControl(\"mode3\")'> mode-3 </button>";
  html += "<button type='button' id='offBtn' class='mode-btn' style='width: 70px; border: none; color: #191970; padding: 10px 20px; text-decoration: none; font-size: 15px; margin: 0px auto 35px; cursor: pointer; border-radius: 4px;' onclick='motorControl(\"off\")'> motor off </button>";

  html += "<br><br>";
  html += "<button type='button' id='refreshBtn' class='mode-btn' style='width: 120px; border: none; color: #191970; padding: 10px 20px; text-decoration: none; font-size: 15px; cursor: pointer; border-radius: 4px;' onclick='updateSensorData()'> Refresh Data </button>";

  html += "<script>";
  html += "function motorControl(command) {";
  html += "  var xhttp = new XMLHttpRequest();";
  html += "  xhttp.open('GET', '/motor?command=' + command, true);";
  html += "  xhttp.onreadystatechange = function() {";
  html += "    if (this.readyState == 4 && this.status == 200) {";
  html += "      resetButtonColors();"; // Đặt lại màu của tất cả các nút
  html += "      document.getElementById(command + 'Btn').style.backgroundColor = '#800080';"; // Đặt màu nền cho nút đã được nhấn
  html += "    }";
  html += "  };";
  html += "  xhttp.send();";
  html += "}";
  html += "function resetButtonColors() {";
  html += "  document.getElementById('autoBtn').style.backgroundColor = null;";
  html += "  document.getElementById('mode1Btn').style.backgroundColor = null;";
  html += "  document.getElementById('mode2Btn').style.backgroundColor = null;";
  html += "  document.getElementById('mode3Btn').style.backgroundColor = null;";
  html += "  document.getElementById('offBtn').style.backgroundColor = null;";
  html += "}";
  html += "function updateSensorData() {";
  html += "  var xhttp = new XMLHttpRequest();";
  html += "  xhttp.open('GET', '/update-sensor-data', true);";
  html += "  xhttp.onreadystatechange = function() {";
  html += "    if (this.readyState == 4 && this.status == 200) {";
  html += "      var data = JSON.parse(this.responseText);";
  html += "      document.getElementById('temperature').innerHTML = data.temperature;";
  html += "      document.getElementById('humidity').innerHTML = data.humidity;";
  html += "    }";
  html += "  };";
  html += "  xhttp.send();";
  html += "}";
  html += "</script>";

  html += "</body>";
  html += "</html>";

  server.send(200, "text/html", html);
}

void motorControl() {
  String command = server.arg("command");

  if (command == "auto") {
    autoMode = !autoMode;
    if (autoMode) {
      autoMotor();
    }
  } else if (autoMode) {
    autoMode = false;
  }

  if (!autoMode) {
    if (command == "mode1") {
      analogWrite(motor, 150);
    } else if (command == "mode2") {
      analogWrite(motor, 200);
    } else if (command == "mode3") {
      analogWrite(motor, 250);
    } else if (command == "off") {
      analogWrite(motor, 0);
    }
  }

  Serial.println("Che do dieu khien: " + command);
  Serial.println();
  server.send(200, "text/plain", "OK");
}

void updateSensorData() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  String data = "{\"temperature\": " + String(temperature) + ", \"humidity\": " + String(humidity) + "}";
  server.send(200, "application/json", data);
}

void setup() {
  Serial.begin(9600);
  dht.begin();

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  pinMode(motor, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWriteRange(255);
  analogWriteFreq(1000);

  server.on("/", HTTP_GET, handleRoot);
  server.on("/motor", HTTP_GET, motorControl);
  server.on("/update-sensor-data", HTTP_GET, updateSensorData);

  server.begin();
  Serial.println("Server started");
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  delay(1000);
}

void autoMotor() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  Serial.println("");
  Serial.print("Nhiệt độ: ");
  Serial.print(temperature);
  Serial.println(" *C");
  Serial.print("Độ ẩm: ");
  Serial.print(humidity);
  Serial.println(" %");

  if (round(temperature) > 15 and round(temperature) < 25) {
    analogWrite(motor, 130);
    Serial.println("Che do motor: 1");
  } else if (round(temperature) >= 25 and round(temperature) < 30) {
    analogWrite(motor, 150);
    Serial.println("Che do motor: 2");
  } else if (round(temperature) >= 30) {
    analogWrite(motor, 200);
    Serial.println("Che do motor: 3");
  } else if (temperature < 15) {
    analogWrite(motor, 0);
    Serial.println("Che do motor: tat");
  }
  delay(1000);
}

void loop() {
  server.handleClient();
}