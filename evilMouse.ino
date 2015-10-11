/***
	EvilMouse:	Mouse (using Teensy 3.1 and ADXL335) that can Pwn the system it is connected to.
	
	Function:	First (30), second (27) and third (24) button: Mouse (left, middle/toggle, right) click 
				Fourth (20) and fifth (17) button: Pwn with EvilMouse
				
	Version:	v0.1	
***/

#include <Bounce.h>
#include <phukdlib.h>

// led pin
const int ledPin = LED_BUILTIN;

// Teensy 3.1 Analog pins for the X, Y, Z outputs of the Accelerometer
const int xInput = 14; // A0 , board: 13
const int yInput = 15; // A1 , board: 12
const int zInput = 16; // A2 , board: 11

// left, middle, right click buttons
const int lClickPin = 2; // board: 30
const int rClickPin = 4; // board: 24
Bounce lClickButton = Bounce(lClickPin, 10);
Bounce rClickButton = Bounce(rClickPin, 10);
const int mClickPin = 3; // board: 27 // middle click - repurposed for mouse toggle
Bounce mClickButton = Bounce(mClickPin, 10);
boolean mouseOFF = true;


// Control buttons to launch Pwn with EvilMouse
// pwn Windows and Mac
const int pwnWinPin = 11; // board: 13
const int pwnMacPin = 12; // board: 14
Bounce pwnWinButton = Bounce(pwnWinPin, 10);  // 10 ms debounce
Bounce pwnMacButton = Bounce(pwnMacPin, 10);  // 10 ms debounce

byte pwnWinStatus = 0;
byte pwnMacStatus = 0;

// Calibrated Min/Max Raw Ranges:
const int xRawMin = 407;
const int xRawMax = 611;
 
const int yRawMin = 402;
const int yRawMax = 605;
 
const int zRawMin = 421;
const int zRawMax = 623;

// screen size
const int screenX = 1440; 
const int screenY = 900;

// raw values
int rawX = 0;
int rawY = 0;
int rawZ = 0;

// mapped values
int moveX = 0;
int moveY = 0;
int moveZ = 0;

// mapped Min/Max range
int moveMin = -20; // about 1/10th of Raw delta
int moveMax = 20;

void setup() 
{
  // manually configure screen size and move to center
  // Mouse.screenSize(screenX, screenY, true);
  // Mouse.moveTo(screenX/2, screenY/2);
	
  // initialize pwn buttons
  pinMode(pwnWinPin, INPUT_PULLUP);
  pinMode(pwnMacPin, INPUT_PULLUP);
  // initialize mouse buttons
  pinMode(lClickPin, INPUT_PULLUP);
  pinMode(mClickPin, INPUT_PULLUP);
  pinMode(rClickPin, INPUT_PULLUP);
  // initialize led
  pinMode(ledPin, OUTPUT);
	
}
 
void loop()
{
  // update all buttons
  pwnWinButton.update();
  pwnMacButton.update();
  lClickButton.update();
  rClickButton.update();
  mClickButton.update();
  
  // Comment this 'if' for middle click and set mouseOFF = true;
  // toggle mouse functions ON-OFF
  if (mClickButton.risingEdge())
  {
    mouseOFF = (mouseOFF == true)?false:true;
  }
  	
  // mouseOFF inidicator
  digitalWrite(ledPin, LOW);
  
  if (!mouseOFF)
  {  
    // mouseON indicator
    digitalWrite(ledPin, HIGH);
	
    // start mouse functions
    delay(10);

    // setup variables to track button state changes
    boolean anyChange = false;
    byte left=0;
    byte middle=0;
    byte right=0;

    // get a raw reading
    rawX = analogRead(xInput);
    rawY = analogRead(yInput);
    rawZ = analogRead(zInput);

    // map to a moveable reading
    moveX = map(rawX, xRawMin, xRawMax, moveMin, moveMax);
    moveY = map(rawY, yRawMin, yRawMax, moveMin, moveMax);
    moveZ = map(rawZ, zRawMin, zRawMax, moveMin, moveMax);

    // With Constrain
    // moveX = map(constrain(rawX,xRawMin,xRawMax), xRawMin, xRawMax, moveMin, moveMax);
    // moveY = map(constrain(rawY,yRawMin,yRawMax), yRawMin, yRawMax, moveMin, moveMax);
    // moveZ = map(constrain(rawZ,zRawMin,zRawMax), zRawMin, zRawMax, moveMin, moveMax);			
    // wearable re-mapping
    // moveY = moveX;
    // moveX = moveZ;
	
    // move cursor
    Mouse.move(-moveX, moveY);
	
    // Mouse actions
    // press
    if (lClickButton.fallingEdge())
    {
      left = 1;
      anyChange = true;
    }
    if (mClickButton.fallingEdge())
    {
      middle = 1;
      anyChange = true;
    }	
    if (rClickButton.fallingEdge())
    {
      right = 1;
      anyChange = true;
    }
    // release
    if (lClickButton.risingEdge())
    {
      left = 0;
      anyChange = true;
    }
    /* Uncomment for middle click function
    if (mClickButton.risingEdge())
    {
      middle = 0;
      anyChange = true;
    }
    */
    if (rClickButton.risingEdge())
    {
      right = 0;
      anyChange = true;
    }
    // if any changes, update the Mouse buttons 
    if (anyChange)
    {
      Mouse.set_buttons(left, middle, right);
    }
  }
  
  // Evil stuff
    
  // pwn Windows
  // press 
  if (pwnWinButton.fallingEdge())
  {
    pwnWinStatus++;  	
  }
  // release
  if (pwnWinButton.risingEdge())
  {
    pwnWinStatus++;  	
  }
  if (pwnWinStatus == 2)
  {  
    // run bar command
    CommandAtRunBarMSWIN("notepad.exe");
    delay (1000);
    Keyboard.print("I took something and you’ll never find out - Good Bye!!");
    delay (3000);  
    // minimize terminal
    ShrinkCurWin();        
    // reset pwnbutton state
    pwnWinStatus = 0;
  }
 
  // pwn Mac
  // press
  if (pwnMacButton.fallingEdge())
  {
    pwnMacStatus++;
  }
  // release
  if (pwnMacButton.risingEdge())
  {
    pwnMacStatus++;
  }
 
  if (pwnMacStatus == 2)
  {
    // run command on terminal
    CommandAtNewTerminal("/usr/bin/who -a");
    // minimize terminal
    ShrinkCurWinOSX();  
    
    // run spotlight command
    CommandAtRunBarOSX("textedit");
    delay (1000);
    Keyboard.print("I took something and you’ll never find out - Good Bye!!");
    delay (3000);  
    // minimize terminal
    ShrinkCurWinOSX();        
    // reset pwnbutton state
    pwnMacStatus = 0;
  }	
}
