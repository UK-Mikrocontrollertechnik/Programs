/**
 * SSD1306xLED - Library for the SSD1306 based OLED/PLED 128x64 displays
 *
 * @author Neven Boyanov
 *
 * This is part of the Tinusaur/SSD1306xLED project.
 *
 * Copyright (c) 2018 Neven Boyanov, The Tinusaur Team. All Rights Reserved.
 * Distributed as open source software under MIT License, see LICENSE.txt file.
 * Retain in your source code the link http://tinusaur.org to the Tinusaur project.
 *
 * Source code available at: https://bitbucket.org/tinusaur/ssd1306xled
 *
 */

#ifndef SSD1306XLED_H
#define SSD1306XLED_H

#define SSD1306_SADDR	0x78  // Display's IC2 slave address, default 0x78
#define ssd1306_fill(p) ssd1306_fill4(p, p, p, p)
#define ssd1306_fill2(p1, p2) ssd1306_fill4(p1, p2, p1, p2)

/**
* @brief Initialize the ssd1306 OLED 
* @param void
*/
void ssd1306_init(void);

/**
* @brief Sets the cursor position on the display
* @param x X coord of the new pos
* @param y Y coord of the new pos
*/
void ssd1306_setpos(uint8_t x, uint8_t y);

/**
* @brief Fill an area
* @param vect4 4 Parameters defining the begin and end point of the rectangle
*/
void ssd1306_fill4(uint8_t, uint8_t, uint8_t, uint8_t);

/**
* @brief Clears the entire display via a fill4 command. Can be made faster.
* @param void
*/
void ssd1306_clear(void);

#endif
