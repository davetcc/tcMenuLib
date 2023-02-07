/*
    The code in this file uses open source libraries provided by thecoderscorner

    DO NOT EDIT THIS FILE, IT WILL BE GENERATED EVERY TIME YOU USE THE UI DESIGNER
    INSTEAD EITHER PUT CODE IN YOUR SKETCH OR CREATE ANOTHER SOURCE FILE.

    All the variables you may need access to are marked extern in this file for easy
    use elsewhere.
 */

#include <tcMenu.h>
#include "stm32OledEncoder_menu.h"
#include "ThemeMonoInverse.h"

// Global variable declarations
const  ConnectorLocalInfo applicationInfo = { "Demo mbed", "f5325e26-a7f6-40ff-876e-47afa06df532" };
TcMenuRemoteServer remoteServer(applicationInfo);
HalStm32EepromAbstraction glBspRom;
EepromAuthenticatorManager authManager(6);
Adafruit_SSD1306_Spi gfx(spi, PD_15, PF_12, PF_13, 64, 128, SSD_1306);
AdafruitDrawable gfxDrawable(&gfx);
GraphicsDeviceRenderer renderer(30, applicationInfo.name, &gfxDrawable);
MbedEthernetInitialiser mbedEthInitialisation(3333);
MBedEthernetTransport ethernetTransport;
TagValueRemoteServerConnection ethernetConnection(ethernetTransport, mbedEthInitialisation);

// Global Menu Item declarations
RENDERING_CALLBACK_NAME_INVOKE(fnEditRtCall, textItemRenderFn, "Edit", -1, NO_CALLBACK)
TextMenuItem menuEdit(fnEditRtCall, "", 16, 16, NULL);
const AnalogMenuInfo minfoCommits = { "Commits", 15, 0xffff, 32767, NO_CALLBACK, 0, 1, "" };
AnalogMenuItem menuCommits(&minfoCommits, 0, &menuEdit, INFO_LOCATION_PGM);
const char pgmStrAuthenticatorText[] = { "Authenticator" };
EepromAuthenticationInfoMenuItem menuAuthenticator(pgmStrAuthenticatorText, NO_CALLBACK, 19, NULL);
const char pgmStrIoTMonitorText[] = { "IoT Monitor" };
RemoteMenuItem menuIoTMonitor(pgmStrIoTMonitorText, 18, &menuAuthenticator);
RENDERING_CALLBACK_NAME_INVOKE(fnIPRtCall, ipAddressRenderFn, "IP", -1, NO_CALLBACK)
IpAddressMenuItem menuIP(fnIPRtCall, IpAddressStorage(127, 0, 0, 1), 14, &menuIoTMonitor);
const SubMenuInfo minfoConnectivity = { "Connectivity", 13, 0xffff, 0, NO_CALLBACK };
BackMenuItem menuBackConnectivity(&minfoConnectivity, &menuIP, INFO_LOCATION_PGM);
SubMenuItem menuConnectivity(&minfoConnectivity, &menuBackConnectivity, &menuCommits, INFO_LOCATION_PGM);
const AnyMenuInfo minfoSaveAll = { "Save All", 17, 0xffff, 0, onSaveAll };
ActionMenuItem menuSaveAll(&minfoSaveAll, NULL, INFO_LOCATION_PGM);
const FloatMenuInfo minfoAvgTemp = { "Avg Temp", 12, 0xffff, 1, NO_CALLBACK };
FloatMenuItem menuAvgTemp(&minfoAvgTemp, 0.0, &menuSaveAll, INFO_LOCATION_PGM);
ListRuntimeMenuItem menuCountingList(11, 10, fnCountingListRtCall, &menuAvgTemp);
extern char choicesItems[];
RENDERING_CALLBACK_NAME_INVOKE(fnChoicesRtCall, enumItemRenderFn, "Choices", 19, NO_CALLBACK)
ScrollChoiceMenuItem menuChoices(10, fnChoicesRtCall, 0, choicesItems, 10, 4, &menuCountingList);
const SubMenuInfo minfoOther = { "Other", 9, 0xffff, 0, NO_CALLBACK };
BackMenuItem menuBackOther(&minfoOther, &menuChoices, INFO_LOCATION_PGM);
SubMenuItem menuOther(&minfoOther, &menuBackOther, &menuConnectivity, INFO_LOCATION_PGM);
RENDERING_CALLBACK_NAME_INVOKE(fnRGBRtCall, rgbAlphaItemRenderFn, "RGB", 15, NO_CALLBACK)
Rgb32MenuItem menuRGB(fnRGBRtCall, RgbColor32(0, 0, 0, 255), 8, true, NULL);
RENDERING_CALLBACK_NAME_INVOKE(fnFrequencyRtCall, largeNumItemRenderFn, "Frequency", 7, onFrequencyChanged)
EditableLargeNumberMenuItem menuFrequency(fnFrequencyRtCall, LargeFixedNumber(8, 0, 0U, 0U, false), 7, true, &menuRGB);
const BooleanMenuInfo minfoPower = { "Power", 6, 6, 1, NO_CALLBACK, NAMING_ON_OFF };
BooleanMenuItem menuPower(&minfoPower, false, &menuFrequency, INFO_LOCATION_PGM);
const char enumStrFoods_0[] = "Salad";
const char enumStrFoods_1[] = "Pasta";
const char enumStrFoods_2[] = "Pizza";
const char enumStrFoods_3[] = "Casserole";
const char enumStrFoods_4[] = "Soup";
const char* const enumStrFoods[]  = { enumStrFoods_0, enumStrFoods_1, enumStrFoods_2, enumStrFoods_3, enumStrFoods_4 };
const EnumMenuInfo minfoFoods = { "Foods", 5, 4, 4, onFoodChange, enumStrFoods };
EnumMenuItem menuFoods(&minfoFoods, 0, &menuPower, INFO_LOCATION_PGM);
const AnalogMenuInfo minfoTenths = { "Tenths", 4, 2, 1000, onTenthsChaned, 0, 10, "tn" };
AnalogMenuItem menuTenths(&minfoTenths, 0, &menuFoods, INFO_LOCATION_PGM);
const SubMenuInfo minfoEditing = { "Editing", 3, 0xffff, 0, NO_CALLBACK };
BackMenuItem menuBackEditing(&minfoEditing, &menuTenths, INFO_LOCATION_PGM);
SubMenuItem menuEditing(&minfoEditing, &menuBackEditing, &menuOther, INFO_LOCATION_PGM);
RENDERING_CALLBACK_NAME_INVOKE(fnRTCTimeRtCall, timeItemRenderFn, "RTCTime", -1, NO_CALLBACK)
TimeFormattedMenuItem menuRTCTime(fnRTCTimeRtCall, TimeStorage(0, 0, 0, 0), 2, (MultiEditWireType)3, &menuEditing);
RENDERING_CALLBACK_NAME_INVOKE(fnRTCDateRtCall, dateItemRenderFn, "RTCDate", -1, NO_CALLBACK)
DateFormattedMenuItem menuRTCDate(fnRTCDateRtCall, DateStorage(1, 1, 2020), 1, &menuRTCTime);

void setupMenu() {
    // First we set up eeprom and authentication (if needed).
    setSizeBasedEEPROMStorageEnabled(false);
    glBspRom.initialise(0);
    menuMgr.setEepromRef(&glBspRom);
    authManager.initialise(menuMgr.getEepromAbstraction(), 100);
    menuMgr.setAuthenticator(&authManager);
    // Now add any readonly, non-remote and visible flags.
    menuEdit.setReadOnly(true);
    menuCommits.setReadOnly(true);
    menuIP.setReadOnly(true);
    menuIoTMonitor.setLocalOnly(true);
    menuAuthenticator.setLocalOnly(true);

    // Code generated by plugins.
    gfx.setRotation(0);
    gfx.begin();
    renderer.setUpdatesPerSecond(5);
    switches.init(internalDigitalIo(), SWITCHES_POLL_EVERYTHING, true);
    menuMgr.initForEncoder(&renderer, &menuRTCDate, PC_8, PC_10, PC_9);
    remoteServer.addConnection(&ethernetConnection);
    renderer.setTitleMode(BaseGraphicalRenderer::TITLE_ALWAYS);
    renderer.setUseSliderForAnalog(false);
    installMonoInverseTitleTheme(renderer, MenuFontDef(nullptr, 1), MenuFontDef(nullptr, 1), true);

    // We have an IoT monitor, register the server
    menuIoTMonitor.setRemoteServer(remoteServer);

    // We have an EEPROM authenticator, it needs initialising
    menuAuthenticator.init();
}

