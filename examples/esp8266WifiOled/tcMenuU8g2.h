/*
 * Copyright (c) 2018 https://www.thecoderscorner.com (Nutricherry LTD).
 * This product is licensed under an Apache license, see the LICENSE file in the top-level directory.
 */

/**
 * @file tcMenuU8g2.h
 * 
 * U8g2 renderer that renders menus onto this type of display. This file is a plugin file and should not
 * be directly edited, it will be replaced each time the project is built. If you want to edit this file in place,
 * make sure to rename it first.
 * 
 * LIBRARY REQUIREMENT
 * This library requires the u8g2 library available for download from your IDE library manager.
 */

#ifndef _TCMENU_U8G2_H_
#define _TCMENU_U8G2_H_

#include <tcMenu.h>
#include <tcUtil.h>
#include <U8g2lib.h>
#include <BaseGraphicalRenderer.h>
#include <BaseDialog.h>
#include <tcUtil.h>

extern const ConnectorLocalInfo applicationInfo;

/**
 * A standard menu render configuration that describes how to renderer each item and the title.
 * Specialised for u8g2 fonts.
 */ 
typedef struct ColorGfxMenuConfig<const uint8_t*> U8g2GfxMenuConfig;

// some colour displays don't create this value
#ifndef BLACK
#define BLACK 0
#endif

// some colour displays don't create this value
#ifndef WHITE
#define WHITE 1
#endif

/**
 * A basic renderer that can use the AdaFruit_GFX library to render information onto a suitable
 * display. It is your responsibility to fully initialise and prepare the display before passing
 * it to this renderer. The usual procedure is to create a display variable globally in your
 * sketch and then provide that as the parameter to setGraphicsDevice. If you are using the
 * designer you provide the display variable name in the code generation parameters.
 * 
 * You can also override many elements of the display using AdaColorGfxMenuConfig, to use the defaults
 * just call prepareAdaColorDefaultGfxConfig(..) passing it a pointer to your config object. Again the
 * designer UI takes care of this.
 */
class U8g2MenuRenderer : public BaseGraphicalRenderer {
private:
	U8G2* u8g2;
	ItemDisplayPropertiesFactory *displayPropsFactory;
	int16_t titleHeight;
    int16_t itemHeight;
    bool redrawNeeded;
public:
	U8g2MenuRenderer(uint8_t bufferSize = 20) : BaseGraphicalRenderer(bufferSize, 1, 1, false) {
		this->u8g2 = NULL;
		this->displayPropsFactory = NULL;
	}
    ~U8g2MenuRenderer() override = default;

	void setGraphicsDevice(U8G2* u8g2, U8g2GfxMenuConfig *gfxConfig);
	void setGraphicsDevice(U8G2* u8g2, ItemDisplayPropertiesFactory *gfxConfig);

	void recalculateTitleAndRowHeights();

    void drawWidget(Coord where, TitleWidget *widget) override;
    void drawMenuItem(MenuItem *theItem, GridPosition::GridDrawingMode mode, Coord where, Coord areaSize) override;
    void drawingCommand(RenderDrawingCommand command) override;

    U8G2* getGraphics() { return u8g2; }
    U8g2GfxMenuConfig* getGfxConfig() { return gfxConfig; }
    BaseDialog* getDialog() override;
private:
    void drawBitmap(int x, int y, int w, int h, const unsigned char *bmp);
    void drawTitleArea(MenuItem* pItem, Coord where, Coord size);
    void drawTextualItem(MenuItem *pItem, Coord where, Coord size);
    void drawIconItem(MenuItem *pItem, Coord where, Coord size, bool withText);
    void drawSlider(AnalogMenuItem *pItem, Coord where, Coord size);

    int drawCoreLineItem(MenuItem *pItem, const Coord &where, const Coord &size);
};

class U8g2Dialog : public BaseDialog {
public:
    U8g2Dialog();
protected:
    void internalRender(int currentValue) override;
    void drawButton(U8G2* gfx, U8g2GfxMenuConfig* config, const char* title, uint8_t num, bool active);
};

/**
 * Provides a basic graphics configuration suitable for low / medium resolution displays
 * @param config usually a global variable holding the graphics configuration.
 */
void prepareBasicU8x8Config(U8g2GfxMenuConfig& config);

#endif // _TCMENU_U8G2_H_
