# NodeMCU-RGB-Matrix 
The code is made for a 14 * 14 matrix using WS2812, but it should work for other sizes.
Most of the animations were found on other github pages. Links to these can be found in "Animations.h".

# Required Board:  
  Go to File>Preferences>Addittional Boards Manager URLs  
  copy and paste http://arduino.esp8266.com/stable/package_esp8266com_index.json  
  Go to Tools>Board>Boards Manager  
  Search "esp8266" and install version 2.7.4. Version 3.0.0 turns on the first led when it receives commands over wifi.
  Go to Tools>Board>ESP8266 Boards  
  Chose "NodeMCU 1.0 (ESP-12E Module)"  

# Required libraries:  
  FastLED  
  Adafruit Neomatrix  
  Adafruit GFX Library  
  Adafruit Neopixel  
  
