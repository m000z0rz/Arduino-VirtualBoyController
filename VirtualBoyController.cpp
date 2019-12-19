#include <Arduino.h>
#include <VirtualBoyController.h>

// A lot of this is adapted from https://github.com/raphnet/virtualboy_usb/blob/master/virtualboy.c

#define POV_ANGLE_NONE -1
#define POV_ANGLE_UP 0
#define POV_ANGLE_UPRIGHT 45
#define POV_ANGLE_RIGHT 90
#define POV_ANGLE_DOWNRIGHT 135
#define POV_ANGLE_DOWN 180
#define POV_ANGLE_DOWNLEFT 225
#define POV_ANGLE_LEFT 270
#define POV_ANGLE_UPLEFT 315


void VirtualBoyController::init(uint8_t _latchPin, uint8_t _clockPin, uint8_t _dataPin)
{
    latchPin = _latchPin;
    clockPin = _clockPin;
    dataPin = _dataPin;

    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, INPUT_PULLUP);

    digitalWrite(latchPin, LOW);
    digitalWrite(clockPin, HIGH);

    delayMicroseconds(10);
}

void VirtualBoyController::update()
{
    // shift in data
    _pressed = 0;

    digitalWrite(latchPin, HIGH);
	delayMicroseconds(12);
    digitalWrite(latchPin, LOW);

    // read 16 bits into _pressed
    for (int i=0; i<16; i++)
    {
        delayMicroseconds(6);
        digitalWrite(clockPin, LOW);

        _pressed <<= 1;
        if (!digitalRead(dataPin)) { _pressed |= 1; }

        delayMicroseconds(6);
        digitalWrite(clockPin, HIGH);
    }

    _pressed = _pressed & 0xFFFC; // mask out the last two bits that are never set

    // determine which buttons changed this update
    _down = _pressed & ~_lastPressed;
    _up = ~_pressed & _lastPressed;

    _lastPressed = _pressed;
}

bool VirtualBoyController::pressed(uint8_t button)
{
    return _pressed & (1 << button);
}

bool VirtualBoyController::up(uint8_t button)
{
    return _up & (1 << button);
}

bool VirtualBoyController::down(uint8_t button)
{
    return _down & (1 << button);
}

int VirtualBoyController::leftDpadHatAngle()
{
    return _hatAngle(VBOY_LUP, VBOY_LLEFT, VBOY_LDOWN, VBOY_LRIGHT);
}

int VirtualBoyController::rightDpadHatAngle()
{
    return _hatAngle(VBOY_RUP, VBOY_RLEFT, VBOY_RDOWN, VBOY_RRIGHT);
}

int VirtualBoyController::_hatAngle(uint8_t bup, uint8_t bleft, uint8_t bdown, uint8_t bright)
{
    uint16_t mask = (1 << bup) | (1 << bleft) | (1 << bdown) | (1 << bright);

    if (pressed(bup))
    {
        if (pressed(bleft))
        {
            return POV_ANGLE_UPLEFT;
        } else if (pressed(bright)) {
            return POV_ANGLE_UPRIGHT;
        } else {
            return POV_ANGLE_UP;
        }
    } else if (pressed(bdown)) {
        if (pressed(bleft))
        {
            return POV_ANGLE_DOWNLEFT;
        } else if (pressed(bright)) {
            return POV_ANGLE_DOWNRIGHT;
        } else {
            return POV_ANGLE_DOWN;
        }
    } else if (pressed(bleft)) {
        return POV_ANGLE_LEFT;
    } else if (pressed(bright)) {
        return POV_ANGLE_RIGHT;
    }

    return POV_ANGLE_NONE;
}
