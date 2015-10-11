# Teensy-Fun

A collection of simple DIYs with the [Teensy] microcontroller. Most of the projects are based on the version 3.1 of the Teensy board.

## EvilMouse - Pentetration testing tilt mouse 

[Teensy] is a USB based HID controller and has the full capabilities of a programmable keyboard and a mouse. One of the coolest aspects of this is using Teensy as a penetration testing usb dongle. [Peensy], [Kautilya] & [PHUKD Lib] are some examples of this.

EvilMouse is a penetration testing device disguised as a tilt controlled mouse. Packaged as a mouse controller, it can be used in penetration tests where USB dongles are frowned upon.

### Pre-requisites

  - Teensy is good to go https://www.pjrc.com/teensy/tutorial.html
  - Accelerometer is calibrated http://codergirljp.blogspot.com/2014/05/adxl335-accelerometer-on-teensy-31.html
  - PHUKD library is installed http://www.irongeek.com/i.php?page=security/programmable-hid-usb-keystroke-dongle#Programming_examples_and_my_PHUKD_library
  
### Design & Function

  - Teensy 3.1 https://www.pjrc.com/teensy/teensy31.html#specs
  - Accelerometer ADXL335 https://www.sparkfun.com/products/9269
  - Pushbuttons https://www.sparkfun.com/products/97
  - Bread board https://www.sparkfun.com/products/112
  - Jumper wires https://www.sparkfun.com/products/11026
  
**evilMouse.ino** is a prototype of the design. It has the functionalilty of a tilt mouse with a couple of sample code executions for Windows and Mac using the [PHUKD Lib].

![evil-mouse-design](evil-mouse-design.JPG?raw=true "EvilMouse Design")

  - **Left** - Left click
  - **Middle/Toggle** - Middle click or a Toggle switch to turn ON/OFF mouse function
  - **Right** - Right click
  - **Win** - Will run commands on a Windows target
  - **Mac** - Will run commands on a Mac target

## More Teensy fun later...

[Teensy]: <https://www.pjrc.com/teensy/>
[Kautilya]: <https://github.com/samratashok/Kautilya>
[Peensy]: <https://www.offensive-security.com/offsec/advanced-teensy-penetration-testing-payloads/>
[PHUKD Lib]: <http://www.irongeek.com/i.php?page=security/programmable-hid-usb-keystroke-dongle>

