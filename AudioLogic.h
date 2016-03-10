/*
 * ESP8266 + FastLED + IR Remote + MSGEQ7: https://github.com/jasoncoon/esp8266-fastled-webserver
 * Copyright (C) 2015 Jason Coon
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#define MSGEQ7_STROBE_PIN  4
#define MSGEQ7_RESET_PIN  14
#define MSGEQ7_OUT_PIN    A0

const uint8_t bandCount = 7;

uint8_t levels[bandCount];
uint8_t filter = 200;

void initializeAudio() {
  pinMode(MSGEQ7_OUT_PIN, INPUT);
  pinMode(MSGEQ7_RESET_PIN, OUTPUT);
  pinMode(MSGEQ7_STROBE_PIN, OUTPUT);
  digitalWrite(MSGEQ7_RESET_PIN, LOW);
  digitalWrite(MSGEQ7_STROBE_PIN, HIGH);
}

void readAudio() {
  digitalWrite(MSGEQ7_RESET_PIN, HIGH);
  digitalWrite(MSGEQ7_RESET_PIN, LOW);

  int level;

  for (uint8_t band = 0; band < bandCount; band++) {
    digitalWrite(MSGEQ7_STROBE_PIN, LOW);
    delayMicroseconds(30);

    uint16_t level = analogRead(MSGEQ7_OUT_PIN);
    levels[band] = map(level, filter, 1023, 0, 255);
    digitalWrite(MSGEQ7_STROBE_PIN, HIGH);
  }
}

