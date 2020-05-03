#include <SoftwareSerial.h>
SoftwareSerial BT1(3, 2); // RX | TX

String ordenes[]=
    {  //"AT+RST",
       //"AT",
       //"AT+CWQAP",
       //"AT+CWMODE=3",
       "AT+CWJAP=\"Fibertel WiFi812\",\"0142697146\"",
       //"AT+CIFSR" ,
       "AT+CIPMUX=1", //puede manejar conexiones en paralelo       
       "AT+CIPSERVER=1,80",
       //"AT+CIPSERVER=0", //sale del modo server
       //"AT+CIPMUX=0", //ninguna conexion en paralelo
       //"AT+CIPSTO=300",
       "END"        // Para reconocer el fin de los comandos AT
    };

unsigned long time;
String linea;

void setup()
  {  
    //pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(19200);  //115200
    BT1.begin(19200);     //115200

    delay (1000);

    int index = 0;
    linea = "";
    
    while(ordenes[index] != "END"){  
        BT1.println(ordenes[index++]);
        time = millis();
        while (true){   
            String s = GetLineWIFI();
            if (s!= "") 
                Serial.println(s);
            if (s.startsWith("OK"))   
                break;
            if ((millis()-time)>8000){
                Serial.println("Time Out");
                break;
            }
        }
        Serial.println("....................");
    } 
    Serial.println("End Setup");
}

void loop() {  

  /*
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(100); 
  */
  if (Serial.available()){  
    char c = Serial.read();
    BT1.print(c);
  }

  linea = "";
  while (BT1.available()>0){
    char c = BT1.read();
    linea = linea + c;
    Serial.print(c);
  }

  String content = "{\"origin\":\"fersca\"}"; 

  if(linea.indexOf("fernando") > 0){
      Serial.println("Enviada Web Request");
      webserver(content);
  }

  if(linea.indexOf("postdata")>0) {
      Serial.println("Posteando Datos");
      String content = "{\"origin\":\"fersca\"}"; 
      httppost("/post","192.168.0.18",content);   
      Serial.println("Posteando Datos - fin"); 
      webserver(content);
  }
  
}

void http(String output){
    BT1.print("AT+CIPSEND=0,");              // AT+CIPSEND=0, num
    BT1.println(output.length());
    if (BT1.find(">")) {                     // Si recibimos la peticion del mensaje   
        Serial.println(output);
        BT1.println(output);                 //Aqui va el string hacia el WIFI 
        //delay(10);
        while (BT1.available()>0) { 
            if (BT1.find("SEND OK"))         // Busca el OK en la respuesta del wifi
                break; 
        }
    }
}

void webserver(String content) {

        http("HTTP/1.1 200 OK\r\n");
        http("Connection: keep-alive\r\n");
        http("Server: Fersca-Arduino\r\n");
        http("Content-Type: text/html; charset=utf-8\r\n");
        http("Content-Length: "+String(content.length())+"\r\n");
        http("Server: Fersca-Arduino\r\n");
        http("\r\n");
        http(content);
        delay(1);
        BT1.println("AT+CIPCLOSE=0");
    }

String GetLineWIFI(){
  
    String S = "";
    if (BT1.available()){
        char c = BT1.read(); 
        while (c!= '\n'){
            S = S + c;
            delay(25);
            if (BT1.available()) {
              c = BT1.read();
            } else {
              if (BT1.overflow()) {
                  Serial.println("SoftwareSerial overflow! 1");
                  S = "overflow";
              }
              break;
            }
        }
     } else {
        if (BT1.overflow()) {
            Serial.println("SoftwareSerial overflow! 2");
            S = S + "overflow";
        }            
     }
     return(S);
}


void httppost (String uri, String server, String data) {

    String command1 = "AT+CIPSTART=1,\"TCP\",\"" + server + "\",80"; //se pone el 1 porque usamos modo server con multiples conexiones y se indica que use la conexion 1 porque la cero es la del request de inicio

    Serial.println(command1);

    BT1.println(command1);//start a TCP connection.

    if(BT1.find("OK")) {
        Serial.println("TCP connection ready");
    } 
    
    delay(1000);
    
    String postRequest = "POST " + uri + " HTTP/1.0\r\n" + "Host: " + server + "\r\n" +
    "Accept: *" + "/" + "*\r\n" +
    "Content-Length: " + data.length() + "\r\n" +
    "Content-Type: application/json\r\n" +
    "Connection: keep-alive\r\n" + 
    
    "\r\n" + data;
    
    String sendCmd = "AT+CIPSEND=1,";//determine the number of caracters to be sent.
    
    BT1.print(sendCmd);
    BT1.println(postRequest.length());
    
    delay(500);
    
    if(BT1.find(">")) { 
        Serial.println("Sending.."); 
        BT1.print(postRequest);

        Serial.println(postRequest);
        
        if(BT1.find("SEND OK")) { 
            Serial.println("Packet sent");
            time = millis();
            while (true){   
                String s = GetLineWIFI();
                if (s.startsWith("overflow")){
                    break;
                }  
                if (s!= "") 
                    Serial.println(s);                
                if (s.startsWith("OK"))   
                    break;
                if ((millis()-time)>4000){
                    Serial.println("Time Out 1");
                    break;
                } 
            }
            
            // close the connection
            BT1.println("AT+CIPCLOSE=1");
            Serial.println("SENT --> AT+CIPCLOSE=1");
        }
    }
}

