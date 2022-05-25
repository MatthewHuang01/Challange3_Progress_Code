#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04

#include <Servo.h>
#include <DHT11.h>
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
// Addr, En, Rw, Rs, d4, d5, d6, d7, backlighpin, polarity

Servo myservo;

int pos = 0;    // variable to store the servo position

long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

int pin = A0;
DHT11 dht11(pin);


double Fahrenheit(double celsius) {
return ((double)(9 / 5) * celsius) + 32;
}

double Kelvin(double celsius) {
return celsius + 273.15;
}

void setup() {
lcd.begin(16, 2);
lcd.backlight();
lcd.clear();
lcd.print("Humidity & temp");
delay(3000);
lcd.clear();
lcd.print("Starting.....");
delay(3000);

 pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");


Serial.begin(9600);
  myservo.attach(4);  // attaches the servo on pin 4 to the servo object


}


void loop() {
int err;


 int analogValue = analogRead(A1);

  Serial.print("Analog reading: ");
  Serial.print(analogValue);   // the raw analog reading

  // We'll have a few threshholds, qualitatively determined
  if (analogValue < 10) {
    Serial.println(" - Dark");
  } else if (analogValue < 200) {
    Serial.println(" - Dim");
  } else if (analogValue < 500) {
    Serial.println(" - Light");
  } else if (analogValue < 800) {
    Serial.println(" - Bright");
  } else {
    Serial.println(" - Very bright");
  }

  delay(500);

 if (analogValue >= 500) {    //photoresistor value higher than 500
 //assuming UV reached an unbearable level, servo moves, umbrella opens

    myservo.write (180);
    delay (50);
 }
    else {

  myservo.write(0);
  delay(50);

  }


float temp, humi;
if ((err = dht11.read(humi, temp)) == 0)
{
lcd.clear();
delay(500);
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
delay(10000);
}
else
{
lcd.println();
lcd.print("Error No :");
lcd.print(err);
lcd.println();
}

 // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}
