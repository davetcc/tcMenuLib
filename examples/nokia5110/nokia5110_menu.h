/*
    The code in this file uses open source libraries provided by thecoderscorner

    DO NOT EDIT THIS FILE, IT WILL BE GENERATED EVERY TIME YOU USE THE UI DESIGNER
    INSTEAD EITHER PUT CODE IN YOUR SKETCH OR CREATE ANOTHER SOURCE FILE.

    All the variables you may need access to are marked extern in this file for easy
    use elsewhere.
 */

#ifndef MENU_GENERATED_CODE_H
#define MENU_GENERATED_CODE_H

#include <tcMenu.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "EthernetTransport.h"
#include <RemoteConnector.h>
#include <RuntimeMenuItem.h>
#include "tcMenuAdaFruitGfx.h"

// all define statements needed
#define TCMENU_USING_PROGMEM true
#define ENCODER_PIN_A 2
#define ENCODER_PIN_B 3
#define ENCODER_PIN_OK A3

// all variables that need exporting
extern Adafruit_PCD8544 gfx;
extern AdaFruitGfxMenuRenderer renderer;

// all menu item forward references.
extern IpAddressMenuItem menuIpAddress;
extern BackMenuItem menuBackConnectivity;
extern SubMenuItem menuConnectivity;
extern TextMenuItem menuTxt;
extern FloatMenuItem menuCurrent;
extern FloatMenuItem menuVoltsIn;
extern BackMenuItem menuBackStatus;
extern SubMenuItem menuStatus;
extern ActionMenuItem menuShutdownNow;
extern AnalogMenuItem menuDelay;
extern BooleanMenuItem menuPwrDelay;
extern BackMenuItem menuBackSettings;
extern SubMenuItem menuSettings;
extern EnumMenuItem menuOnAlm;
extern AnalogMenuItem menuKitchen;
extern AnalogMenuItem menuLiving;
extern AnalogMenuItem menuHall;
extern const ConnectorLocalInfo applicationInfo;

// Callback functions must always include CALLBACK_FUNCTION after the return type
#define CALLBACK_FUNCTION

void CALLBACK_FUNCTION onHallLight(int id);
void CALLBACK_FUNCTION onKitchenLight(int id);
void CALLBACK_FUNCTION onLivingRoomLight(int id);
void CALLBACK_FUNCTION onPowerDownDetected(int id);

void setupMenu();

#endif // MENU_GENERATED_CODE_H
