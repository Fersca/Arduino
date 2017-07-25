const int sensorPin = A0;
const int motorPin = 7;
char data = 0;            //Variable for storing received data
 
void setup() {
  pinMode(motorPin, OUTPUT);
  pinMode(13, OUTPUT);  //Sets digital pin 13 as output pin
  Serial.begin(9600);
}
 
void loop() 
{
   int humedad = analogRead(sensorPin);
  
   if(humedad < 1000)
   { 
      digitalWrite(motorPin, HIGH);
      Serial.println("Encendido");  
   } else {
      digitalWrite(motorPin, LOW);
   }

   if(Serial.available() > 0)      // Send data only when you receive data:
   {
      data = Serial.read();        //Read the incoming data & store into data
      Serial.print(humedad);
      Serial.print("\n");
      digitalWrite(motorPin, HIGH);   //If value is 1 then LED turns ON
      delay(2000);
      digitalWrite(motorPin, LOW);    //If value is 0 then LED turns OFF
   }
   delay(2000);   
}
