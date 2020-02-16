/*
    The code in this file uses open source libraries provided by thecoderscorner

    DO NOT EDIT THIS FILE, IT WILL BE GENERATED EVERY TIME YOU USE THE UI DESIGNER
    INSTEAD EITHER PUT CODE IN YOUR SKETCH OR CREATE ANOTHER SOURCE FILE.

    All the variables you may need access to are marked extern in this file for easy
    use elsewhere.
*/

#include <tcMenu.h>
#include <ledFlashNoRemote_menu.h>

// Global variable declarations

const PROGMEM ConnectorLocalInfo applicationInfo = { "LED Blink", "86bb814a-5b77-45eb-8050-7dba18617635" };
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
LiquidCrystalRenderer renderer(lcd, 16, 2);

// Global Menu Item declarations

const ActionMenuInfo PROGMEM minfoSaveLEDState = { "Save LED state", 3, 0xFFFF, 0, onSaveState };
ActionMenuItem menuSaveLEDState(&minfoSaveLEDState, false, NULL);
const AnalogMenuInfo PROGMEM minfoA0Volts = { "A0Volts", 2, 0xFFFF, 1024, NULL, 0, 200, "V" };
AnalogMenuItem menuA0Volts(&minfoA0Volts, 0, &menuSaveLEDState);
const BooleanMenuInfo PROGMEM minfoBuiltInLED = { "BuiltIn LED", 1, 2, 1, onLedChange, NAMING_ON_OFF };
BooleanMenuItem menuBuiltInLED(&minfoBuiltInLED, false, &menuA0Volts);


// Set up code

void setupMenu() {
    switches.initialise(ioUsingArduino(), true);
    menuMgr.initForEncoder(&renderer, menuBuiltInLED, 2, 3, A3);
    lcd.setIoAbstraction(ioUsingArduino());
    lcd.begin(16, 2);
    lcd.configureBacklightPin(10);
    lcd.backlight();


}