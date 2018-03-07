# WeMos Wifi Robot using L298N

Wifi-enabled devices are all the rage these days. I've decided to swap out my Arduino Uno + Sensor shield for a WeMos D1 Mini to control an L298N FWD robot.

Read more in the full tutorial on [Learn Robotics Blog](https://www.learnrobotics.org/blog)

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a robot.

### Prerequisites

Software

```
* Arduino IDE
* ESP8266 library
* ESP8266 Board Manager
* WeMos D1 Mini DRIVER: https://wiki.wemos.cc/downloads
* Web browser (for commanding robot)
* WeMos_D1_Mini_Wifi_Robot sketch (.ino)
```

Hardware

```
* Arduino Robot Chassis w/ motors (2WD or 4WD is fine)
* L298N motor controller
* Battery Pack (I used a 7.4V battery pack)
* Jumper Wires
* WeMos D1 Mini controller
* Micro usb cable
* Breadboard
```

[Contact Me to buy my Create Robot](https://www.learnrobotics.org/contact#form)


### Building & Electronic Wiring
You'll need to build the robot chassis prior to starting this tutorial. When you're finished, pick up here with the Electronic Wiring.

1. Connect the Motor Leads from the DC Motors to the Motor A and Motor B +/- terminals on the L298N. Motor pin 1 is red +, pin 2 is black -, pin 3 is black -, and pin 4 is red +. Use the L298N diagram to see the #'d motor pins. If you have 2 sets of motors, attach both LEFT motors on one side, and RIGHT motors on the other side.
2. Attach Jumpers to pins ENA and ENB
3. Remove Jumper from power pin (this will keep your robot from moving while connected to your computer. Remove the jumper during unteathered operations.)
4. Connect the signal wires as follows:
	IN1 to D7
	IN2 to D6
	IN3 to D3
	IN4 to D4
5. Connect power (pins listed left to right, refer to diagram):
	6-9V power = +Red from battery
	GND = -Battery & GND on WeMos D1 Mini
	5V power = 5V on WeMos D1 Mini

### Installing

Follow these steps to deploy this code on your robot.

1. Install [Arduino IDE](http://arduino.cc/downloads)
2. ESP8266 library: Sketch >> Include Library >> Manage Libraries >> Search for ESP8266com & install
3. Arduino Board Manager URL (Copy & paste in Arduino >> Preferences): http://arduino.esp8266.com/stable/package_esp8266com_index.json
4. Set board to WeMos D1 R2 & mini under Tools >> Board. 
5. Change baud rate to 115200 Tools >> Upload Speed >> 115200

Then change these lines to include your Network Name (ssid) and Network password (password):

```
// Replace with your network credentials
const char* ssid     = "yourssid";
const char* password = "yourpassword";
```

If you choose not to use my pins from the hardware wiring example, you'll need to update this part of the code with the pins you connected your wires to:

```
// Motor Inputs (INL=left in INR=right in)
const int INL1 = D7;
const int INL2 = D6;
const int INR1 = D3;
const int INR2 = D4;
```


## Deployment

Upload the code as you would any other Arduino Sketch, ensuring that you have the WeMos D1 R2 & mini board selected and the baud rate set to 115200.

Open the Serial Monitor and find your IP address. i.e. 192.168.X.XXX

Visit that URL on your internet browser.
You should see the Learn Robotics command page open up. 

### Robot Control
Click a command as if it was a remote controller. The robot will begin to move. 

Note: *Your computer or smart phone MUST be connected to the same network as the robot.*

**If you aren't tethered to your computer be sure you've added the jumper to the power pins.**


## Versioning

Versions will be updated as needed or upon request using this github repo.

## Authors

* **Liz Miller** - *Initial work* - [Learn Robotics](https://www.learnrobotics.org)

## License

Wemos D1 mini + L298N wifi-enabled Robot Controller by Learn Robotics LLC is licensed under a Creative Commons Attribution-ShareAlike 4.0 International License.

## Acknowledgments

* Thanks to the following for helping me structure this project and providing useful resources!
* [Random Nerd Tutorials](https://randomnerdtutorials.com/esp8266-web-server/)
* [L298N Wiring Diagram](http://www.14core.com/wiring-driving-the-l298n-h-bridge-on-2-to-4-dc-motors/)
* [Wemos-D1-Mini-RC](https://github.com/wassgha/WemosD1MiniRC)
* [esp8266-robot](https://github.com/openhomeautomation/esp8266-robot)
