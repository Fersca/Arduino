const int sensorPin = A0;
const int motorPin = 7;
char data = 0;            //Variable for storing received data
int regando=0;

void setup() {
  pinMode(motorPin, OUTPUT);
  pinMode(13, OUTPUT);  //Sets digital pin 13 as output pin
  Serial.begin(9600);
}
 
void loop() 
{
   int humedad = analogRead(sensorPin);
   Serial.print("humedad: ");
   Serial.println(humedad);
   Serial.print("Regando: ");
   Serial.println(regando);
   
   //Verifica si no está regando
   if (!regando){

     //Si no está regando pero está muy seco, empieza a regar
     if(humedad > 550)
     { 
        digitalWrite(motorPin, HIGH);
        Serial.println("prende motor");
        regando = 1;  
     } else {
        //digitalWrite(motorPin, LOW);
        Serial.println("sigue apagado");        
        //regando = 0; 
     }
   }
   else {
     //Si está regando y ya está bastante húmedo, deja de regar
     if(humedad < 300)
     { 
        digitalWrite(motorPin, LOW);
        Serial.println("apaga motor");
        regando = 0;  
     } else {
        //digitalWrite(motorPin, HIGH);
        //Serial.println("sigue prendido");          
        //regando = 1;     
     }
   }

   //Si recibe una señal del teléfono, riega
   /*
   if(Serial.available() > 0){
      data = Serial.read();
      digitalWrite(motorPin, HIGH);
      Serial.println("BLUETOOTH ON");
      regando = 1;      
   }
  */
   delay(2000);   
}
