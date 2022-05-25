#include <Servo.h>
#include "Adafruit_LTR390.h"
#include <DHT11.h>
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
// Addr, En, Rw, Rs, d4, d5, d6, d7, backlighpin, polarity

Adafruit_LTR390 ltr = Adafruit_LTR390();

// constants won't change
const int MOTION_SENSOR_PIN = 7; // Arduino pin connected to motion sensor's pin
const int SERVO_PIN         = 4; // Arduino pin connected to servo motor's pin

Servo tap_servo;

// variables will change:
int angle = 0;          // the current angle of servo motor
int lastMotionState;    // the previous state of motion sensor
int currentMotionState; // the current state of motion sensor
int sensor_pin = 5;
int tap_servo_pin = 4 ;
int val;
int pin = A0;
DHT11 dht11(pin);


double Fahrenheit(double celsius) {
return ((double)(9 / 5) * celsius) + 32;
}

double Kelvin(double celsius) {
return celsius + 273.15;
}


void setup(){
  pinMode(sensor_pin,INPUT);
  // rain sensor pin
  tap_servo.attach(tap_servo_pin);
  // servo
lcd.begin(16, 2);
lcd.backlight();
lcd.clear();
lcd.print("Humidity & temp");
delay(100);
lcd.clear();
lcd.print("Starting.....");
delay(100);


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

  Serial.begin(9600);                // initialize serial
  pinMode(MOTION_SENSOR_PIN, INPUT); // set arduino pin to input mode
  tap_servo.attach(SERVO_PIN);           // attaches the servo on pin 9 to the servo object

  tap_servo.write(angle);
  currentMotionState = digitalRead(MOTION_SENSOR_PIN);
}

void loop(){
  val = digitalRead(sensor_pin);
  lastMotionState    = currentMotionState;             // save the last state
  currentMotionState = digitalRead(MOTION_SENSOR_PIN); // read new state
int err;
float temp, humi;

  if ((val==0) || UV data>= 6 )  //rain sensor sense 0 raindrop
  {tap_servo.write(180);
  }
  else
  {tap_servo.write(0);
    }
    if ((err = dht11.read(humi, temp)) == 0)


  if (currentMotionState == LOW) { // pin state change: LOW -> HIGH
    Serial.println("Motion detected!");
    tap_servo.write(0);
  }
  else
  if (currentMotionState == HIGH) { // pin state change: HIGH -> LOW
    Serial.println("Motion stopped!");
   tap_ servo.write(180);
  }

{
lcd.clear();
delay(100);
lcd.setCursor(0, 0);
lcd.print("Temp");
lcd.setCursor(0, 1);
lcd.print("Humidity");
lcd.setCursor(9, 0);
lcd.print(temp);
lcd.print(" C");
lcd.setCursor(9, 1);
lcd.print(humi);
lcd.print(" %");
delay(100);
}
{
  if (ltr.newDataAvailable()) {
      Serial.print("UV data: ");
      Serial.print(ltr.readUVS());
  }
}
}
