# N64_bluetooth
Turn an N64 controller into a bluetooth HID device

You will need:

Nintendo 64 Controller
Arduino Uno
Sparkfun Protoshield
Sparkfun BlueSMiRF HID module
Battery with Barrel Jack connector (standard 9V battery will work)
Hook-up wire
Heatshrink
Soldering iron, etc.

Instructions:

1) Solder the Sparkfun Protoshield together. Instructions on SparkFun website.
2) Solder a stackable header to the BlueSMiRF connector on the protoshield.
3) Solder header pins to the BlueSMiRF HID module so that it mates with the protoshield. Do not solder it directly to the shield.
4) Stick 3 lengths of hookup wire into the controller's connector. I recommend bending the hookup wire to ensure good contact. 
5) Use heatshrink to hold the hookup wire in place.
6) Solder the hookup wire to 3.3V, GND and D2. There should be a wiring diagram included with this project.
7) Upload the sketch to the Arduino Uno.
8) Disconnect USB, apply battery.
9) Pair and use like any Bluetooth gamepad. :)