#ifndef VirtualBoyController_H
#define VirtualBoyController_H

// bits 0 and 1 are not defined
#define VBOY_A       2 // A button
#define VBOY_B       3 // B button
#define VBOY_R       4 // Right trigger
#define VBOY_L       5 // Left trigger
#define VBOY_RUP     6 // Right d-pad, up button
#define VBOY_RRIGHT  7 // Right d-pad right button
#define VBOY_LRIGHT  8 // Left d-pad, right button
#define VBOY_LLEFT   9 // Left d-pad, left button
#define VBOY_LDOWN  10 // Left d-pad, down button
#define VBOY_LUP    11 // Left d-pad, up button
#define VBOY_START  12 // Start button
#define VBOY_SELECT 13 // Select button
#define VBOY_RLEFT  14 // Right d-pad, left button
#define VBOY_RDOWN  15 // Right d-pad, down button


class VirtualBoyController
{
    public:
        void init(uint8_t latchPin, uint8_t clockPin, uint8_t dataPin);
        void update();
        bool pressed(uint8_t button); // true if the given button was held this update()
        bool up(uint8_t button); // true if the given button was just released this update()
        bool down(uint8_t button); // true if the given button was just pressed this update()

        int leftDpadHatAngle();
        int rightDpadHatAngle();

    private:
        uint8_t latchPin;
        uint8_t clockPin;
        uint8_t dataPin;

        uint16_t _pressed;
        uint16_t _lastPressed;
        uint16_t _changed;
        uint16_t _up;
        uint16_t _down;

        int _hatAngle(uint8_t bup, uint8_t bleft, uint8_t bdown, uint8_t bright);
};

#endif