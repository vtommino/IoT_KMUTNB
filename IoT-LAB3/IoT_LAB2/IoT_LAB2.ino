#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <BH1750FVI.h>

int pinled_green = 26;

BH1750FVI LightSensor(BH1750FVI::k_DevModeContLowRes);

unsigned long interval = 5000;
unsigned long previousMillis = 0;

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
  pinMode(pinled_green, OUTPUT);
  delay(250); // wait for the OLED to power up

  LightSensor.begin();

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

}

void loop() {
  // put your main code here, to run repeatedly:

  delay(2000);
  int lux = LightSensor.GetLightIntensity();

  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(SH110X_WHITE); 
  oled.setCursor(0, 30);
  oled.println("Welcome to OLED SH1106");
  oled.println("Light: " + String(lux, 1) + "ux");
    
  // oled.display();

  Serial.println(lux);
  
  if(lux > 100){
    digitalWrite(pinled_green, HIGH);
  }else{
    digitalWrite(pinled_green, LOW);
  }
  
}
