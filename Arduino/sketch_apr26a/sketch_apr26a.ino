#include <SoftwareSerial.h>

/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;

SoftwareSerial toESP2866(10, 11); // Specify RX and TX pins on Arduino (RX, RX) as serial

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  monitor.begin(9600);
  Serial.begin(9600);  
  
  Serial.println("Reseting ESP2866");
  delay(2000);
  toESP2866.println("AT+RST");
}

// the loop routine runs over and over again forever:
void loop() {
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
}

void connectWifi(){
  Serial.println("Setting WiFi mode to BOTH (3)");
  String cmd = "AT+CWMODE:3";
  toESP2866.println(cmd);
  delay(1000);
  Serial.println("Done");
  
  Serial.println("Setting TCP/UDP connection mode to Multiple (1)");
  toESP2866.println("AT+CIPMUX=1");
  delay(1000);
  Serial.println("Done");

  // Connect to wifi network
  cmd = "AT+CWJAP=\"SSD\",\"PASS\"";  
  
}

// Send to android the GET data

// Send to thingspeak?

// Get to thingspeak
