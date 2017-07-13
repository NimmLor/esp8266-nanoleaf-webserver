bool mask[NUM_LEDS];

const byte digits4x8[8 * 10] = {
  0x06, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x06, // 0
  0x04, 0x06, 0x04, 0x04, 0x04, 0x04, 0x04, 0x0e, // 1
  0x06, 0x09, 0x08, 0x08, 0x04, 0x02, 0x01, 0x0f, // 2
  0x06, 0x09, 0x08, 0x04, 0x08, 0x08, 0x09, 0x06, // 3
  0x04, 0x05, 0x05, 0x05, 0x0f, 0x04, 0x04, 0x04, // 4
  0x0f, 0x01, 0x01, 0x07, 0x08, 0x08, 0x09, 0x06, // 5
  0x06, 0x09, 0x01, 0x07, 0x09, 0x09, 0x09, 0x06, // 6
  0x0f, 0x08, 0x08, 0x04, 0x02, 0x01, 0x01, 0x01, // 7
  0x06, 0x09, 0x09, 0x06, 0x09, 0x09, 0x09, 0x06, // 8
  0x06, 0x09, 0x09, 0x09, 0x0e, 0x08, 0x09, 0x06, // 9
};

// preceed with a call to fillMask(false);
// set mask to true where digit should light
void digit(byte start, byte d) {
  byte row, col;
  for (col = 0; col < 4; col++) {
    for (row = 0; row < 8; row++) {
      if ((digits4x8[d * 8 + row] >> col) & 1) {
        togglePixelMask(row, col + start, true);
      }
      else {
      }
    }
  }
}

void displayNum(uint32_t n) {
  digit( 0, (n / 10000) % 10);
  digit( 5, (n / 1000) % 10);
  digit(10, (n / 100) % 10);
  digit(15, (n / 10) % 10);
  digit(20, (n / 1) % 10);
}

void displayTime(uint32_t tm) {
  uint8_t hh = (tm / 3600) % 12;
  uint8_t mm = (tm / 60) % 60;
  uint8_t ss = (tm) % 60;
  if (hh > 9) {
    digit( 1, hh / 10);
  }
  digit( 6, hh % 10);
  setPixelMask(2, 11, true);
  setPixelMask(3, 11, true);
  setPixelMask(5, 11, true);
  setPixelMask(6, 11, true);
  digit(13, mm / 10);
  digit(18, mm % 10);

  if (hh > 9) {
    digit( 1 + 24, hh / 10);
  }
  digit( 6 + 24, hh % 10);
  setPixelMask(2, 11 + 24, true);
  setPixelMask(3, 11 + 24, true);
  setPixelMask(5, 11 + 24, true);
  setPixelMask(6, 11 + 24, true);
  digit(13 + 24, mm / 10);
  digit(18 + 24, mm % 10);
}

