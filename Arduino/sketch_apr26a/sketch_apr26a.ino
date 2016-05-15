#include <SoftwareSerial.h>
/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;
boolean DEBUG = true;

SoftwareSerial ESP2866(10, 11); // Specify RX and TX pins on Arduino (TX, RX) as serial
String GETSTR = "GET /channels/111722/fields/1/last.txt?api_key=SE5ZR5HILIB7FF4T HTTP/1.1\r\nHost: api.thingspeak.com:80\r\nContent-Type: text/html; charset=utf-8\r\n\r\n\r\n";
// the setup routine runs once when you press reset:

void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
 
  Serial.begin(9600);  
  ESP2866.begin(9600);
  
  Serial.println("Reseting ESP2866");
  //ESP2866.println("AT+RST"); 
  //ESP2866.println("AT+RST");
  //Serial.println("Connecting to network");
  //connectWifi("cozy", "juanisdumb");
  //waitForResponse("OK");
  //connectToHost("api.thingspeak.com");
  //waitForResponse("OK");

  //Serial.println("Resetting ESP2866");
  //checkForResponse( "OK", sendCommandLN("AT+RST");
  //connectWifi("cozy","juanisdumb");

  
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
  if( !sendCommand("AT+CIPSTART=4,\"TCP\",\"api.thingspeak.com\",80\r\n", "OK", "ERROR") ){
    Serial.println("Something went wrong!");
    //return;
  }

  
  if( !sendCommand("AT+CIPSEND=4,"+String(GETSTR.length()-2)+"\r\n", "OK", "ERROR") ){
    Serial.println("Something went wrong!");
    //return;
  }
  //delay(5000);
  ESP2866.print(GETSTR);
  readReceive();
  readReceive();

  /*+IPD,4,5:0*/
  /*
  if( !sendCommand(GETSTR, "SEND OK", "+IPD,4,5:0") ){
    Serial.println("Something went wrong!");
    //return;
  }*/

  /*
  if( !sendCommand("AT+CIPCLOSE=4\r\n", "OK", "ERROR") ){
    Serial.println("Something went wrong!");
    //return;
  }*/
  
  /*
  delay(1000);
  
  
  //sendCommand("GET /channels/111722/fields/1/last.txt?api_key=SE5ZR5HILIB7FF4T\r\n\r\n");

  
 //ESP2866.println("AT+CIPSEND=4,"+String(GETstr.length()));
  //delay(5000);
  //ESP2866.print(GETstr);
  //readReceive();
  
  
  //Serial.println("AT+CIPSEND=4,"+String(GETstr.length()));
  /*
  if(ESP2866.find(">")){
    delay(7000);
    ESP2866.print(GETstr);
    Serial.print(GETstr);
    while(ESP2866.available()){
      Serial.write(ESP2866.read());
    }
  }else{
    //sendCommand("AT+CIPCLOSE");
  }
  delay(16000);

  
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


//@TODO: flush command for esp?

void connectWifi(String Ssd, String Pass){
  Serial.println("Software reset");
  //checkForResponse( "OK", sendCommandLN("AT+RST"));
  if( !sendCommandLN("AT+RST", "OK", "ERROR") ){
    Serial.println("Something went wrong!");
    return;
  }
  
  Serial.println("Setting WiFi mode to BOTH (3)");
  //checkForResponse( "OK", sendCommandLN("AT+CWMODE=3"));
  if( !sendCommandLN("AT+CWMODE=3", "OK", "ERROR") ){
    Serial.println("Something went wrong!");
    return;
  }
  
  Serial.println("Setting TCP/UDP connection mode to Multiple (1)");
  //checkForResponse( "OK", sendCommandLN("AT+CIPMUX=1"));
  if( !sendCommandLN("AT+CIPMUX=1", "OK", "ERROR") ){
    Serial.println("Something went wrong!");
    return;
  }

  // Connect to wifi network
  Serial.println("Connecting to " + Ssd);
  //sendCommand("AT+CWJAP=\""+Ssd+"\",\""+Pass+"\"");
  //checkForResponse( "OK", sendCommandLN("AT+CWJAP=\""+Ssd+"\",\""+Pass+"\""));
  //waitForResponse("OK");
  //delay(10000);
  if( !sendCommandLN("AT+CWJAP=\""+Ssd+"\",\""+Pass+"\"", "OK", "ERROR") ){
    Serial.println("Something went wrong!");
    return;
  }

  //Serial.println("Getting connection status");
  //sendCommand("AT+CIFSR");

  Serial.println("Ready to work!");
}

void connectToHost(String host){
  Serial.println("Connecting to " + host);
  //String response = sendCommand("AT+CIPSTART=4,\"TCP\",\""+host+"\",80");

  ESP2866.println("AT+CIPSTART=4,\"TCP\",\""+host+"\",80");
  delay(10000);

  //sendCommand("GET /channels/111722/fields/1/last.txt?api_key=SE5ZR5HILIB7FF4T\r\n");
  /*
  if(Serial.find("Error")){
    Serial.println("Could not connect");
  }*/
  
  //@TODO
  /*
  while( response ){
    response = sendCommand("AT+CIPSTART=4,\"TCP\",\""+host+"\",80");
  }*/
  
  
}

int find_text(String needle, String haystack) {
  int foundpos = -1;
  for (int i = 0; i <= haystack.length() - needle.length(); i++) {
    if (haystack.substring(i,needle.length()+i) == needle) {
      foundpos = i;
    }
  }
  return foundpos;
}

// Send and receive command. Sends with \r\n
String sendCommandLN(String cmd){
  ESP2866.println(cmd);
  delay(5000);
  //return readReceive();
  return readUntil("OK", "ERROR");
}


/*
 * Send command with \r\n attached at the end. It will return true if str1 is found in the response.
 * Otherwise, it will return false.
 * str1, str2 used to read response of esp from command until either of those two strings are found.
 */
boolean sendCommandLN(String cmd, String str1, String str2){
  if( DEBUG ){
    Serial.println(cmd);
  }
  ESP2866.println(cmd);
  return checkForResponse( str1, readUntil(str1, str2) );
}

boolean sendCommand(String cmd, String str1, String str2){
  if( DEBUG ){
    Serial.println(cmd);
  }
  ESP2866.print(cmd);
  return checkForResponse( str1, readUntil(str1, str2) );
}

// Send and receive command. Does not append \r\n
String sendCommand(String cmd){
  ESP2866.print(cmd);
  //delay(5000);
  //return readReceive();
  return readUntil("OK", "ERROR");
}

// Read next output stream of esp2866 when available
String readReceive(){
  String response = "";
  char charRead;
  while( ESP2866.available() ){
    //response = response + ESP2866.read();
    //Serial.write( ESP2866.read() );
    charRead = ESP2866.read();
    response.concat(charRead);
  }
  
  Serial.println(response);
  return response;
}

// Used to keep checking esp2866 response until its operation is done. This is usually
// represented by a success string such as OK, or fail string such as ERROR
String readUntil(String str1, String str2){
  String response = "";
  char charRead;

  // Keep checking if esp2866 output is available (and consequently read it) until on of the two
  // target strings is found
  while( find_text(str1, response) == -1 && find_text(str2, response) == -1 ){
    // Read response. Note that in long pauses from esp, available will return false. That is why
    // there is an outer loop so that ALL of the output is recorded
    while( ESP2866.available() ){
      charRead = ESP2866.read();
      response.concat(charRead);
    }
  }


  if( DEBUG ){
    Serial.println(response);
  }
  
  return response;
}

boolean waitFor(String prompt){
  int timeout = 20000; // Timeout after 20 seconds
  int tick = 0;

  int strlength = prompt.length();
  char buff[strlength];
  prompt.toCharArray(buff, strlength);
  
  while( !Serial.find(buff) ){
    tick += 1000;
    Serial.print(".");
    if( tick > timeout ){
      Serial.println("Timeout");
      return false;
    }
    delay(1000);
  }
  Serial.println("");
  return true;
}

void waitForResponse(String response){
  String espResponse = readReceive();
  
  if( find_text(response, espResponse) != -1 ){
    Serial.println("OK to proceed");
  }else{
    Serial.println("Something went wrong");
  }
}

boolean checkForResponse(String target, String refstr){
  if( find_text(target, refstr) != -1 ){
    Serial.println("OK TO PROCEED");
    return true;
  }else{
    Serial.println("SOMETHING WENT WRONG");
    return false;
  }
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
