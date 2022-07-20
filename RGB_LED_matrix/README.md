# NodeMCU-RGB-Matrix  

![image info](./images/rainbow_with_powerbank.jpg)

The code is made for a 14 * 14 matrix using WS2812, but it should work for other sizes and LEDs by changing Rows, Columns and WS2812 in "RGB_LED_matrix.ino".
Some of the animations were found on other github pages, and are modified to work here. Links to the original code can be found in "Animations.h" and in the Animations section down under.

## Required Board Manager  

  Go to File>Preferences>Addittional Boards Manager URLs  
  copy and paste <http://arduino.esp8266.com/stable/package_esp8266com_index.json>  
  Go to Tools>Board>Boards Manager  
  Search "esp8266" and install version 2.7.4. This program has not been tested on later versions.  
  Go to Tools>Board>ESP8266 Boards  
  Chose "NodeMCU 1.0 (ESP-12E Module)"  

## Required libraries  

  FastLED  
  Adafruit Neomatrix  
  Adafruit GFX Library  
  Adafruit Neopixel  

## Wiring

![image info](./images/inside.jpg)
![image info](./images/front.jpg)

## Backside

![image info](./images/backside.jpg)

## Animations

### Rainbow

Found on <https://github.com/FastLED/FastLED/blob/master/examples/XYMatrix/XYMatrix.ino>
![image info](./images/rainbow.jpg)

### Sunshine

![image info](./images/sunshine.jpg)

### Confetti

Found on <https://github.com/atuline/FastLED-Demos/blob/master/confetti_pal/confetti_pal.ino>
![image info](./images/confetti.jpg)

### Fire

Found on <https://gist.github.com/StefanPetrick/1ba4584e534ba99ca259c1103754e4c5>
![image info](./images/fire.jpg)

### Fast dots

Found on <https://github.com/atuline/FastLED-Demos/blob/master/dot_beat/dot_beat.ino>
![image info](./images/fast_dots.jpg)

### Corner pulses

![image info](./images/corner_pulses.jpg)

### Random pulses

![image info](./images/random_pulses.jpg)

### Fireworks

![image info](./images/fireworks.jpg)
