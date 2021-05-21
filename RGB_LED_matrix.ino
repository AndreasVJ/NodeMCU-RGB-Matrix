#define FASTLED_ESP8266_RAW_PIN_ORDER
#define ROWS 14
#define COLUMNS 14
#define LED_PIN 4

// Global variables used for changing animations and sending commands
bool left = false;
bool down = false;
bool right = false;
bool up = false;
bool enter = false;
bool breakLoop = false;

// Setting "Hello" scrolling text as the first animation after connecting to WiFi
String queue = "scrolling text";
String text = "Hello";

#include <FastLED.h>
#include "MatrixCords.h"
#include "Website.h"
#include "Text.h"
#include "Snake.h"
#include "Animations.h"

#define NUM_LEDS ROWS*COLUMNS

CRGB leds[NUM_LEDS]; //FastLED list containing the colors of each induvidual pixel

// List containing all links on main menu. Adding new strings will display them as links on main menu
String events[] = {"Snake", "Rainbow", "Sunshine", "Fire", "Confetti", "FastDots"};
int numberOfEvents = sizeof(events) / sizeof(String);

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 1500);
  // Garbage signals often turn on some pixels when powering up. This clears these pixels
  FastLED.clear();
  FastLED.show();
  
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password); // ssid and password variables can be changed in "Website.h"
  Serial.println("");

  // Simple animation while waiting for connection to WiFi
  int column = 0;
  int hue = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    for (int i = 0; i<ROWS; i++) {
      leds[serpentine_xy(column, i)].setHSV(hue,255,80);
      hue += round(255/ROWS);
    }
    hue = 0;
    FastLED.show();
    if (column == ROWS-1) {
      FastLED.clear();
      column = 0;
    }
    else {
      column++;
    }
  }
  // Clear animation from before
  FastLED.clear();
  FastLED.show();

  // printing name of WiFi and IP address. Write the IP address in a browser to access server
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  // Adding responses to URLs. All handle functions can be found at the end of the file
  server.on("/", handle_mainMenu);
  server.on("/Snake", handle_snake);
  server.on("/SnakeUp", handle_snakeUp);
  server.on("/SnakeLeft", handle_snakeLeft);
  server.on("/SnakeDown", handle_snakeDown);
  server.on("/SnakeRight", handle_snakeRight);
  server.on("/Rainbow", handle_rainbow);
  server.on("/Sunshine", handle_sunshine);
  server.on("/Fire", handle_fire);
  server.on("/Confetti", handle_confetti);
  server.on("/FastDots", handle_fastDots);
  server.onNotFound(handle_NotFound);
  server.begin();
}

/*
 * The program will constantly check for requests from clients. Also while playing an animation or game.
 * Valid request will set breakLoop to true. This will make the program jump out of the current task.
 * queue will also be set to some other string. A new animation or game will start based on queue.
 */

void loop() {
  if (queue == "") {
    server.handleClient();
  }
  else {
    breakLoop = false; // Variable used to jump out of animation and game loops. It must be set to false before playing an animation
    if (queue == "snake") {
      queue = ""; // Must be set to empty string to prevent animation from playing again after request to leave
      playSnake(ROWS, COLUMNS, 1000, leds);
    }
    else if (queue == "scrolling text") {
      queue = "";
      scrollingText(text, ROWS, COLUMNS, LED_PIN);
      FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS); // scrollingText uses Adafruit_NeoMatrix. Leds has to be added again for FastLED to function properly        
    }
    else if (queue == "rainbow") {
      queue = "";
      rotatingRainbow(ROWS, COLUMNS, leds);
    }
    else if (queue == "sunshine") {
      queue = "";
      sunshine(ROWS, COLUMNS, leds);
    }
    else if (queue == "fire") {
      queue = "";
      fire(ROWS, COLUMNS, leds);
    }
    else if (queue == "confetti") {
      queue = "";
      confetti(ROWS, COLUMNS, leds);
    }
    else if (queue == "fastDots") {
      queue = "";
      fastDots(ROWS, COLUMNS, leds);
    }
  }
  
}

// Functions used when a valid request has been received
void handle_mainMenu() {
  server.send(200, "text/html", mainMenuHTML(events, numberOfEvents));
  FastLED.clear();
  FastLED.show();
  breakLoop = true;
}

void handle_snake() {
  server.send(200, "text/html", snakeHTML());
  queue = "snake";
  breakLoop = true;
}

void handle_snakeUp() {
  server.send(200, "text/html", snakeHTML());
  up = true;
}
void handle_snakeLeft() {
  server.send(200, "text/html", snakeHTML());
  left = true;
}

void handle_snakeRight() {
  server.send(200, "text/html", snakeHTML());
  right = true;
}

void handle_snakeDown() {
  server.send(200, "text/html", snakeHTML());
  down = true;
}

void handle_rainbow() {
  server.send(200, "text/html", mainMenuHTML(events, numberOfEvents));
  queue = "rainbow";
  breakLoop = true;
}

void handle_sunshine() {
  server.send(200, "text/html", mainMenuHTML(events, numberOfEvents));
  queue = "sunshine";
  breakLoop = true;
}

void handle_fire() {
  server.send(200, "text/html", mainMenuHTML(events, numberOfEvents));
  queue = "fire";
  breakLoop = true;
}

void handle_confetti() {
  server.send(200, "text/html", mainMenuHTML(events, numberOfEvents));
  queue = "confetti";
  breakLoop = true;
}

void handle_fastDots() {
  server.send(200, "text/html", mainMenuHTML(events, numberOfEvents));
  queue = "fastDots";
  breakLoop = true;
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}
