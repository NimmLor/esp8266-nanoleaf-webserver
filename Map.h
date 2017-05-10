uint8_t cubeWidth = 8;
uint8_t cubeDepth = 8;
uint8_t cubeHeight = 8;

uint8_t coordsX[NUM_LEDS] = { 7, 7, 7, 7, 7, 7, 7, 7, 6, 6, 6, 6, 6, 6, 6, 6, 5, 5, 5, 5, 5, 5, 5, 5, 4, 4, 4, 4, 4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 6, 5, 4, 3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 6, 7, 7, 6, 5, 4, 3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 6, 7, 7, 6, 5, 4, 3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 6, 7, 7, 6, 5, 4, 3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 6, 7 };
uint8_t coordsY[NUM_LEDS] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 6, 6, 6, 6, 6, 6, 6, 5, 5, 5, 5, 5, 5, 5, 5, 4, 4, 4, 4, 4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 };
uint8_t coordsZ[NUM_LEDS] = { 7, 6, 5, 4, 3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 6, 7, 7, 6, 5, 4, 3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 6, 7, 7, 6, 5, 4, 3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 6, 7, 7, 6, 5, 4, 3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 6, 7, 7, 6, 5, 4, 3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 6, 7, 7, 6, 5, 4, 3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 6, 7, 7, 6, 5, 4, 3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 6, 7, 7, 6, 5, 4, 3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

void cubeTest() {
  static uint8_t x = 0;
  static uint8_t y = 0;
  static uint8_t z = 0;

  EVERY_N_MILLIS(255 - speed) {
    x++;
    if(x >= cubeWidth) {
      x = 0;
      y++;
      if(y >= cubeDepth) {
        y = 0;
        z++;
        if(z >= cubeHeight) {
          z = 0;
        }
      }
    }
    
    FastLED.clear();

    CHSV color = CHSV(gHue, 255, 255);
    
    for(uint8_t i = 0; i < NUM_LEDS; i++) {
      uint8_t cx = coordsX[i];
      uint8_t cy = coordsY[i];
      uint8_t cz = coordsZ[i];
      
      if((cx == x && cy == y) || (cx == x && cz == z) || (cy == y && cz == z)) {
        leds[i] = color;
      }
    }
  }
}

void cubeXPalette() {
  uint8_t hues = 8;

  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    uint8_t x = coordsX[i];

    leds[i] = ColorFromPalette(palettes[currentPaletteIndex], beat8(speed) - (x * hues));
  }
}

void cubeYPalette() {
  uint8_t hues = 8;

  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    uint8_t y = coordsY[i];

    leds[i] = ColorFromPalette(palettes[currentPaletteIndex], beat8(speed) - (y * hues));
  }
}

void cubeZPalette() {
  uint8_t hues = 8;

  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    uint8_t z = coordsZ[i];

    leds[i] = ColorFromPalette(palettes[currentPaletteIndex], beat8(speed) - (z * hues));
  }
}

void cubeXYPalette() {
  uint8_t hues = 8;

  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    uint8_t x = coordsX[i];
    uint8_t y = coordsY[i];

    leds[i] = ColorFromPalette(palettes[currentPaletteIndex], beat8(speed) - ((x + y) * hues));
  }
}

void cubeXZPalette() {
  uint8_t hues = 8;

  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    uint8_t x = coordsX[i];
    uint8_t z = coordsZ[i];

    leds[i] = ColorFromPalette(palettes[currentPaletteIndex], beat8(speed) - ((x + z) * hues));
  }
}

void cubeYZPalette() {
  uint8_t hues = 8;

  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    uint8_t y = coordsY[i];
    uint8_t z = coordsZ[i];

    leds[i] = ColorFromPalette(palettes[currentPaletteIndex], beat8(speed) - ((y + z) * hues));
  }
}

void cubeXYZPalette() {
  uint8_t hues = 8;

  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    uint8_t x = coordsX[i];
    uint8_t y = coordsY[i];
    uint8_t z = coordsZ[i];

    leds[i] = ColorFromPalette(palettes[currentPaletteIndex], beat8(speed) - ((x + y + z) * hues));
  }
}

void cubeXGradientPalette() {
  uint8_t hues = 8;
  
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    uint8_t x = coordsX[i];

    leds[i] = ColorFromPalette(gCurrentPalette, beat8(speed) - (x * hues));
  }
}

void cubeYGradientPalette() {
  uint8_t hues = 8;
  
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    uint8_t y = coordsY[i];

    leds[i] = ColorFromPalette(gCurrentPalette, beat8(speed) - (y * hues));
  }
}

void cubeZGradientPalette() {
  uint8_t hues = 8;
  
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    uint8_t z = coordsZ[i];

    leds[i] = ColorFromPalette(gCurrentPalette, beat8(speed) - (z * hues));
  }
}

void cubeXYGradientPalette() {
  uint8_t hues = 8;
  
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    uint8_t x = coordsX[i];
    uint8_t y = coordsY[i];

    leds[i] = ColorFromPalette(gCurrentPalette, beat8(speed) - ((x + y) * hues));
  }
}

void cubeXZGradientPalette() {
  uint8_t hues = 8;

  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    uint8_t x = coordsX[i];
    uint8_t z = coordsZ[i];

    leds[i] = ColorFromPalette(gCurrentPalette, beat8(speed) - ((x + z) * hues));
  }
}

void cubeYZGradientPalette() {
  uint8_t hues = 8;

  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    uint8_t y = coordsY[i];
    uint8_t z = coordsZ[i];

    leds[i] = ColorFromPalette(gCurrentPalette, beat8(speed) - ((y + z) * hues));
  }
}

void cubeXYZGradientPalette() {
  uint8_t hues = 8;

  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    uint8_t x = coordsX[i];
    uint8_t y = coordsY[i];
    uint8_t z = coordsZ[i];

    leds[i] = ColorFromPalette(gCurrentPalette, beat8(speed) - ((x + y + z) * hues));
  }
}

