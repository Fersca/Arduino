/*
 * Tutorial 6a: Introduction to Servo Motors
 * 
 * Simply rotates your server from 0 to 180 degrees and back.
 *
 * The circuit:
 * - Brown pin to ground
 * - Red pin to 5v
 * - Orange pin to digital pin 9
 *
 * by BARRAGAN <http://barraganstudio.com>
 * modified 14 August 2013
 * by Blaise Jarrett
 *
 * This example code is in the public domain.
 *
 * Derivative work from:
 * http://arduino.cc/en/Tutorial/Sweep
 *
 */

#include <Servo.h> 
// include the library

const int buttonPin = 2;     // the number of the pushbutton pin
const int buttonSet = 3;     // the number of the pushbutton pin

const int ledPin    = 13;    // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
int setState = 0;            // variable for reading the pushbutton status
long horas = 0;
int beforeState = LOW;
long miliSegundos = 0;
long multiplicador = 36000; //60*60*10
int horasRiego = 0;

// the Orange pin is connected to digital pin 9
int servoPin = 9;

// create servo object to control our servo
// a maximum of eight servo objects can be created 
Servo myServo;

const int ledRojo     = 4;    // the number of the LED pin
const int ledVerde    = 5;    // the number of the LED pin
const int ledAmarillo = 6;    // the number of the LED pin
const int ledAzul     = 7;    // the number of the LED pin
const int ledBlanco   = 8;    // the number of the LED pin
 
void setup() 
{

    // initialize the LED pin as an output:
    pinMode(ledPin, OUTPUT);

    pinMode(ledRojo, OUTPUT);
    pinMode(ledVerde, OUTPUT);
    pinMode(ledAmarillo, OUTPUT);
    pinMode(ledAzul, OUTPUT);
    pinMode(ledBlanco, OUTPUT);
    
    // initialize the pushbutton pin as an input:
    pinMode(buttonPin, INPUT);
    pinMode(buttonSet, INPUT);
    
    // attaches the servo on pin 9 to the servo object 
    myServo.attach(servoPin);

    // move the servo to degree 180
    myServo.write(180);

}

void regar(){
      // turn LED on:
      digitalWrite(ledPin, HIGH);

      //Prende los leds
      prenderLeds();
      
      // move the servo to degree 0
      myServo.write(70);

      // wait for it to move
      delay(10000);

      myServo.write(10);

      delay(10000);

      // move the servo to degree 180
      myServo.write(180);

      //Apaga los leds
      apagarLeds();

      miliSegundos = 0;
}

void apagarLeds(){
      digitalWrite(ledRojo, HIGH);
      digitalWrite(ledVerde, HIGH);
      digitalWrite(ledAmarillo, HIGH);
      digitalWrite(ledAzul, HIGH);
      digitalWrite(ledBlanco, HIGH);  
}

void prenderLeds(){
      digitalWrite(ledRojo, LOW);
      digitalWrite(ledVerde, LOW);
      digitalWrite(ledAmarillo, LOW);
      digitalWrite(ledAzul, LOW);
      digitalWrite(ledBlanco, LOW);  
}

void procesaLeds(){
    
    if (horas == 0) {
      digitalWrite(ledRojo, HIGH);
      digitalWrite(ledVerde, HIGH);
      digitalWrite(ledAmarillo, HIGH);      
      digitalWrite(ledAzul, HIGH);
      digitalWrite(ledBlanco, HIGH);
    }
    
    if (horas == 1) {
      digitalWrite(ledRojo, LOW);
      digitalWrite(ledVerde, HIGH);
      digitalWrite(ledAmarillo, HIGH);
      digitalWrite(ledAzul, HIGH);
      digitalWrite(ledBlanco, HIGH);

    }

    if (horas == 2) {
      digitalWrite(ledRojo, HIGH);
      digitalWrite(ledVerde, LOW);
      digitalWrite(ledAmarillo, HIGH);
      digitalWrite(ledAzul, HIGH);
      digitalWrite(ledBlanco, HIGH);

    }

    if (horas == 3) {
      digitalWrite(ledRojo, HIGH);
      digitalWrite(ledVerde, HIGH);
      digitalWrite(ledAmarillo, LOW);
      digitalWrite(ledAzul, HIGH);
      digitalWrite(ledBlanco, HIGH);

    }

    if (horas == 4) {
      digitalWrite(ledRojo, HIGH);
      digitalWrite(ledVerde, HIGH);
      digitalWrite(ledAmarillo, HIGH);
      digitalWrite(ledAzul, LOW);
      digitalWrite(ledBlanco, HIGH);
    }

    if (horas == 5) {
      digitalWrite(ledRojo, HIGH);
      digitalWrite(ledVerde, HIGH);
      digitalWrite(ledAmarillo, HIGH);
      digitalWrite(ledAzul, HIGH);
      digitalWrite(ledBlanco, LOW);
    }

    if (horas == 6){
      horas = 0;
    }

}

void loop()
{

    // read the state of the pushbutton value:
    buttonState = digitalRead(buttonPin);

    // read the state of the pushbutton value:
    setState = digitalRead(buttonSet);

    if (setState == HIGH && beforeState == LOW) {
      miliSegundos=0;
      horas++;
      beforeState = HIGH;
    }
    
    if (setState == LOW && beforeState == HIGH) {
      beforeState = LOW;
    }

    procesaLeds();
    
    // check if the pushbutton is pressed.
    // if it is, the buttonState is HIGH:
    if (buttonState == HIGH) {
      regar();
    } else {
      // turn LED off:
      digitalWrite(ledPin, LOW);
    }

    
    //un segundo entre cada ciclo
    delay(100);

    miliSegundos++;

    if (horas==0)
      horasRiego=0;
    if (horas==1)
      horasRiego=1;
    if (horas==2)
      horasRiego=3;
    if (horas==3)
      horasRiego=6;
    if (horas==4)
      horasRiego=12;
    if (horas==5)
      horasRiego=24;

    if(horasRiego>0 && miliSegundos>=(horasRiego*multiplicador)) {
      regar();
    } 
    
}
