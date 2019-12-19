# Arduino-VirtualBoyController

A PlatformIO for reading and working with a Nintendo Virtual Boy controller

## Simple example
```
VirtualBoyController vboy;

void setup() {
  vboy.init(LATCH_PIN, CLOCK_PIN, DATA_PIN);
}

void loop() {
  vboy.update();

  if (vboy.down(VBOY_A)) // just pressed
  {
      Keyboard.press("a");
  } else if (vboy.up(VBOY_A)) // just released
  {
      Keyboard.release("a");
  }
}
```

## Initialization
Call `VirtualBoyController.init(latchPin, clockPin, dataPin)` in `setup()` with the appropriate pins.


## Getting controller state
Call `VirtualBoyController.update()` to read the controller state.

`VirtualBoyController.pressed(button)` returns true if the given button is held down as of the last update

`VirtualBoyController.down(button)` returns true only if the button was just pressed down as of the last update (and was not pressed before)

`VirtualBoyController.up(button)` returns true only if the butt was just released as of the last update (and was pressed before)

`VirtualBoyController.leftDpadHatAngle()` and `.rightDpadHatAngle()` return an int that can be used as a POV hat angle for `Joystick.hat()`

## Virtual boy buttons
*`VBOY_A` - A button
*`VBOY_B` - B button
*`VBOY_R` - Right trigger
*`VBOY_L` - Left trigger
*`VBOY_RUP` - Right d-pad, up button
*`VBOY_RRIGHT` - Right d-pad right button
*`VBOY_LRIGHT` - Left d-pad, right button
*`VBOY_LLEFT` - Left d-pad, left button
*`VBOY_LDOWN` - Left d-pad, down button
*`VBOY_LUP` - Left d-pad, up button
*`VBOY_START` - Start button
*`VBOY_SELECT` - Select button
*`VBOY_RLEFT` - Right d-pad, left button
*`VBOY_RDOWN` - Right d-pad, down button
