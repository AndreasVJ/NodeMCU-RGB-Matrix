#define FASTLED_ESP8266_RAW_PIN_ORDER
#define ROWS 14
#define COLUMNS 14
#define LED_PIN 4 
#define NUM_LEDS ROWS*COLUMNS

// Lists containing all links on main menu
String games[] =  {"Snake"};
String animations[] = {"Rainbow", "Sunshine", "Fire", "Confetti", "FastDots", "CornerPulses", "RandomPulses", "Fireworks"};

int numberOfGames = sizeof(games) / sizeof(String);
int numberOfAnimations = sizeof(animations) / sizeof(String);

// Global variables used for changing animations and sending commands
bool left = false;
bool down = false;
bool right = false;
bool up = false;
bool enter = false;
bool breakLoop = false;

// Setting "Hello" scrolling text as the first animation after connecting to WiFi
String queue = "Scrolling text";
String text = "Hello";

#include <FastLED.h>
CRGB leds[NUM_LEDS]; //FastLED list containing the colors of each induvidual led
#include "MatrixCords.h"
#include "Website.h"
#include "Text.h"
#include "Snake.h"
#include "Tetris.h"
#include "Animations.h"


void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
  // Garbage signals often turn on some leds when powering up. This clears these leds
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
  server.on("/Tetris", handle_tetris);
  server.on("/SnakeUp", handle_snakeUp);
  server.on("/SnakeLeft", handle_snakeLeft);
  server.on("/SnakeDown", handle_snakeDown);
  server.on("/SnakeRight", handle_snakeRight);

  for (int i = 0; i < numberOfAnimations; i++) {
    makeAnimationLink(animations[i]);
  }
  
  server.onNotFound(handle_NotFound);
  server.begin();
}

/*
 * The program will constantly check for requests from clients. Also while playing an animation or game.
 * Valid request will set breakLoop to true. This will make the program jump out of the current task.
 * queue will be set to some other string. A new animation or game will start based on queue.
 */

void loop() {
  if (queue == "") {
    server.handleClient();
  }
  else {
    breakLoop = false; // Variable used to jump out of animation and game loops. It must be set to false before playing an animation
    if (queue == "Snake") {
      playSnake();
    }
    else if (queue == "Tetris") {
      playTetris();
      Serial.println("done");
    }
    else if (queue == "Scrolling text") {
      scrollingText(text, ROWS, COLUMNS, LED_PIN);
      FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS); // scrollingText uses Adafruit_NeoMatrix. Leds has to be added again for FastLED to function properly        
    }
    else if (queue == "Rainbow") {
      rotatingRainbow();
    }
    else if (queue == "Sunshine") {
      sunshine();
    }
    else if (queue == "Fire") {
      fire();
    }
    else if (queue == "Confetti") {
      confetti();
    }
    else if (queue == "FastDots") {
      fastDots();
    }
    else if (queue == "CornerPulses") {
      cornerPulses();
    }
    else if (queue == "RandomPulses") {
      randomPulses();
    }
    else if (queue == "Fireworks") {
      fireworks();
    }
    else {
      text = "Invalid queue string";
      queue = "Scrolling text";
    }
  }
  
}

// Functions used when a valid request has been received
void handle_mainMenu() {
  server.send(200, "text/html", mainMenuHTML());
  FastLED.clear();
  FastLED.show();
  queue = "";
  breakLoop = true;
}

void handle_snake() {
  server.send(200, "text/html", snakeHTML());
  queue = "Snake";
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

void handle_tetris() {
  server.send(200, "text/html", mainMenuHTML());
  queue = "Tetris";
  breakLoop = true;
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}
