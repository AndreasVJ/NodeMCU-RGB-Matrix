// Based on the example code "matrixtest" from Adafruit industries 
// For other layouts see this website https://learn.adafruit.com/adafruit-neopixel-uberguide/neomatrix-library

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
#define PSTR // Make Arduino Due happy
#endif

void scrollingText(String text, int rows, int columns, int pin) {
  breakLoop = false;
  Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(rows, columns, pin,
    NEO_MATRIX_TOP    + NEO_MATRIX_LEFT +
    NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
    NEO_GRB            + NEO_KHZ800);
  
  const uint16_t colors[] = {matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255) };
  
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(40);
  matrix.setTextColor(colors[0]);

  int textLength = text.length(); 
  int x = matrix.width();
  int pass = 0;
  
  while (breakLoop == false) {
    server.handleClient();
    EVERY_N_MILLISECONDS(100) {
      matrix.fillScreen(0);
      matrix.setCursor(x, 3);
      matrix.print(text);
      if(--x < -textLength*6) {
        x = matrix.width();
        if(++pass >= 3) pass = 0;
        matrix.setTextColor(colors[pass]);
      }
      matrix.show();
    }
  }
}
