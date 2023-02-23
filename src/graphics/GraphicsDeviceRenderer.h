/*
 * Copyright (c) 2018 https://www.thecoderscorner.com (Dave Cherry).
 * This product is licensed under an Apache license, see the LICENSE file in the top-level directory.
 */

/**
 * @file GraphicsDeviceRenderer.h
 * @brief the interface that all graphics devices should implement to do the actual graphics rendering.
 */

#ifndef TCLIBRARYDEV_GRAPHICSDEVICERENDERER_H
#define TCLIBRARYDEV_GRAPHICSDEVICERENDERER_H

#include <PlatformDetermination.h>
#include "../tcMenu.h"
#include "BaseGraphicalRenderer.h"
#include "GfxMenuConfig.h"
#include "DeviceDrawableHelper.h"

#ifndef MINIMUM_CURSOR_SIZE
#define MINIMUM_CURSOR_SIZE 6
#endif // MINIMUM_CURSOR_SIZE

namespace tcgfx {
    /**
     * The layout modes that are supported by the graphical renderer, you can set this per sub menu.
     */
    enum MenuLayoutMode {
        /** The regular vertical scrolling layout, items are presented vertically, and scroll as needed */
        LAYOUT_REGULAR_VERTICAL,
        /** Horizontal card layout, one item is shown at once, with button indicators for moving between items */
        LAYOUT_CARD_HORIZONTAL
    };

    /**
     * This class contains all the drawing code that is used for most graphical displays, it relies on an instance of
     * device drawable to do the drawing. It can also use sub drawing if the drawing device supports it, and it is enabled.
     * This means that on supported devices it is possible to do flicker free rendering.
     *
     * To support a new display, do not touch this class unless something is amiss or there is a bug, instead just implement
     * the above DeviceDrawable for that display. Take a look at the other rendering classes we already have for an example
     * of how.
     */
    class GraphicsDeviceRenderer : public BaseGraphicalRenderer {
    private:
        DeviceDrawable* rootDrawable;
        DeviceDrawableHelper helper;
        ConfigurableItemDisplayPropertiesFactory propertiesFactory;
        bool redrawNeeded = false;
    public:
        GraphicsDeviceRenderer(int bufferSize, const char *appTitle, DeviceDrawable *drawable);

        void drawWidget(Coord where, TitleWidget *widget, color_t colorFg, color_t colorBg) override;
        void drawMenuItem(GridPositionRowCacheEntry *entry, Coord where, Coord areaSize, bool drawAll) override;
        void drawingCommand(RenderDrawingCommand command) override;

        void fillWithBackgroundTo(int endPoint) override;

        /**
         * Get the height for the font and add the descent to the bottom padding.
         * @param font the font to measure
         * @param mag any magnification to apply - if supported
         * @param padding the padding for the item, bottom will be adjusted
         * @return the height of the item.
         */
        int heightForFontPadding(const void *font, int mag, MenuPadding &padding);

        /**
         * Set up the display based on the legacy graphics configuration. This is deprecated and you should move to
         * using prepareDisplay. New code should NOT use this as it will be removed in a future build.
         * @deprecated use prepareDisplay with displayProperties overrides instead as per all examples.
         * @param gfxConfig the legacy graphics configuration
         */
        void setGraphicsConfiguration(void* gfxConfig);

        /**
         * Set up the display using a basic configuration. Setting factories with default colours and sizes.
         * @param monoPalette true if the display is monochrome, otherwise false.
         * @param itemFont the font to use for items
         * @param titleFont the font to use for the title
         * @param needEditingIcons true if editing icons should be prepared, otherwise false.
         */
        void prepareDisplay(bool monoPalette, const void *itemFont, int magItem, const void *titleFont, int magTitle, bool needEditingIcons);

        /**
         * Gets the abstract display properties factory, used internally to get the factory regardless of what actual
         * type it is, in user code that is using graphics properties factory, use getGraphicsPropertiesFactory
         * @return the properties factory
         */
        ItemDisplayPropertiesFactory &getDisplayPropertiesFactory() override { return propertiesFactory; }

        /**
         * Gets the graphical display properties factory, so that you can add graphics configuration easily.
         * @return the properties factory
         */
        ConfigurableItemDisplayPropertiesFactory &getGraphicsPropertiesFactory() { return propertiesFactory; }

        /**
         * Gets the underlying device drawable so that you can render to the screen in a device independent way.
         * On most systems this is a very thin wrapper on the library and performs very well for all but the most
         * intensive of drawing operations.
         * @return the underlying device drawable.
         */
        DeviceDrawable* getDeviceDrawable() { return rootDrawable; }

        /**
         * Enables TcUnicode as the default font processor for all operations, and ensures that the unicode helper can
         * be accessed too.
         */
        void enableTcUnicode() { rootDrawable->enableTcUnicode(); }

        /**
         * Sets the mode in which to render the submenu, see the enumeration for the possible options.
         * @param item the sub menu to set the mode for
         * @param layout the layout mode, see the enumeration
         */
        void setRenderModeForSubMenu(SubMenuItem* item, MenuLayoutMode layout);
    private:
        int calculateSpaceBetween(const void* font, uint8_t mag, const char* buffer, int start, int end);
        void internalDrawText(GridPositionRowCacheEntry* pEntry, const Coord& where, const Coord& size);
        void drawCoreLineItem(GridPositionRowCacheEntry* entry, DrawableIcon* icon, Coord &where, Coord &size, bool drawBg);
        void drawTextualItem(GridPositionRowCacheEntry* entry, Coord& where, Coord& size);
        void drawCheckbox(GridPositionRowCacheEntry *entry, Coord& where, Coord& size);
        void drawSlider(GridPositionRowCacheEntry* entry, AnalogMenuItem* pItem, Coord& where, Coord& size);
        void drawUpDownItem(GridPositionRowCacheEntry* entry, Coord& where, Coord& size);
        void drawIconItem(GridPositionRowCacheEntry *pEntry, Coord& where, Coord& size);
        void drawBorderAndAdjustSize(Coord &where, Coord &size, MenuBorder &border);
    };
} // namespace tcgfx

#endif //TCLIBRARYDEV_GRAPHICSDEVICERENDERER_H
