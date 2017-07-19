const uint16_t sunriseSeconds = 60; // how long should the "sun" take to rise from completely dark to completely lit
const uint16_t sunriseMillis = (sunriseSeconds * 1000);
const uint16_t sunriseInterval = sunriseMillis / 240; // when using palettes, the usable range is 0-240 before it starts wrapping from the last color to the first

uint8_t sunriseIncrement = 4; // how much to change brightness for each level of the matrix

uint8_t sunriseLevel;

const CRGBPalette16 sunrisePalette = HeatColors_p;
const uint8_t centerX = MatrixWidth / 2;

void updateSunrise() {
  EVERY_N_MILLIS(sunriseInterval) {
    if (sunriseLevel < 240) {
      sunriseLevel++;
      Serial.print("Current level: "); Serial.println(sunriseLevel);
    }
    else if (sunriseIncrement > 0) {
      sunriseIncrement--;
    }
  }

  if (resetPattern) {
    sunriseLevel = 0;
    sunriseIncrement = 4;
    FastLED.clear();
  }
}

void sunriseStatic() {
  updateSunrise();

  for (uint8_t x = 0; x < MatrixWidth; x++) {
    int16_t d = sunriseLevel - sunriseIncrement;

    for (uint8_t y = 0; y < MatrixHeight; y++) {
      if (d >= 0) {
        CRGB newcolor = ColorFromPalette(sunrisePalette, random(0, d), random8(d, 255));
        uint16_t pixelnumber = XY(x, y);
        nblend(leds[pixelnumber], newcolor, 64);
      }
      d -= sunriseIncrement;
    }
  }
}

void sunriseFlicker() {
  dimAll(240);

  updateSunrise();

  for (uint8_t x = 0; x < MatrixWidth; x++) {
    int16_t d = sunriseLevel - sunriseIncrement;

    for (uint8_t y = 0; y < MatrixHeight; y++) {
      if (d >= 0) {
        CRGB newcolor = ColorFromPalette(sunrisePalette, random(0, d), random8(d, 255));
        uint16_t pixelnumber = XY(x, y);
        nblend(leds[pixelnumber], newcolor, 64);
      }
      d -= sunriseIncrement;
    }
  }
}

void sunriseWavesDiagonal() {
  dimAll(240);

  updateSunrise();

  uint8_t t = beat8(60);

  for (uint8_t x = 0; x < MatrixWidth; x++) {
    for (uint8_t y = 0; y < MatrixHeight; y++) {
      uint8_t cx = sin8(x);
      uint8_t cy = cos8(y);
      uint8_t bri8 = sin8(8 * (cx + cy) + t);

      CRGB newcolor = ColorFromPalette(sunrisePalette, sunriseLevel, bri8);

      uint16_t pixelnumber = XY(x, y);
      pixelnumber = (NUM_LEDS - 1) - pixelnumber;

      nblend(leds[pixelnumber], newcolor, 64);
    }
  }
}

void sunriseWavesVertical() {
  updateSunrise();

  static uint16_t sPseudotime = 0;
  static uint16_t sLastMillis = 0;

  uint8_t brightdepth = beatsin88( 341, 96, 224);
  uint16_t brightnessthetainc16 = beatsin88( 203, (25 * 256), (40 * 256));
  uint8_t msmultiplier = beatsin88(147, 23, 60);

  uint16_t ms = millis();
  uint16_t deltams = ms - sLastMillis ;
  sLastMillis  = ms;
  sPseudotime += deltams * msmultiplier;
  uint16_t brightnesstheta16 = sPseudotime;

  for (uint8_t y = 0; y < MatrixHeight; y++) {
    brightnesstheta16  += brightnessthetainc16;
    uint16_t b16 = sin16( brightnesstheta16  ) + 32768;

    uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
    uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
    bri8 += (255 - brightdepth);

    for (uint8_t x = 0; x < MatrixWidth; x++) {
      CRGB newcolor = ColorFromPalette(sunrisePalette, sunriseLevel, bri8);

      uint16_t pixelnumber = XY(x, (MatrixHeight - 1) - y);
      pixelnumber = (NUM_LEDS - 1) - pixelnumber;

      nblend(leds[pixelnumber], newcolor, 64);
    }
  }
}

void sunriseWavesHorizontal() {
  updateSunrise();

  static uint16_t sPseudotime = 0;
  static uint16_t sLastMillis = 0;

  uint8_t brightdepth = beatsin88( 341, 96, 224);
  uint16_t brightnessthetainc16 = beatsin88( 203, (25 * 256), (40 * 256));
  uint8_t msmultiplier = beatsin88(147, 23, 60);

  uint16_t ms = millis();
  uint16_t deltams = ms - sLastMillis ;
  sLastMillis  = ms;
  sPseudotime += deltams * msmultiplier;
  uint16_t brightnesstheta16 = sPseudotime;

  for (uint8_t x = 0; x < MatrixWidth; x++) {
    brightnesstheta16  += brightnessthetainc16;
    uint16_t b16 = sin16( brightnesstheta16  ) + 32768;

    uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
    uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
    bri8 += (255 - brightdepth);

    for (uint8_t y = 0; y < MatrixHeight; y++) {
      CRGB newcolor = ColorFromPalette(sunrisePalette, sunriseLevel, bri8);

      uint16_t pixelnumber = XY(x, y);
      pixelnumber = (NUM_LEDS - 1) - pixelnumber;

      nblend(leds[pixelnumber], newcolor, 64);
    }
  }
}

void sunriseWavesRotating() {
  updateSunrise();

  static uint16_t sPseudotime = 0;
  static uint16_t sLastMillis = 0;

  uint8_t brightdepth = beatsin88( 341, 96, 224);
  uint16_t brightnessthetainc16 = beatsin88( 203, (25 * 256), (40 * 256));
  uint8_t msmultiplier = beatsin88(147, 23, 60);

  uint16_t ms = millis();
  uint16_t deltams = ms - sLastMillis ;
  sLastMillis  = ms;
  sPseudotime += deltams * msmultiplier;
  uint16_t brightnesstheta16 = sPseudotime;

  for (uint8_t x = 0; x < MatrixWidth; x++) {
    for (uint8_t y = 0; y < MatrixHeight; y++) {
      brightnesstheta16  += brightnessthetainc16;
      uint16_t b16 = sin16( brightnesstheta16  ) + 32768;

      uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
      uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
      bri8 += (255 - brightdepth);

      CRGB newcolor = ColorFromPalette(sunrisePalette, sunriseLevel, bri8);

      uint16_t pixelnumber = XY(x, y);
      pixelnumber = (NUM_LEDS - 1) - pixelnumber;

      nblend(leds[pixelnumber], newcolor, 64);
    }
  }
}

