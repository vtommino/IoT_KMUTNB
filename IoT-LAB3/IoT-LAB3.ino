#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include "DHTesp.h"

int DHT_PIN = 15;
int pinled_red = 25;
int pinled_green = 26;

unsigned long interval = 5000;
unsigned long previousMillis = 0;

DHTesp dhtSensor; 

/* Uncomment the initialize the I2C address , uncomment only one, If you get a totally blank screen try the other*/
#define i2c_Address 0x3c //initialize with the I2C addr 0x3C Typically eBay OLED's
//#define i2c_Address 0x3d //initialize with the I2C addr 0x3D Typically Adafruit OLED's

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1   //   QT-PY / XIAO
Adafruit_SH1106G oled = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(250); // wait for the OLED to power up
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);

  // initialize OLED display with address 0x3C for 128x64
  if (!oled.begin(i2c_Address, true)) {
    Serial.println(F("SH1106G allocation failed"));
    while (true);
    delay(2000);         // wait for initializing          
  }

  oled.clearDisplay();          // clear display
  oled.setTextSize(1);          // text size
  oled.setTextColor(SH110X_WHITE);     // text color
  oled.setCursor(0, 10);
  oled.println("Hello, OLED !.");
  oled.display();

  Serial.begin(115200);
  pinMode(pinled_red, OUTPUT);
  pinMode(pinled_green, OUTPUT);


}

void loop() {
  // put your main code here, to run repeatedly:
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(SH110X_WHITE);
  oled.setCursor(0, 0);
  oled.println("Welcome to OLED SH1106");
  TempAndHumidity data = dhtSensor.getTempAndHumidity();
  oled.println("Humidity: " + String(data.humidity, 1) + "%");
  oled.println("Temp: " + String(data.temperature, 2) + "C");

  oled.setTextSize(2);
  oled.setCursor(0, 30);
  oled.println("Good Day!");
  oled.display();
  delay(2000);

  if(data.temperature>28){
    digitalWrite(pinled_green, HIGH);
  }else{
    digitalWrite(pinled_green, LOW);
  }

  if(data.humidity>65){
    digitalWrite(pinled_red, HIGH);
  }else{
    digitalWrite(pinled_red, LOW);
  }




}