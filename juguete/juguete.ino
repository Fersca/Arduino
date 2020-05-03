/*
  Analog Input
 Demonstrates analog input by reading an analog sensor on analog pin 0 and
 turning on and off a light emitting diode(LED)  connected to digital pin 13.
 The amount of time the LED will be on and off depends on
 the value obtained by analogRead().

 The circuit:
 * Potentiometer attached to analog input 0
 * center pin of the potentiometer to the analog pin
 * one side pin (either one) to ground
 * the other side pin to +5V
 * LED anode (long leg) attached to digital output 13
 * LED cathode (short leg) attached to ground

 * Note: because most Arduinos have a built-in LED attached
 to pin 13 on the board, the LED is optional.


 Created by David Cuartielles
 modified 30 Aug 2011
 By Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/AnalogInput

 */

int sensorPin = A0;    // select the input pin for the potentiometer
int ledPin = 8;
int ledPin2 = 9;
int ledPin3 = 11;

int buzzer = 10;
int sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {
  Serial.begin(9600);
  // declare the ledPin as an OUTPUT:
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);  
  pinMode(ledPin3, OUTPUT);  
  pinMode(buzzer, OUTPUT);
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)

  if (sensorValue>800){
    digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)  
    digitalWrite(ledPin2, LOW);   // turn the LED on (HIGH is the voltage level)  
    digitalWrite(ledPin3, LOW);   // turn the LED on (HIGH is the voltage level)  
    tone(buzzer, 400);
    delay(100);

    digitalWrite(ledPin, LOW);   // turn the LED on (HIGH is the voltage level)  
    digitalWrite(ledPin2, HIGH);   // turn the LED on (HIGH is the voltage level)  
    digitalWrite(ledPin3, LOW);   // turn the LED on (HIGH is the voltage level)  
    tone(buzzer, 500);
    delay(100);

    digitalWrite(ledPin, LOW);   // turn the LED on (HIGH is the voltage level)  
    digitalWrite(ledPin2, LOW);   // turn the LED on (HIGH is the voltage level)  
    digitalWrite(ledPin3, HIGH);   // turn the LED on (HIGH is the voltage level)  
    tone(buzzer, 600);
    delay(100);

    digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)  
    digitalWrite(ledPin2, LOW);   // turn the LED on (HIGH is the voltage level)  
    digitalWrite(ledPin3, LOW);   // turn the LED on (HIGH is the voltage level)  
    tone(buzzer, 700);
    delay(100);

    digitalWrite(ledPin, LOW);   // turn the LED on (HIGH is the voltage level)  
    digitalWrite(ledPin2, HIGH);   // turn the LED on (HIGH is the voltage level)  
    digitalWrite(ledPin3, LOW);   // turn the LED on (HIGH is the voltage level)  
    tone(buzzer, 800);
    delay(100);

    digitalWrite(ledPin, LOW);   // turn the LED on (HIGH is the voltage level)  
    digitalWrite(ledPin2, LOW);   // turn the LED on (HIGH is the voltage level)  
    digitalWrite(ledPin3, HIGH);   // turn the LED on (HIGH is the voltage level)  
    tone(buzzer, 900);
    delay(100);
    
  } else {
    digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW   
    digitalWrite(ledPin2, LOW);    // turn the LED off by making the voltage LOW       
    digitalWrite(ledPin3, LOW);    // turn the LED off by making the voltage LOW       

    noTone(buzzer); 
  }                  


  
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(100);                       // wait for a second
  
}
