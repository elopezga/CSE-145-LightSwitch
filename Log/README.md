# Milestone Log

## Milestone 1 [Completed]
#### Solder ESP8266 to adaptor for easy breadboard prototyping
The ESP8266 WiFi chip has an unfortunate design that does not allow it to be easily used in prototype boards.
Fortunately, an adaptor exists which makes it easy to prototype. The only requirement is to solder the header
pins on the adaptor. After this, the ESP8266 is easily adaptable.

<a href="https://drive.google.com/open?id=0B8I6-MtRe_U0Q1JyajNyaHpvanM">Link to image of soldered adaptor for ESP8266</a>

## Milestone 2 [Completed]
#### Interface Arduino and ESP8266 communication
#####Hardware
I choose to use a prototype board to connect the ESP8226 and Arduino MC for quick and easy developing and debugging. An FTDI
is connected to the Arduino via header pins. This allows me to upload my program to the Arduino and debug it by seeing the
output on my computer.
<a href="https://drive.google.com/open?id=0B8I6-MtRe_U0bUNJX0drU1Vkekk">Link to hardware wiring</a>
#####Software
Since the Arduino is connected via USB, I am able to communicate with the ESP8266 directly. This means I can send AT commands
and the ESP8266 will respond. This is useful for debugging. 
<p align="center">
  <img src="https://github.com/elopezga/CSE-145-LightSwitch/blob/master/Log/Milestone2.gif"/>
</p>
The software loaded onto the Arduino sends automatically sends AT commands in a sequence that will connect the ESP8266 to
the home network, connect to the ThingSpeak server, and send and receive HTTP requests every couple of seconds on the
status of the light.

## Milestone 3 [Completed]
#### Connect ESP8266 WiFi chip to Internet network
Connecting to a home network is relatively simple once you can communicate with ESP8266 from the Arduino or computer.

```
AT+CWLAP
```

will list the access points available. You can connect to an access point by simply sending the command

```
AT+CWJAP="SSID","PASSWORD"
```

To insure that the ESP8266 has connected to the home network successfully, we can run the command

```
AT+CIFSR
```

This will return the IP address.

<p align="center">
  <img src="https://github.com/elopezga/CSE-145-LightSwitch/blob/master/Log/Milestone3.gif"/>
</p>

## Milestone 4
#### Light-switching mechanism on Arduino board

## Milestone 5 [Completed]
#### TCP connection from ESP8266 to ThingSpeak
In order to contact the ThingSpeak server and start sending HTTP request, the ESP8266 must first connect to it.
Sending the command

```
AT+CIPSTART="TCP","api.thingspeak.com",80
```

will connect the ESP8266 to the ThingSpeak HTTP server. Once connected, we can start sending HTTP requests by first, telling
the ThingSpeak server how many bytes of request we want to send, and finally, the actualy request string. The following two
commands describe how to tell the ESP8266 to do this.

```
AT+CIPSEND=[BYTES_TO_SEND]
```
<br>
<br>
```
GET /channel/[CHANNEL_ID]/fields/[FIELD_ID]/last.txt?api_key=[GET_KEY] HTTP/1.1\r\nHOST: api.thingspeak.com:80\r\nContent-Type: text/html; charset=utf-8\r\n\r\n\r\n
```

<p align="center">
  <img src="https://github.com/elopezga/CSE-145-LightSwitch/blob/master/Log/Milestone5.gif"/>
</p>

## Milestone 6 [Completed]
#### Android Application
The core functionality for the Android application is completed. The Android application communicates directly to the ThingSpeak
server through the ThingSpeak channel and API. The form of communication takes place through HTTP requests. The
application initiates a GET request to the server to grab the current state of the light every second. If the button is pressed, 
an GET request is sent (per ThingSpeak API) to change the state of the light.

<p align="center">
  <img src="https://github.com/elopezga/CSE-145-LightSwitch/blob/master/Log/screen1.gif" width="auto" height="480"/>
</p>
On launch of the application, the current state of the light is obtained to inform the user of the status of the light.
A '0' indicates that the light is off, while a '1' indicates that the light is on.



<p align="center">
  <img src="https://github.com/elopezga/CSE-145-LightSwitch/blob/master/Log/screen2.gif" width="auto" height="480"/>
</p>
Clicking the button creates an HTTP GET request to change the state of the light. If its on, then it gets turned off, and visa-versa.



<p align="center">
  <img src="https://github.com/elopezga/CSE-145-LightSwitch/blob/master/Log/screen3.gif" width="auto" height="480"/>
</p>
A limitation to the ThingSpeak server is that it cannot handle rapid state-change requests. The user has to wait
some time until the ThingSpeak server is ready to accept requests. As such, the user is prompted with a "working" display.



.
