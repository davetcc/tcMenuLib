/*
    The code in this file uses open source libraries provided by thecoderscorner

    DO NOT EDIT THIS FILE, IT WILL BE GENERATED EVERY TIME YOU USE THE UI DESIGNER
    INSTEAD EITHER PUT CODE IN YOUR SKETCH OR CREATE ANOTHER SOURCE FILE.

    All the variables you may need access to are marked extern in this file for easy
    use elsewhere.
 */

#ifndef MENU_GENERATED_CODE_H
#define MENU_GENERATED_CODE_H

#include <Arduino.h>
#include <tcMenu.h>

#include "tcMenuU8g2.h"
#include "tcMenuBLERemoteConnector.h"

// all variables that need exporting
extern U8G2_SSD1306_128X64_NONAME_F_SW_I2C gfx;
extern GraphicsDeviceRenderer renderer;

// all menu item forward references.
extern AnalogMenuItem menuAnalogReadingsOutputPWM;
extern FloatMenuItem menuAnalogReadingsInA0;
extern BackMenuItem menuBackAnalogReadings;
extern SubMenuItem menuAnalogReadings;
extern FloatMenuItem menuAccelerometerAccelZ;
extern FloatMenuItem menuAccelerometerAccelY;
extern FloatMenuItem menuAccelerometerAccelX;
extern FloatMenuItem menuAccelerometerMagZ;
extern FloatMenuItem menuAccelerometerMagY;
extern FloatMenuItem menuAccelerometerMagX;
extern BackMenuItem menuBackAccelerometer;
extern SubMenuItem menuAccelerometer;
extern AnalogMenuItem menuBPressure;
extern AnalogMenuItem menuHumidity;
extern AnalogMenuItem menuTemp;
extern const ConnectorLocalInfo applicationInfo;

// Callback functions must always include CALLBACK_FUNCTION after the return type
#define CALLBACK_FUNCTION

void CALLBACK_FUNCTION onPWMChanged(int id);

void setupMenu();

#endif // MENU_GENERATED_CODE_H
