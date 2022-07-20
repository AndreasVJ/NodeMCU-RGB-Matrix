// Sends pulses with random colors from the corners
void cornerPulses() {
  int circleWidth = 3;
  int brightnessVariation = 100/circleWidth; // might need to be changed if using other circleWidths
  uint8_t hue = random8();
  int startCorner = 1; 
  int yOffset = 0;  // Start position of pulse
  int xOffset = 0;
  float distance[ROWS][COLUMNS];  // List that contains the distance from each led to the circle pulse
  float maxDistance;  // Max distance before pulse is out of range
  
  for (int y = 0; y < ROWS; y++) {
    for (int x = 0; x < COLUMNS; x++) {
      distance[x][y] = sqrt(pow((x-xOffset),2) + pow((y-yOffset),2)) + circleWidth;
    }
  }
  maxDistance = distance[ROWS-1][COLUMNS-1] + circleWidth;

  while (breakLoop == false) {
    server.handleClient();
    EVERY_N_MILLISECONDS(10) {
      FastLED.clear();
      for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLUMNS; x++) {
          distance[x][y] -= 0.2; // Simulates a pulse by decreasing the distance from every led
          if (abs(distance[x][y]) < circleWidth) {  // Turns on an led if the distance from the pulse is less than the width
            leds[serpentine_xy(x, y)].setHSV(hue,255,(circleWidth*1.25 - abs(distance[x][y]))*brightnessVariation); // leds further away from the pulse will have a lower brigthness
          }
        }
      }
      FastLED.show();
      if (abs(distance[xOffset][yOffset]) > maxDistance) {  // Checks if pulse is out of range
        startCorner++;
        switch(startCorner) { // Changes the starting corner of the next pulse by changing the x and y offset
          case 1:
            xOffset = 0;
            yOffset = 0;
            break;
          case 2:
            xOffset = COLUMNS-1;
            yOffset = ROWS-1;
            break;
          case 3:
            xOffset = COLUMNS-1;
            yOffset = 0;
            break;
          case 4:
            startCorner = 0;
            xOffset = 0;
            yOffset = ROWS-1;
            break;
        }
        hue += 50;  // Changes color
        for (int y = 0; y < ROWS; y++) {
          for (int x = 0; x < COLUMNS; x++) {
            distance[x][y] = sqrt(pow((x-xOffset),2) + pow((y-yOffset),2)) + circleWidth; // New list of pulse distances based on x and y offset
          }
        }
      }
    }
  }
}

// Same as the animation above, but the pulses starts at random locations
void randomPulses() {
  int circleWidth = 2;
  int brightnessVariation = 100/circleWidth;
  uint8_t hue = random8();
  int yOffset = random(0, ROWS);
  int xOffset = random(0, COLUMNS);
  float distance[ROWS][COLUMNS];
  float maxDistance = 0;
  
  for (int y = 0; y < ROWS; y++) {
    for (int x = 0; x < COLUMNS; x++) {
      distance[x][y] = sqrt(pow((x-xOffset),2) + pow((y-yOffset),2)) + circleWidth;
      if (distance[x][y] > maxDistance) {
        maxDistance = distance[x][y];
      }
    }
  }
  while (breakLoop == false) {
    server.handleClient();
    EVERY_N_MILLISECONDS(10) {
      FastLED.clear();
      for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLUMNS; x++) {
          distance[x][y] -= 0.2;
          if (abs(distance[x][y]) < circleWidth) {
            leds[serpentine_xy(x, y)].setHSV(hue,255,(circleWidth*1.25 - abs(distance[x][y]))*brightnessVariation);
          }
        }
      }
      FastLED.show();
      if (abs(distance[xOffset][yOffset]) > maxDistance) {
        yOffset = random(0, ROWS);
        xOffset = random(0, COLUMNS);
        hue += 50;
        maxDistance = 0;
        for (int y = 0; y < ROWS; y++) {
          for (int x = 0; x < COLUMNS; x++) {
            distance[x][y] = sqrt(pow((x-xOffset),2) + pow((y-yOffset),2)) + circleWidth;
            if (distance[x][y] > maxDistance) {
              maxDistance = distance[x][y];
            }
          }
        }
      }
    }
  }
}

// Same as above, but the leds are turned off with the fadeToBlackBy function
void fireworks() {
  int circleWidth = 1;
  int brightnessVariation = 100/circleWidth;
  uint8_t hue = random8();
  int yOffset = random(0, ROWS);
  int xOffset = random(0, ROWS);
  float distance[ROWS][COLUMNS];
  int maxDistance = 0;
  
  for (int y = 0; y < ROWS; y++) {
    for (int x = 0; x < COLUMNS; x++) {
      distance[x][y] = sqrt(pow((x-xOffset),2) + pow((y-yOffset),2)) + circleWidth;
      if (distance[x][y] > maxDistance) {
        maxDistance = distance[x][y];
      }
    }
  }
  while (breakLoop == false) {
    server.handleClient();
    EVERY_N_MILLISECONDS(25) {
      fadeToBlackBy(leds, NUM_LEDS, 1);
    }
    EVERY_N_MILLISECONDS(10) {
      for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLUMNS; x++) {
          distance[x][y] -= 0.1;
          if (abs(distance[x][y]) < circleWidth) {
            leds[serpentine_xy(x, y)].setHSV(hue,255,(circleWidth*1.25 - abs(distance[x][y]))*brightnessVariation);
          }
        }
      }
      FastLED.show();
      if (abs(distance[int(xOffset)][int(yOffset)]) > maxDistance) {
        hue += 40;
        yOffset = random(0, ROWS);
        xOffset = random(0, ROWS);
        maxDistance = 0;
        for (int y = 0; y < ROWS; y++) {
          for (int x = 0; x < COLUMNS; x++) {
            distance[x][y] = sqrt(pow((x-xOffset),2) + pow((y-yOffset),2)) + circleWidth;
            if (distance[x][y] > maxDistance) {
              maxDistance = distance[x][y];
            }
          }
        }
      }
    }
  }
}


// Found on https://github.com/atuline/FastLED-Demos/blob/master/dot_beat/dot_beat.ino
void fastDots() {
  // Define variables used by the sequences.
  int numLeds = ROWS*COLUMNS;
  int   thisdelay =   10;                                       // A delay value for the sequence(s)
  uint8_t   count =   0;                                        // Count up to 255 and then reverts to 0
  uint8_t fadeval = 224;                                        // Trail behind the LED's. Lower => faster fade.
  uint8_t bpm = 30;

  while (breakLoop == false) {
    server.handleClient();
    uint8_t inner = beatsin8(bpm, numLeds/4, numLeds/4*3);    // Move 1/4 to 3/4
    uint8_t outer = beatsin8(bpm, 0, numLeds-1);               // Move entire length
    uint8_t middle = beatsin8(bpm, numLeds/3, numLeds/3*2);   // Move 1/3 to 2/3
  
    leds[middle] = CRGB::Purple;
    leds[inner] = CRGB::Blue;
    leds[outer] = CRGB::Aqua;
  
    nscale8(leds,numLeds,fadeval);                             // Fade the entire array. Or for just a few LED's, use  nscale8(&leds[2], 5, fadeval);
    FastLED.show();
  }
}



// Found on https://github.com/atuline/FastLED-Demos/blob/master/confetti_pal/confetti_pal.ino
void confetti() {
  int numLeds = ROWS*COLUMNS;
  CRGBPalette16 currentPalette;
  CRGBPalette16 targetPalette;
  TBlendType    currentBlending = LINEARBLEND;;                                // NOBLEND or LINEARBLEND
  
  // Define variables used by the sequences.
  uint8_t  thisfade = 8;                                        // How quickly does it fade? Lower = slower fade rate.
  int       thishue = 50;                                       // Starting hue.
  uint8_t   thisinc = 1;                                        // Incremental value for rotating hues
  uint8_t   thissat = 100;                                      // The saturation, where 255 = brilliant colours.
  uint8_t   thisbri = 255;                                      // Brightness of a sequence. Remember, max_bright is the overall limiter.
  int       huediff = 256;                                      // Range of random #'s to use for hue
  uint8_t thisdelay = 5;                                        // We don't need much delay (if any)
  uint8_t max_bright = 192;                                      // Overall brightness definition. It can be changed on the fly.

  while (breakLoop == false) {
    server.handleClient();
    uint8_t secondHand = (millis() / 1000) % 15;                // IMPORTANT!!! Change '15' to a different value to change duration of the loop.
    static uint8_t lastSecond = 99;                             // Static variable, means it's only defined once. This is our 'debounce' variable.
    if (lastSecond != secondHand) {                             // Debounce to make sure we're not repeating an assignment.
      lastSecond = secondHand;
      switch(secondHand) {
        case  0: targetPalette = OceanColors_p; thisinc=1; thishue=192; thissat=255; thisfade=2; huediff=255; break;  // You can change values here, one at a time , or altogether.
        case  5: targetPalette = LavaColors_p; thisinc=2; thishue=128; thisfade=8; huediff=64; break;
        case 10: targetPalette = ForestColors_p; thisinc=1; thishue=random16(255); thisfade=1; huediff=16; break;      // Only gets called once, and not continuously for the next several seconds. Therefore, no rainbows.
        case 15: break;                                         // Here's the matching 15 for the other one.
      }
    }
    EVERY_N_MILLISECONDS(100) {
      uint8_t maxChanges = 24; 
      nblendPaletteTowardPalette(currentPalette, targetPalette, maxChanges);   // AWESOME palette blending capability.
    }
    EVERY_N_MILLISECONDS(thisdelay) {                           // FastLED based non-blocking delay to update/display the sequence.
      fadeToBlackBy(leds, numLeds, thisfade);                    // Low values = slower fade.
    int pos = random16(numLeds);                               // Pick an LED at random.
    leds[pos] = ColorFromPalette(currentPalette, thishue + random16(huediff)/4 , thisbri, currentBlending);
    thishue = thishue + thisinc;                                // It increments here.
    }
    FastLED.show();
  }
}

// Found on https://github.com/FastLED/FastLED/blob/master/examples/XYMatrix/XYMatrix.ino
void rotatingRainbow() {
  breakLoop = false;
  while (breakLoop == false) {
    server.handleClient();
    uint32_t ms = millis();
    int32_t yHueDelta32 = ((int32_t)cos16( ms * (27/1) ) * (350 / COLUMNS));
    int32_t xHueDelta32 = ((int32_t)cos16( ms * (39/1) ) * (310 / ROWS));
    uint8_t lineStartHue = ms / 65536;
      for( uint8_t y = 0; y < COLUMNS; y++) {
        lineStartHue += yHueDelta32 / 32768;
        uint8_t pixelHue = lineStartHue;      
        for( uint8_t x = 0; x < ROWS; x++) {
          pixelHue += xHueDelta32 / 32768;
          leds[ serpentine_xy(x, y)]  = CHSV( pixelHue, 255, 255);
        }
      }
    FastLED.show();
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

// Gives all leds a color from the palette above. Gradually changes the positions on the palette
void sunshine() {
  breakLoop = false;
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


// Found on https://gist.github.com/StefanPetrick/1ba4584e534ba99ca259c1103754e4c5
void fire() {
  uint32_t scale_x;
  uint32_t scale_y;
  
  // storage for the noise data
  // adjust the size to suit your setup
  uint8_t noise[16][16];
  
  // heatmap data with the size matrix width * height
  uint8_t heat[196];
  CRGBPalette16 Pal = HeatColors_p;
  uint8_t Width  = COLUMNS;
  uint8_t Height = ROWS;
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
      for (uint8_t i = 0; i < ROWS; i++) {
        uint32_t ioffset = scale_x * (i - CentreX);
        for (uint8_t j = 0; j < COLUMNS; j++) {
          uint32_t joffset = scale_y * (j - CentreY);
          uint16_t data = ((inoise16(x + ioffset, y + joffset, z)) + 1);
          noise[i][j] = data >> 8;
        }
      }
    
    
      // Draw the first (lowest) line - seed the fire.
      // It could be random pixels or anything else as well.
      for (uint8_t x = 0; x < ROWS; x++) {
        // draw
        leds[serpentine_xy(x, COLUMNS-1)] = ColorFromPalette( Pal, noise[x][0]);
        // and fill the lowest line of the heatmap, too
        heat[serpentine_xy(x, COLUMNS-1)] = noise[x][0];
      }
    
      // Copy the heatmap one line up for the scrolling.
      for (uint8_t y = 0; y < COLUMNS - 1; y++) {
        for (uint8_t x = 0; x < ROWS; x++) {
          heat[serpentine_xy(x, y)] = heat[serpentine_xy(x, y + 1)];
        }
      }
    
      // Scale the heatmap values down based on the independent scrolling noise array.
      for (uint8_t y = 0; y < COLUMNS - 1; y++) {
        for (uint8_t x = 0; x < ROWS; x++) {
    
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
      for (uint8_t y = 0; y < COLUMNS - 1; y++) {
        for (uint8_t x = 0; x < ROWS; x++) {
          leds[serpentine_xy(x, y)] = ColorFromPalette( Pal, heat[serpentine_xy(x, y)]);
        }
      }
    
      // Done. Bring it on!
      FastLED.show();
    }
  }
}
