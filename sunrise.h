void sunrise() {
  dimAll(240);

  CRGBPalette16 palette = HeatColors_p;

  const uint8_t centerX = MatrixWidth / 2;

  static uint8_t currentLevel = 0;

  static uint8_t inc = 4;

  EVERY_N_MILLIS(250) {
    if (currentLevel < 240) {
      currentLevel++;
      Serial.print("Current level: "); Serial.println(currentLevel);
    }
    else if (inc > 0) {
      inc--;      
    }
  }

  for (uint8_t x = 0; x < MatrixWidth; x++) {
    int16_t d = currentLevel - inc;

    for (uint8_t y = 0; y < MatrixHeight; y++) {
      if (d >= 0) {
        leds[XY(x, y)] += ColorFromPalette(palette, random(0, d), random8(d, 255));
      }
      d -= inc;
    }
  }
}

