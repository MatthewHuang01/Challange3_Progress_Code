#include <Servo.h>
#include "Adafruit_LTR390.h"
#include <DHT11.h>
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
// Addr, En, Rw, Rs, d4, d5, d6, d7, backlighpin, polarity

Adafruit_LTR390 ltr = Adafruit_LTR390();

Servo tap_servo;

// variables will change:
int angle = 0;          // the current angle of servo motor
int sensor_pin = 5;
int tap_servo_pin = 4 ;
int val;
int pin = A0;
DHT11 dht11(pin);



void setup(){
  pinMode(sensor_pin,INPUT);
  // rain sensor pin
  tap_servo.attach(tap_servo_pin); 
  // servo
lcd.begin(16, 2);
lcd.backlight();
lcd.clear();
lcd.print("Humidity & temp");

lcd.clear();
lcd.print("Starting.....");



  Serial.begin(115200);
  Serial.println("Adafruit LTR-390 test");

  if ( ! ltr.begin() ) {
    Serial.println("Couldn't find LTR sensor!");
    while (1) delay(10);
  }
  Serial.println("Found LTR sensor!");

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

  ltr.setThresholds(100, 1000);
  ltr.configInterrupt(true, LTR390_MODE_UVS);

}

void loop(){
  val = digitalRead(sensor_pin);
 
int err;
float temp, humi;

  if ((val==0) || ltr.readUVS()>=10 )  
  {tap_servo.write(180);
  }
  else
  {tap_servo.write(0);
    }
    if ((err = dht11.read(humi, temp)) == 0)



{


lcd.setCursor(0, 0);
lcd.print("Temp     ");
lcd.setCursor(0, 1);
lcd.print("Humidity");
lcd.setCursor(9, 0);
lcd.print(temp);
lcd.print(" C");
lcd.setCursor(9, 1);
lcd.print(humi);
lcd.print(" %");
}
{
  if (ltr.newDataAvailable()) {
      Serial.print("UV data: "); 
      Serial.print(ltr.readUVS());
  }
}
}
