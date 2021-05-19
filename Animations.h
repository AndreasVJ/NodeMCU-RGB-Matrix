

// Hentet og modifisert fra https://github.com/FastLED/FastLED/blob/master/examples/XYMatrix/XYMatrix.ino
void rotatingRainbow(int rows, int columns, CRGB leds[]) {
  breakLoop = false;
  while (breakLoop == false) {
    server.handleClient();
    uint32_t ms = millis();
    int32_t yHueDelta32 = ((int32_t)cos16( ms * (27/1) ) * (350 / columns));
    int32_t xHueDelta32 = ((int32_t)cos16( ms * (39/1) ) * (310 / rows));
    uint8_t lineStartHue = ms / 65536;
      for( uint8_t y = 0; y < columns; y++) {
        lineStartHue += yHueDelta32 / 32768;
        uint8_t pixelHue = lineStartHue;      
        for( uint8_t x = 0; x < rows; x++) {
          pixelHue += xHueDelta32 / 32768;
          leds[ serpentine_xy(x, y)]  = CHSV( pixelHue, 255, 255);
        }
      }
    FastLED.show();
  }
}


void red(int rows, int columns, CRGB leds[]) {
  breakLoop = false;
  int NUM_LEDS = rows * columns;
  for (int i = 0; i<NUM_LEDS; i++) {
    leds[i].setRGB(255,0,0);
  }
  FastLED.show();
  while (breakLoop == false) {
    server.handleClient();
  }
}

DEFINE_GRADIENT_PALETTE(sunshine_gp) {
    0, 120, 0, 0,
    2, 179, 22, 0,
    51, 255, 104, 0,
    85, 167, 22, 18,
    135, 100, 0, 103,
    198, 16, 0, 130,
    255, 120, 0, 0
};

// Gir alle lysene en tilfeldig posisjon fra fargepalleten over. Justerer deretter gradvis posisjonen for å lage en animasjon
void sunshine(int numberOfRows, int numberOfColumns, CRGB leds[]) {
  breakLoop = false;
  int NUM_LEDS = numberOfRows * numberOfColumns;
  uint8_t colorIndex[NUM_LEDS];
  
  CRGBPalette16 sunshinePalette = sunshine_gp;
  
  for (int i = 0; i < NUM_LEDS; i++) {
    colorIndex[i] = random8();
  }

  while (breakLoop == false) {
    server.handleClient();

    EVERY_N_MILLISECONDS(1) {
      for (int i = 0; i <NUM_LEDS; i++) {
        colorIndex[i]++;
      }
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette(sunshinePalette, colorIndex[i]);
      }
      FastLED.show();
    }
  }
}


void greenRays(int numberOfRows, int numberOfColumns, CRGB leds[]) {
  int greenValue = 206;
  while (true) {
    FastLED.clear();
    for (int i = 0; i<numberOfRows*numberOfColumns; i++) {
      leds[i].setRGB(0, greenValue, greenValue);
      if (i<10) {
        for (int n = 1; n<i; n++) {
          leds[i-n].setRGB(0, greenValue-n*2, greenValue-n*10);
        }
      }
      else {
        for (int n = 0; n<10; n++) {
          leds[i-n].setRGB(0, greenValue-n*2, greenValue-n*10);
        }
        leds[i-10].setRGB(0, 0, 0);
      }
      FastLED.show();
      delay(10);
    }
  }
}

// Hentet og modifisert fra https://gist.github.com/StefanPetrick/1ba4584e534ba99ca259c1103754e4c5
void fire(int rows, int columns, CRGB leds[]) {
  uint32_t scale_x;
  uint32_t scale_y;
  
  // storage for the noise data
  // adjust the size to suit your setup
  uint8_t noise[16][16];
  
  // heatmap data with the size matrix width * height
  uint8_t heat[196];
  CRGBPalette16 Pal = HeatColors_p;
  uint8_t Width  = 14;
  uint8_t Height = 14;
  uint8_t CentreX =  (Width / 2) - 1;
  uint8_t CentreY = (Height / 2) - 1;

  uint32_t x;
  uint32_t y;
  uint32_t z;
  
  while(breakLoop == false) {
    server.handleClient();
    EVERY_N_MILLISECONDS(10) {
      // get one noise value out of a moving noise space
      uint16_t ctrl1 = inoise16(11 * millis(), 0, 0);
      // get another one
      uint16_t ctrl2 = inoise16(13 * millis(), 100000, 100000);
      // average of both to get a more unpredictable curve
      uint16_t  ctrl = ((ctrl1 + ctrl2) / 2);
    
      // this factor defines the general speed of the heatmap movement
      // high value = high speed
      uint8_t speed = 27;
    
      // here we define the impact of the wind
      // high factor = a lot of movement to the sides
      x = 3 * ctrl * speed;
    
      // this is the speed of the upstream itself
      // high factor = fast movement
      y = 15 * millis() * speed;
    
      // just for ever changing patterns we move through z as well
      z = 3 * millis() * speed ;
    
      // ...and dynamically scale the complete heatmap for some changes in the
      // size of the heatspots.
      // The speed of change is influenced by the factors in the calculation of ctrl1 & 2 above.
      // The divisor sets the impact of the size-scaling.
      scale_x = ctrl1 / 2;
      scale_y = ctrl2 / 2;
    
      // Calculate the noise array based on the control parameters.
      uint8_t layer = 0;
      for (uint8_t i = 0; i < rows; i++) {
        uint32_t ioffset = scale_x * (i - CentreX);
        for (uint8_t j = 0; j < columns; j++) {
          uint32_t joffset = scale_y * (j - CentreY);
          uint16_t data = ((inoise16(x + ioffset, y + joffset, z)) + 1);
          noise[i][j] = data >> 8;
        }
      }
    
    
      // Draw the first (lowest) line - seed the fire.
      // It could be random pixels or anything else as well.
      for (uint8_t x = 0; x < rows; x++) {
        // draw
        leds[serpentine_xy(x, columns-1)] = ColorFromPalette( Pal, noise[x][0]);
        // and fill the lowest line of the heatmap, too
        heat[serpentine_xy(x, columns-1)] = noise[x][0];
      }
    
      // Copy the heatmap one line up for the scrolling.
      for (uint8_t y = 0; y < columns - 1; y++) {
        for (uint8_t x = 0; x < rows; x++) {
          heat[serpentine_xy(x, y)] = heat[serpentine_xy(x, y + 1)];
        }
      }
    
      // Scale the heatmap values down based on the independent scrolling noise array.
      for (uint8_t y = 0; y < columns - 1; y++) {
        for (uint8_t x = 0; x < rows; x++) {
    
          // get data from the calculated noise field
          uint8_t dim = noise[x][y];
    
          // This number is critical
          // If it´s to low (like 1.1) the fire dosn´t go up far enough.
          // If it´s to high (like 3) the fire goes up too high.
          // It depends on the framerate which number is best.
          // If the number is not right you loose the uplifting fire clouds
          // which seperate themself while rising up.
          dim = dim / 1.4;
    
          dim = 255 - dim;
    
          // here happens the scaling of the heatmap
          heat[serpentine_xy(x, y)] = scale8(heat[serpentine_xy(x, y)] , dim);
        }
      }
    
      // Now just map the colors based on the heatmap.
      for (uint8_t y = 0; y < columns - 1; y++) {
        for (uint8_t x = 0; x < rows; x++) {
          leds[serpentine_xy(x, y)] = ColorFromPalette( Pal, heat[serpentine_xy(x, y)]);
        }
      }
    
      // Done. Bring it on!
      FastLED.show();
    }
  }
}