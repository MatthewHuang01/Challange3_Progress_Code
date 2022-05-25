#include <Servo.h>

Servo myservo;

int pos = 0;    // variable to store the servo position

void setup() {

Serial.begin(9600);
  myservo.attach(4);  // attaches the servo on pin 4 to the servo object

}

void loop() {

 int analogValue = analogRead(A0);

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



}
