/*
   ESP8266 + FastLED + IR Remote: https://github.com/jasoncoon/esp8266-fastled-webserver
   Copyright (C) 2015-2016 Jason Coon

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// The 16 bit version of our coordinates
uint16_t noisex;
uint16_t noisey;
uint16_t noisez;

// We're using the x/y dimensions to map to the x/y pixels on the matrix.  We'll
// use the z-axis for "time".  speed determines how fast time moves forward.  Try
// 1 for a very slow moving effect, or 60 for something that ends up looking like
// water.
int8_t noisespeedx = 0;
int8_t noisespeedy = 1;
int8_t noisespeedz = 0;

// Scale determines how far apart the pixels in our noise matrix are.  Try
// changing these values around to see how it affects the motion of the display.  The
// higher the value of scale, the more "zoomed out" the noise will be.  A value
// of 1 will be so zoomed in, you'll mostly see solid colors.
uint16_t noisescale = 1; // scale is set dynamically once we've started up

uint8_t colorLoop = 0;

CRGBPalette16 blackAndWhiteStripedPalette;

// This function sets up a palette of black and white stripes,
// using code.  Since the palette is effectively an array of
// sixteen CRGB colors, the various fill_* functions can be used
// to set them up.
void SetupBlackAndWhiteStripedPalette()
{
  // 'black out' all 16 palette entries...
  fill_solid( blackAndWhiteStripedPalette, 16, CRGB::Black);
  // and set every fourth one to white.
  blackAndWhiteStripedPalette[0] = CRGB::White;
  blackAndWhiteStripedPalette[4] = CRGB::White;
  blackAndWhiteStripedPalette[8] = CRGB::White;
  blackAndWhiteStripedPalette[12] = CRGB::White;

}

CRGBPalette16 blackAndBlueStripedPalette;

// This function sets up a palette of black and blue stripes,
// using code.  Since the palette is effectively an array of
// sixteen CRGB colors, the various fill_* functions can be used
// to set them up.
void SetupBlackAndBlueStripedPalette()
{
  // 'black out' all 16 palette entries...
  fill_solid( blackAndBlueStripedPalette, 16, CRGB::Black);

  for(uint8_t i = 0; i < 6; i++) {
    blackAndBlueStripedPalette[i] = CRGB::Blue;
  }
}

// There are several different palettes of colors demonstrated here.
//
// FastLED provides several 'preset' palettes: RainbowColors_p, RainbowStripeColors_p,
// OceanColors_p, CloudColors_p, LavaColors_p, ForestColors_p, and PartyColors_p.
//
// Additionally, you can manually define your own color palettes, or you can write
// code that creates color palettes on the fly.

void drawNoise3d(CRGBPalette16 palette, uint8_t hueReduce = 0)
{
  for(uint16_t i = 0; i < NUM_LEDS; i++) {
    uint8_t x = coordsX[i];
    uint8_t y = coordsY[i];
    uint8_t z = coordsZ[i];
   
    int xoffset = noisescale * x;
    int yoffset = noisescale * y;
    int zoffset = noisescale * z;

    uint8_t data = inoise8(x + xoffset + noisex, y + yoffset + noisey, z + zoffset + noisez);

    // The range of the inoise8 function is roughly 16-238.
    // These two operations expand those values out to roughly 0..255
    // You can comment them out if you want the raw noise data.
    data = qsub8(data, 16);
    data = qadd8(data, scale8(data, 39));

    if(hueReduce > 0 && data >= hueReduce)
      data -= hueReduce;

    leds[i] = ColorFromPalette(palette, data, 255, LINEARBLEND); 
  }
  
  noisex += noisespeedx;
  noisey += noisespeedy;
  noisez += noisespeedz;
}

void rainbowNoise3d() {
  noisespeedx = -1;
  noisespeedy = -1;
  noisespeedz = 0;
  noisescale = 24;
  colorLoop = 0;
  drawNoise3d(RainbowColors_p);
}

void rainbowStripeNoise3d() {
  noisespeedx = -1;
  noisespeedy = -1;
  noisespeedz = -1;
  noisescale = 24;
  colorLoop = 0;
  drawNoise3d(RainbowStripeColors_p);
}

void partyNoise3d() {
  noisespeedx = -9;
  noisespeedy = 0;
  noisespeedz = 0;
  noisescale = 32;
  colorLoop = 0;
  drawNoise3d(PartyColors_p);
}

void forestNoise3d() {
  noisespeedx = -9;
  noisespeedy = 0;
  noisespeedz = 0;
  noisescale = 32;
  colorLoop = 0;
  drawNoise3d(ForestColors_p);
}

void cloudNoise3d() {
  noisespeedx = -2;
  noisespeedy = 0;
  noisespeedz = 0;
  noisescale = 24;
  colorLoop = 0;
  drawNoise3d(CloudColors_p);
}

void fireNoise3d() {
  noisespeedx = 16;
  noisespeedy = 16;
  noisespeedz = 16;
  noisescale = 64;
  colorLoop = 0;
  drawNoise3d(HeatColors_p, 60);
}

void fireNoise23d() {
  noisespeedx = -3;
  noisespeedy = -3;
  noisespeedz = -3;
  noisescale = 32;
  colorLoop = 0;
  drawNoise3d(HeatColors_p);
}

void lavaNoise3d() {
  noisespeedx = -4;
  noisespeedy = -4;
  noisespeedz = -4;
  noisescale = 32;
  colorLoop = 0;
  drawNoise3d(LavaColors_p);
}

void oceanNoise3d() {
  noisespeedx = -2;
  noisespeedy = 0;
  noisespeedz = 4;
  noisescale = 24;
  colorLoop = 0;
  drawNoise3d(OceanColors_p);
}

void blackAndWhiteNoise3d() {
  SetupBlackAndWhiteStripedPalette();
  noisespeedx = -12;
  noisespeedy = 0;
  noisespeedz = 0;
  noisescale = 24;
  colorLoop = 0;
  drawNoise3d(blackAndWhiteStripedPalette);
}

void blackAndBlueNoise3d() {
  SetupBlackAndBlueStripedPalette();
  noisespeedx = -4;
  noisespeedy = -4;
  noisespeedz = -4;
  noisescale = 32;
  colorLoop = 0;
  drawNoise3d(blackAndBlueStripedPalette);
}

