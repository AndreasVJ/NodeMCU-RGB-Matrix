#define FASTLED_ESP8266_RAW_PIN_ORDER
#define ROWS 14
#define COLUMNS 14
#define LED_PIN 4

// Globale variabler som brukes for å utføre kommandoer
bool left = false;
bool down = false;
bool right = false;
bool up = false;
bool enter = false;
bool breakLoop = false;

String queue = "scrolling text";
String text = "Hello";

#include <FastLED.h>
#include "MatrixCords.h"
#include "Website.h"
#include "Text.h"
#include "Snake.h"
#include "Animations.h"

#define NUM_LEDS ROWS*COLUMNS

CRGB leds[NUM_LEDS]; //Liste som inneholder fargen til alle lysene

String events[] = {"Snake", "Rainbow", "Sunshine", "Fire", "Confetti"};
int numberOfEvents = sizeof(events) / sizeof(String);

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 1500); //Begrenser strømforbruket til 5v og 1500ma
  FastLED.clear();
  FastLED.show();
  
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  int column = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    for (int i = 0; i<ROWS; i++) {
      leds[serpentine_xy(column, i)].setRGB(0, 75, 75);
    }
    FastLED.show();
    if (column == ROWS-1) {
      FastLED.clear();
      column = 0;
    }
    else {
      column++;
    }
  }
  FastLED.clear();
  FastLED.show();
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

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
  server.onNotFound(handle_NotFound);
  server.begin();
}


void loop() {
  if (queue == "") {
    server.handleClient();
  }
  else {
    breakLoop = false; // Må settes til false for å ikke hoppe ut av neste loop med en gang
    if (queue == "snake") {
      queue = "";
      playSnake(ROWS, COLUMNS, 1000, leds);
    }
    else if (queue == "scrolling text") {
      queue = "";
      scrollingText(text, ROWS, COLUMNS, LED_PIN);
      FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS); // scrollingText bruker Adafruit_NeoMatrix. Må derfor definere lysene på nytt for FastLED
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
  }
  
}

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

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}
