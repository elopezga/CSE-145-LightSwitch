# Milestone Log

## Milestone 1
#### Solder ESP8266 to adaptor for easy breadboard prototyping

* Soldered adaptor on ESP2866 for easy prototyping
* Connected ESP2866 to my computer via USB.
* 
<img src="https://github.com/elopezga/CSE-145-LightSwitch/blob/master/Log/P_20160511_005205.jpg" data-rotate="90"/>

## Milestone 2
#### Interface Arduino and ESP8266 communication
- Hardware
- Software

## Milestone 3
#### Connect ESP8266 WiFi chip to Internet network

## Milestone 4
#### Light-switching mechanism on Arduino board

## Milestone 5
#### TCP connection from ESP8266 to ThingSpeak

## Milestone 6
#### Android Application
The core functionality for the Android application is completed. The Android application communicates directly to the ThingSpeak
server through the ThingSpeak channel and API. The form of communication takes place through HTTP requests. The
application initiates a GET request to the server to grab the current state of the light every second. If the button is pressed, 
an GET request is sent (per ThingSpeak API) to change the state of the light.

<p align="center">
  <img src="https://github.com/elopezga/CSE-145-LightSwitch/blob/master/Log/screen1.gif"/>
</p>
On launch of the application, the current state of the light is obtained to inform the user of the status of the light.
A '0' indicates that the light is off, while a '1' indicates that the light is on.



<p align="center">
  <img src="https://github.com/elopezga/CSE-145-LightSwitch/blob/master/Log/screen2.gif"/>
</p>
Clicking the button creates an HTTP GET request to change the state of the light. If its on, then it gets turned off, and visa-versa.



<p align="center">
  <img src="https://github.com/elopezga/CSE-145-LightSwitch/blob/master/Log/screen3.gif"/>
</p>
A limitation to the ThingSpeak server is that it cannot handle rapid state-change requests. The user has to wait
some time until the ThingSpeak server is ready to accept requests. As such, the user is prompted with a "working" display.



.
