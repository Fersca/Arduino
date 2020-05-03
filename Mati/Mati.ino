void setup(){

  Serial.begin(9600);
  
}

void loop(){

  int analogValue;

  analogValue = analogRead(A0);

  Serial.print("Luz: ");
  Serial.println(analogValue);

  if (analogValue > 800){
    tone(8,2000,300);
    delay(300);
    tone(8,1000,300);
    Serial.println("Mucha Luz");
  } 

  if (analogValue<300){
    tone(8,3000,300);
    delay(300);
    tone(8,1500,300);
    Serial.println("Poca luz");
  }

  
  delay(1000);
  
}

