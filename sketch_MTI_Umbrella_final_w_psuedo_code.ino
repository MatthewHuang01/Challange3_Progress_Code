#include <Servo.h>  //include library for servo
#include "Adafruit_LTR390.h"   //include library for UV sensor
#include <DHT11.h>  //include library for humidity & temperature sensor
#include <Wire.h>  //include library for LCD display
#include <LCD.h>  //include library for LCD display
#include <LiquidCrystal_I2C.h>  //include library for LCD display
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); // LCD module connections

Adafruit_LTR390 ltr = Adafruit_LTR390();

Servo tap_servo;

// variables will change:
int angle = 0;          // the current angle of servo motor
int sensor_pin = 5;     // Set digital pin 5 for rain sensor
int tap_servo_pin = 4 ;     // Set digital pin 4 for servo
int val;    //assign the value to rain sensor
int pin = A0;     // Set analog pin 0 for humidity & temperature sensor
DHT11 dht11(pin);



void setup(){
  pinMode(sensor_pin,INPUT);
  // Set digital pin 5 as input for rain sensor
  tap_servo.attach(tap_servo_pin); 
  // Connect to servo via digital pin 4
lcd.begin(16, 2);  // initialize the lcd
lcd.backlight();   //To Power ON the back light
lcd.clear();   //clear LCD
lcd.print("Humidity & temp");    //LCD prints "Humidity & temp"
lcd.clear();   //clear LCD
lcd.print("Starting.....");   //LCD prints "Starting"



  Serial.begin(115200);   // Opens serial port, sets data rate to 115200 bps
  Serial.println("Adafruit LTR-390 test");    // Run test for Adafruit LTR-390 UV sensor in Serial port

  if ( ! ltr.begin() ) {
    Serial.println("Couldn't find LTR sensor!");
    while (1) delay(10);
  }
  Serial.println("Found LTR sensor!");
// sets the UV sensor when this sketch was compiled

  ltr.setMode(LTR390_MODE_UVS);
  if (ltr.getMode() == LTR390_MODE_ALS) {
    Serial.println("In ALS mode");
  } else {
    Serial.println("In UVS mode");
  }
 
  ltr.setGain(LTR390_GAIN_3);
  Serial.print("Gain : ");
  switch (ltr.getGain()) {
    case LTR390_GAIN_1: Serial.println(1); break;
    case LTR390_GAIN_3: Serial.println(3); break;
    case LTR390_GAIN_6: Serial.println(6); break;
    case LTR390_GAIN_9: Serial.println(9); break;
    case LTR390_GAIN_18: Serial.println(18); break;
  }

  ltr.setResolution(LTR390_RESOLUTION_16BIT);
  Serial.print("Resolution : ");
  switch (ltr.getResolution()) {
    case LTR390_RESOLUTION_13BIT: Serial.println(13); break;
    case LTR390_RESOLUTION_16BIT: Serial.println(16); break;
    case LTR390_RESOLUTION_17BIT: Serial.println(17); break;
    case LTR390_RESOLUTION_18BIT: Serial.println(18); break;
    case LTR390_RESOLUTION_19BIT: Serial.println(19); break;
    case LTR390_RESOLUTION_20BIT: Serial.println(20); break;
  }

  ltr.setThresholds(100, 1000);    //set range of values for UV sensor reading
  ltr.configInterrupt(true, LTR390_MODE_UVS);

}

void loop(){
  val = digitalRead(sensor_pin);    // Get reading of rain sensor from digital pin 5
 
int err;
float temp, humi;    // Get reading of humidity & temperature sensor in continuous values
  if ((val==0) || ltr.readUVS()>=10 )    // if rain sensor detects water or UV sensor's reading is equal or more than 10
  {tap_servo.write(180);   // servo angle point to 180
  }
  else
  {tap_servo.write(0);   // Otherwise, servo angle point to 0
    }
    
    if ((err = dht11.read(humi, temp)) == 0)    // Get reading of humidty & temperature sensor
{
lcd.setCursor(0, 0);
lcd.print("Temp     ");   // LCD prints "Temp     "
lcd.setCursor(0, 1);
lcd.print("Humidity");   // LCD prints "Humidity"
lcd.setCursor(9, 0);
lcd.print(temp);   // LCD prints temperature reading from sensor
lcd.print(" C");   // LCD prints " C"
lcd.setCursor(9, 1);
lcd.print(humi);   // LCD prints humidty reading from sensor
lcd.print(" %");   // LCD prints " %"
}
{
  if (ltr.newDataAvailable()) {     // if UV sensor reads new data
      Serial.print("UV data: ");    //serial prints "UV data: "
      Serial.print(ltr.readUVS());   //serial prints UV level
  }
}
}
