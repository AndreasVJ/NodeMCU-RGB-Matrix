# NodeMCU-RGB-Matrix  

![image info](https://github.com/AndreasVJ/NodeMCU-RGB-Matrix/blob/main/images/rainbow_with_powerbank.JPG?raw=true)

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

![image info](https://github.com/AndreasVJ/NodeMCU-RGB-Matrix/blob/main/images/inside.JPG?raw=true)
![image info](https://github.com/AndreasVJ/NodeMCU-RGB-Matrix/blob/main/images/front.JPG)

## Backside

![image info](https://github.com/AndreasVJ/NodeMCU-RGB-Matrix/blob/main/images/backside.JPG?raw=true)

## Animations

### Rainbow

Found on <https://github.com/FastLED/FastLED/blob/master/examples/XYMatrix/XYMatrix.ino>
![image info](https://github.com/AndreasVJ/NodeMCU-RGB-Matrix/blob/main/images/rainbow.JPG?raw=true)

### Sunshine

![image info](https://github.com/AndreasVJ/NodeMCU-RGB-Matrix/blob/main/images/sunshine.JPG?raw=true)

### Confetti

Found on <https://github.com/atuline/FastLED-Demos/blob/master/confetti_pal/confetti_pal.ino>
![image info](https://github.com/AndreasVJ/NodeMCU-RGB-Matrix/blob/main/images/confetti.JPG?raw=true)

### Fire

Found on <https://gist.github.com/StefanPetrick/1ba4584e534ba99ca259c1103754e4c5>
![image info](https://github.com/AndreasVJ/NodeMCU-RGB-Matrix/blob/main/images/fire.JPG?raw=true)

### Fast dots

Found on <https://github.com/atuline/FastLED-Demos/blob/master/dot_beat/dot_beat.ino>
![image info](https://github.com/AndreasVJ/NodeMCU-RGB-Matrix/blob/main/images/fast_dots.JPG?raw=true)

### Corner pulses

![image info](https://github.com/AndreasVJ/NodeMCU-RGB-Matrix/blob/main/images/corner_pulses.JPG?raw=true)

### Random pulses

![image info](https://github.com/AndreasVJ/NodeMCU-RGB-Matrix/blob/main/images/random_pulses.JPG?raw=true)

### Fireworks

![image info](https://github.com/AndreasVJ/NodeMCU-RGB-Matrix/blob/main/images/fireworks.JPG?raw=true)
