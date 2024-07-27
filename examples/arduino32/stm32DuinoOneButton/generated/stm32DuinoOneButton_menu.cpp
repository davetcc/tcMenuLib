/*
    The code in this file uses open source libraries provided by thecoderscorner

    DO NOT EDIT THIS FILE, IT WILL BE GENERATED EVERY TIME YOU USE THE UI DESIGNER
    INSTEAD EITHER PUT CODE IN YOUR SKETCH OR CREATE ANOTHER SOURCE FILE.

    All the variables you may need access to are marked extern in this file for easy
    use elsewhere.
 */

// Generated for STM32Duino by TcMenu 4.3.0-SNAPSHOT on 2024-07-27T07:53:35.721721700Z.

#include <tcMenu.h>
#include "stm32DuinoOneButton_menu.h"
#include "../ThemeMonoInverse.h"
#include <Fonts/OpenSansRegular8pt.h>

// Global variable declarations
const  ConnectorLocalInfo applicationInfo = { "One Button", "4fe6e85d-2bbd-4d19-84e5-5d6746883028" };
HalStm32EepromAbstraction glBspRom;
EepromAuthenticatorManager authManager(4);
U8G2_SSD1306_128X64_NONAME_F_4W_HW_SPI gfx(U8G2_R0, PF13, PD15, PF12);
U8g2Drawable gfxDrawable(&gfx);
GraphicsDeviceRenderer renderer(30, applicationInfo.name, &gfxDrawable);
TcOneButtonHandler oneButtonHandler(USER_BTN, 250);

// Global Menu Item declarations
const char enumStrSettingsEnumProp_0[] = "Item1";
const char enumStrSettingsEnumProp_1[] = "Item2";
const char enumStrSettingsEnumProp_2[] = "Item3";
const char* const enumStrSettingsEnumProp[]  = { enumStrSettingsEnumProp_0, enumStrSettingsEnumProp_1, enumStrSettingsEnumProp_2 };
const EnumMenuInfo minfoSettingsEnumProp = { "EnumProp", 24, 0xffff, 2, NO_CALLBACK, enumStrSettingsEnumProp };
EnumMenuItem menuSettingsEnumProp(&minfoSettingsEnumProp, 0, nullptr, INFO_LOCATION_PGM);
const AnalogMenuInfo minfoSettingsIntProp = { "IntProp", 23, 0xffff, 10, NO_CALLBACK, 0, 1, "A" };
AnalogMenuItem menuSettingsIntProp(&minfoSettingsIntProp, 0, &menuSettingsEnumProp, INFO_LOCATION_PGM);
const BooleanMenuInfo minfoSettingsOption = { "Option", 22, 0xffff, 1, NO_CALLBACK, NAMING_TRUE_FALSE };
BooleanMenuItem menuSettingsOption(&minfoSettingsOption, false, &menuSettingsIntProp, INFO_LOCATION_PGM);
const SubMenuInfo minfoSettings = { "Settings", 21, 0xffff, 0, NO_CALLBACK };
BackMenuItem menuBackSettings(&minfoSettings, &menuSettingsOption, INFO_LOCATION_PGM);
SubMenuItem menuSettings(&minfoSettings, &menuBackSettings, nullptr, INFO_LOCATION_PGM);
const AnalogMenuInfo minfoTemp = { "Temp", 20, 0xffff, 100, NO_CALLBACK, 0, 1, "%" };
AnalogMenuItem menuTemp(&minfoTemp, 0, &menuSettings, INFO_LOCATION_PGM);
const AnyMenuInfo minfoPressMe = { "Press Me", 19, 0xffff, 0, onPressMe };
ActionMenuItem menuPressMe(&minfoPressMe, &menuTemp, INFO_LOCATION_PGM);

void setupMenu() {
    // First we set up eeprom and authentication (if needed).
    setSizeBasedEEPROMStorageEnabled(false);
    glBspRom.initialise(0);
    menuMgr.setEepromRef(&glBspRom);
    authManager.initialise(menuMgr.getEepromAbstraction(), 150);
    menuMgr.setAuthenticator(&authManager);
    // Code generated by plugins and new operators.
    gfx.begin();
    renderer.setUpdatesPerSecond(5);
    switches.init(internalDigitalIo(), SWITCHES_POLL_EVERYTHING, false);
    menuMgr.initWithoutInput(&renderer, &menuPressMe);
    oneButtonHandler.start();
    renderer.setTitleMode(BaseGraphicalRenderer::NO_TITLE);
    renderer.setUseSliderForAnalog(false);
    renderer.enableTcUnicode();
    installMonoInverseTitleTheme(renderer, MenuFontDef(&OpenSansRegular8pt, 0), MenuFontDef(&OpenSansRegular8pt, 0), true);
}

