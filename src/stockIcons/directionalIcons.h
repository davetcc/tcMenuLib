/*
 * Copyright (c) 2018 https://www.thecoderscorner.com (Dave Cherry).
 * This product is licensed under an Apache license, see the LICENSE file in the top-level directory.
 */

#ifndef TCMENU_DIRECTIONAL_ICONS_H
#define TCMENU_DIRECTIONAL_ICONS_H

/**
 * @file directionalIcons.h
 * @brief Contains directional icons in XBM format suited to use where arrow buttons are needed.
 */


#include <PlatformDetermination.h>

/**
 * ArrowHoriz11x22 icon=0, width=11, height=22, size=44
 * A left arrow that is 11 pixels wide by 22 high
 */
const uint8_t ArrowHoriz11x22BitmapLeft[] PROGMEM = {
        0x00,0x04,0x00,0x06,0x00,0x07,0x80,0x03,0xc0,0x01,0xe0,0x00,0x70,0x00,0x38,0x00,0x1c,0x00,0x0e,0x00,
        0x07,0x00,0x07,0x00,0x0e,0x00,0x1c,0x00,0x38,0x00,0x70,0x00,0xe0,0x00,0xc0,0x01,0x80,0x03,0x00,0x07,
        0x00,0x06,0x00,0x04
};

/**
 * ArrowHoriz11x22 icon=1, width=11, height=22, size=44
 * A right arrow that is 11 pixels wide by 22 high
 */
const uint8_t ArrowHoriz11x22BitmapRight[] PROGMEM = {
        0x01,0x00,0x03,0x00,0x07,0x00,0x0e,0x00,0x1c,0x00,0x38,0x00,0x70,0x00,0xe0,0x00,0xc0,0x01,0x80,0x03,
        0x00,0x07,0x00,0x07,0x80,0x03,0xc0,0x01,0xe0,0x00,0x70,0x00,0x38,0x00,0x1c,0x00,0x0e,0x00,0x07,0x00,
        0x03,0x00,0x01,0x00
};

#endif //TCMENU_DIRECTIONAL_ICONS_H