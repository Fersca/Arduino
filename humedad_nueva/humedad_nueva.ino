const int sensorPin = A0;

const int buttonPin = 2;
const int relayPin = 7;

//constantes del led de warning
const int waterPin = 5;
const int ledWaterPin = 3;

//Leds rango
const int led1 = 8;
const int led2 = 9;
const int led3 = 10;
const int led4 = 11;
const int led5 = 12;
const int led6 = 13;

int value;
int buttonState;
int switchState;
int humedad;

void setup() {
  pinMode(sensorPin,INPUT);
  pinMode(buttonPin,INPUT);
  pinMode(waterPin, INPUT);
  pinMode(relayPin ,OUTPUT);
  pinMode(ledWaterPin ,OUTPUT);

  pinMode(led1 ,OUTPUT);
  pinMode(led2 ,OUTPUT);
  pinMode(led3 ,OUTPUT);
  pinMode(led4 ,OUTPUT);
  pinMode(led5 ,OUTPUT);
  pinMode(led6 ,OUTPUT);
  
  Serial.begin(9600);
}
 
void loop() 
{

  bool hayAgua = chequeaAgua();

  if (hayAgua){
      chequeaHumedad();
    
      chequeaBoton();
      
      activaBomba(buttonState);    
  }
 
  delay(500);   
}

void chequeaHumedad(){
  humedad = analogRead(sensorPin);
  Serial.print("humedad: ");
  Serial.println(humedad);

  if (humedad<904)  digitalWrite(led1, HIGH); else digitalWrite(led1, LOW);
  if (humedad<784)  digitalWrite(led2, HIGH); else digitalWrite(led2, LOW);
  if (humedad<664)  digitalWrite(led3, HIGH); else digitalWrite(led3, LOW);
  if (humedad<544)  digitalWrite(led4, HIGH); else digitalWrite(led4, LOW);
  if (humedad<424)  digitalWrite(led5, HIGH); else digitalWrite(led5, LOW);
  if (humedad<304)  digitalWrite(led6, HIGH); else digitalWrite(led6, LOW);  

  //Si está prendido el switch, no procesa la humedad
  if (switchState==HIGH)
    return;
  
  if (humedad<800 && buttonState==LOW){
    buttonState=HIGH;
    Serial.println("Prende Motor por temperatura");
  } else {
    if (humedad>900 && buttonState==HIGH){
      buttonState=LOW;
      Serial.println("Apaga Motor por temperatura");
    }    
  }
    
}

void chequeaBoton(){

   value = digitalRead(buttonPin);

   //Si está prendido cambia de estado
   if (value==HIGH){
      //Si estaba high lo pasa a low y sino, lo pasa a high
      if (buttonState==HIGH){
          buttonState=LOW;
          switchState=LOW;
          Serial.println("Apaga Motor por Switch");
      } else {
        
          buttonState=HIGH;
          switchState=HIGH;
          Serial.println("Prende Motor por Switch");
      }
   }  
}

bool chequeaAgua(){

   value = digitalRead(waterPin);

   //Si está apagado, prender led de warning
   if (value==LOW){
      digitalWrite(ledWaterPin, HIGH);
      Serial.println("Nivel de Agua Bajo");
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      digitalWrite(led5, LOW);
      digitalWrite(led6, LOW);           
      return false;
   } else {
      digitalWrite(ledWaterPin, LOW);    
      return true;
   }
}

void activaBomba(bool buttonState){
   if (buttonState == HIGH)
   {
      digitalWrite(relayPin, HIGH);
   }
   else
   {
      digitalWrite(relayPin, LOW);
   }  
}


