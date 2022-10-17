/*
    The code in this file uses open source libraries provided by thecoderscorner

    DO NOT EDIT THIS FILE, IT WILL BE GENERATED EVERY TIME YOU USE THE UI DESIGNER
    INSTEAD EITHER PUT CODE IN YOUR SKETCH OR CREATE ANOTHER SOURCE FILE.

    All the variables you may need access to are marked extern in this file for easy
    use elsewhere.
 */

#include <tcMenu.h>
#include "esp32Amplifier_menu.h"
#include "ThemeCoolBlueModern.h"

// Global variable declarations
const PROGMEM  ConnectorLocalInfo applicationInfo = { "ESP Amplifier", "4656c798-10c6-4110-8e03-b9c51ed8fffb" };
TcMenuRemoteServer remoteServer(applicationInfo);
ArduinoEEPROMAbstraction glArduinoEeprom(&EEPROM);
EepromAuthenticatorManager authManager(6);
TFT_eSPI tft;
TfteSpiDrawable tftDrawable(&tft, 45);
GraphicsDeviceRenderer renderer(30, applicationInfo.name, &tftDrawable);
iotouch::ResistiveTouchInterrogator touchInterrogator(2, 33, 32, 0);
MenuTouchScreenManager touchScreen(&touchInterrogator, &renderer, iotouch::TouchInterrogator::LANDSCAPE);
WiFiServer server(3333);
EthernetInitialisation ethernetInitialisation(&server);
EthernetTagValTransport ethernetTransport;
TagValueRemoteServerConnection ethernetConnection(ethernetTransport, ethernetInitialisation);

// Global Menu Item declarations
const PROGMEM char pgmStrConnectivityAuthenticatorText[] = { "Authenticator" };
EepromAuthenticationInfoMenuItem menuConnectivityAuthenticator(pgmStrConnectivityAuthenticatorText, NO_CALLBACK, 27, NULL);
const PROGMEM char pgmStrConnectivityIoTMonitorText[] = { "IoT Monitor" };
RemoteMenuItem menuConnectivityIoTMonitor(pgmStrConnectivityIoTMonitorText, 26, &menuConnectivityAuthenticator);
RENDERING_CALLBACK_NAME_INVOKE(fnConnectivityPasscodeRtCall, textItemRenderFn, "Passcode", 37, NO_CALLBACK)
TextMenuItem menuConnectivityPasscode(fnConnectivityPasscodeRtCall, 19, 20, &menuConnectivityIoTMonitor);
RENDERING_CALLBACK_NAME_INVOKE(fnConnectivitySSIDRtCall, textItemRenderFn, "SSID", 17, NO_CALLBACK)
TextMenuItem menuConnectivitySSID(fnConnectivitySSIDRtCall, 18, 20, &menuConnectivityPasscode);
RENDERING_CALLBACK_NAME_INVOKE(fnConnectivityIPAddressRtCall, ipAddressRenderFn, "IP address", -1, NO_CALLBACK)
IpAddressMenuItem menuConnectivityIPAddress(fnConnectivityIPAddressRtCall, 13, &menuConnectivitySSID);
RENDERING_CALLBACK_NAME_INVOKE(fnConnectivityRtCall, backSubItemRenderFn, "Connectivity", -1, NO_CALLBACK)
const PROGMEM SubMenuInfo minfoConnectivity = { "Connectivity", 12, 0xffff, 0, NO_CALLBACK };
BackMenuItem menuBackConnectivity(fnConnectivityRtCall, &menuConnectivityIPAddress);
SubMenuItem menuConnectivity(&minfoConnectivity, &menuBackConnectivity, NULL);
const PROGMEM AnalogMenuInfo minfoStatusTest = { "Test", 28, 0xffff, 65535, NO_CALLBACK, -5000, 10, "U" };
AnalogMenuItem menuStatusTest(&minfoStatusTest, 0, NULL);
ListRuntimeMenuItem menuStatusDataList(21, 0, fnStatusDataListRtCall, &menuStatusTest);
const PROGMEM AnyMenuInfo minfoStatusShowDialogs = { "Show Dialogs", 20, 0xffff, 0, onShowDialogs };
ActionMenuItem menuStatusShowDialogs(&minfoStatusShowDialogs, &menuStatusDataList);
const PROGMEM AnalogMenuInfo minfoStatusRightVU = { "Right VU", 16, 0xffff, 30000, NO_CALLBACK, -20000, 1000, "dB" };
AnalogMenuItem menuStatusRightVU(&minfoStatusRightVU, 0, &menuStatusShowDialogs);
const PROGMEM AnalogMenuInfo minfoStatusLeftVU = { "Left VU", 15, 0xffff, 30000, NO_CALLBACK, -20000, 1000, "dB" };
AnalogMenuItem menuStatusLeftVU(&minfoStatusLeftVU, 0, &menuStatusRightVU);
const char enumStrStatusAmpStatus_0[] PROGMEM = "Warm up";
const char enumStrStatusAmpStatus_1[] PROGMEM = "Warm Valves";
const char enumStrStatusAmpStatus_2[] PROGMEM = "Ready";
const char enumStrStatusAmpStatus_3[] PROGMEM = "DC Protection";
const char enumStrStatusAmpStatus_4[] PROGMEM = "Overloaded";
const char enumStrStatusAmpStatus_5[] PROGMEM = "Overheated";
const char* const enumStrStatusAmpStatus[] PROGMEM  = { enumStrStatusAmpStatus_0, enumStrStatusAmpStatus_1, enumStrStatusAmpStatus_2, enumStrStatusAmpStatus_3, enumStrStatusAmpStatus_4, enumStrStatusAmpStatus_5 };
const PROGMEM EnumMenuInfo minfoStatusAmpStatus = { "Amp Status", 14, 0xffff, 5, NO_CALLBACK, enumStrStatusAmpStatus };
EnumMenuItem menuStatusAmpStatus(&minfoStatusAmpStatus, 0, &menuStatusLeftVU);
RENDERING_CALLBACK_NAME_INVOKE(fnStatusRtCall, backSubItemRenderFn, "Status", -1, NO_CALLBACK)
const PROGMEM SubMenuInfo minfoStatus = { "Status", 6, 0xffff, 0, NO_CALLBACK };
BackMenuItem menuBackStatus(fnStatusRtCall, &menuStatusAmpStatus);
SubMenuItem menuStatus(&minfoStatus, &menuBackStatus, &menuConnectivity);
const PROGMEM AnyMenuInfo minfoSettingsSaveSettings = { "Save settings", 25, 0xffff, 0, onSaveSettings };
ActionMenuItem menuSettingsSaveSettings(&minfoSettingsSaveSettings, NULL);
const PROGMEM AnalogMenuInfo minfoSettingsValveHeating = { "Valve Heating", 17, 15, 600, valveHeatingChanged, 0, 10, "s" };
AnalogMenuItem menuSettingsValveHeating(&minfoSettingsValveHeating, 0, &menuSettingsSaveSettings);
const PROGMEM AnalogMenuInfo minfoSettingsWarmUpTime = { "Warm up time", 11, 7, 300, warmUpChanged, 0, 10, "s" };
AnalogMenuItem menuSettingsWarmUpTime(&minfoSettingsWarmUpTime, 0, &menuSettingsValveHeating);
const PROGMEM AnyMenuInfo minfoChannelSettingsUpdateSettings = { "Update Settings", 24, 0xffff, 0, onChannelSetttingsUpdate };
ActionMenuItem menuChannelSettingsUpdateSettings(&minfoChannelSettingsUpdateSettings, NULL);
RENDERING_CALLBACK_NAME_INVOKE(fnChannelSettingsNameRtCall, textItemRenderFn, "Name", -1, NO_CALLBACK)
TextMenuItem menuChannelSettingsName(fnChannelSettingsNameRtCall, 22, 15, &menuChannelSettingsUpdateSettings);
const PROGMEM AnalogMenuInfo minfoChannelSettingsLevelTrim = { "Level Trim", 8, 9, 20, NO_CALLBACK, -10, 2, "dB" };
AnalogMenuItem menuChannelSettingsLevelTrim(&minfoChannelSettingsLevelTrim, 0, &menuChannelSettingsName);
ScrollChoiceMenuItem menuChannelSettingsChannel(23, fnChannelSettingsChannelRtCall, 0, 3, &menuChannelSettingsLevelTrim);
RENDERING_CALLBACK_NAME_INVOKE(fnSettingsChannelSettingsRtCall, backSubItemRenderFn, "Channel Settings", -1, NO_CALLBACK)
const PROGMEM SubMenuInfo minfoSettingsChannelSettings = { "Channel Settings", 7, 0xffff, 0, NO_CALLBACK };
BackMenuItem menuBackSettingsChannelSettings(fnSettingsChannelSettingsRtCall, &menuChannelSettingsChannel);
SubMenuItem menuSettingsChannelSettings(&minfoSettingsChannelSettings, &menuBackSettingsChannelSettings, &menuSettingsWarmUpTime);
RENDERING_CALLBACK_NAME_INVOKE(fnSettingsRtCall, backSubItemRenderFn, "Settings", -1, NO_CALLBACK)
const PROGMEM SubMenuInfo minfoSettings = { "Settings", 5, 0xffff, 0, NO_CALLBACK };
BackMenuItem menuBackSettings(fnSettingsRtCall, &menuSettingsChannelSettings);
SubMenuItem menuSettings(&minfoSettings, &menuBackSettings, &menuStatus);
const PROGMEM BooleanMenuInfo minfoMute = { "Mute", 4, 0xffff, 1, onMuteSound, NAMING_TRUE_FALSE };
BooleanMenuItem menuMute(&minfoMute, false, &menuSettings);
const PROGMEM BooleanMenuInfo minfoDirect = { "Direct", 3, 6, 1, onAudioDirect, NAMING_TRUE_FALSE };
BooleanMenuItem menuDirect(&minfoDirect, false, &menuMute);
RENDERING_CALLBACK_NAME_INVOKE(fnChannelsRtCall, enumItemRenderFn, "Channel", 4, onChannelChanged)
ScrollChoiceMenuItem menuChannels(2, fnChannelsRtCall, 0, 150, 16, 3, &menuDirect);
const PROGMEM AnalogMenuInfo minfoVolume = { "Volume", 1, 2, 255, onVolumeChanged, -180, 2, "dB" };
AnalogMenuItem menuVolume(&minfoVolume, 0, &menuChannels);

void setupMenu() {
    // First we set up eeprom and authentication (if needed).
    menuMgr.setEepromRef(&glArduinoEeprom);
    authManager.initialise(menuMgr.getEepromAbstraction(), 200);
    menuMgr.setAuthenticator(&authManager);
    // Now add any readonly, non-remote and visible flags.
    menuConnectivityIPAddress.setReadOnly(true);
    menuConnectivityAuthenticator.setLocalOnly(true);
    menuConnectivityIoTMonitor.setLocalOnly(true);

    // Code generated by plugins.
    tft.begin();
    tft.setRotation(1);
    renderer.setUpdatesPerSecond(10);
    touchScreen.start();
    menuMgr.initWithoutInput(&renderer, &menuVolume);
    remoteServer.addConnection(&ethernetConnection);
    renderer.setTitleMode(BaseGraphicalRenderer::TITLE_ALWAYS);
    renderer.setUseSliderForAnalog(true);
    installCoolBlueModernTheme(renderer, MenuFontDef(nullptr, 4), MenuFontDef(nullptr, 4), false);

    // We have an IoT monitor, register the server
    menuConnectivityIoTMonitor.setRemoteServer(remoteServer);

    // We have an EEPROM authenticator, it needs initialising
    menuConnectivityAuthenticator.init();
}
