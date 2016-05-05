#include <SoftwareSerial.h>

/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;

SoftwareSerial ESP2866(10, 11); // Specify RX and TX pins on Arduino (TX, RX) as serial

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
 
  Serial.begin(9600);  
  ESP2866.begin(9600);
  
  //Serial.println("Reseting ESP2866");
  //delay(2000);
  //ESP2866.println("AT+RST");
  Serial.println("Connecting to network");
  connectWifi("cozy", "juanisdumb");
}

// the loop routine runs over and over again forever:
void loop() {

  if( Serial.available() ){
    ESP2866.write( Serial.read() );
  }

  if( ESP2866.available() ){
    Serial.write( ESP2866.read() );
  }
  
  /*
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  Serial.println("LED ON");
  delay(1000);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  Serial.println("LED OFF");
  delay(1000);               // wait for a second
  
  Serial.println("Reseting ESP 2866");
  delay(2000);
  monitor.println("AT+RST");
  */
  /*
  toESP2866.listen();
  toESP2866.println("AT+CWMODE?");
  delay(500);
  //Serial.println(String(toESP2866.read()));
  //Serial.println(readLine(toESP2866));
  while( toESP2866.available() >0 ){
    Serial.print("Response: ");
    Serial.write(toESP2866.read());
  }
  Serial.println("Done");*/
}


void connectWifi(String Ssd, String Pass){
  Serial.println("Setting WiFi mode to BOTH (3)");
  sendCommand("AT+CWMODE=3");

  Serial.println("Software reset");
  sendCommand("AT+RST");
  
  Serial.println("Setting TCP/UDP connection mode to Multiple (1)");
  sendCommand("AT+CIPMUX=1");

  // Connect to wifi network
  Serial.println("Connecting to " + Ssd);
  sendCommand("AT+CWJAP=\""+Ssd+"\",\""+Pass+"\"");

  Serial.println("Getting connection status");
  sendCommand("AT+CIFSR");

  Serial.println("Ready to work!");
}

void connectToHost(String host){
  Serial.println("Connecting to " + host);

  
  String response = sendCommand("AT+CIPSTART=4,\"TCP\",\""+host+"\",80");

  //@TODO
  /*
  while( response ){
    response = sendCommand("AT+CIPSTART=4,\"TCP\",\""+host+"\",80");
  }*/
  
  
}

void sendCommand(String cmd){
  ESP2866.println(cmd);
  delay(5000);
  readReceive();
  Serial.println("Done");
}

String readReceive(){
  String response = "";
  while( ESP2866.available() ){
    response = response + ESP2866.read();
    //Serial.write( ESP2866.read() );
  }
  Serial.write( response );
  return response;
}


/*
String readLine(SoftwareSerial mon){
  char c;
  String msg;
  String cstr;

  //mon.listen();
  /*
  do{
    c = mon.read();
    cstr = String(c);
    Serial.println(cstr);
    msg = msg + cstr;
    Serial.println(msg);
  } while (cstr!="\n");

  return msg;
}*/


// Send to android the GET data

// Send to thingspeak?

// Get to thingspeak
