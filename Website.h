#ifndef Website_h
#define Website_h

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "NodeMCU";
const char* password = "12345678";

IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);

String mainMenuHTML(String *links, int numberOfLinks) {
  String html =  "<!DOCTYPE html>";
         html +=     "<html>";
         html +=        "<head>";
         html +=            "<style> html {font-family: Helvetica; text-align: center;}";
         html +=                    "hr {margin-top: 100px; margin-bottom: 100px}";
         html +=                    "a {color:#45A29E; font-size: 128px; margin-right: 50px; margin-left: 50px; text-decoration: none;}";
         html +=            "</style>";
         html +=        "</head>";
         html +=        "<body style=\"font-size: 64px; background-color:#0B0C10; margin-top: 50px; margin-bottom: 50px;\">";
         html +=            "<h1 style=\"color:#FFFFFF;\">Main menu</h1>";
         html +=            "<hr>";
         
         for (int i = 0; i < numberOfLinks; i++) {
           html +=          "<a href=\"/" + links[i] + "\">" + links[i] + "</a>";
           html +=          "<hr>";
         }

         html +=        "</body>";
         html +=    "</html>";
  return html;
}

String snakeHTML() {
  String html =  "<!DOCTYPE html>";
         html +=     "<html>";
         html +=         "<head>";
         html +=             "<style> html { font-family: Helvetica; text-align: center;}";
         html +=                     "hr {margin-top: 100px; margin-bottom: 100px}";
         html +=                     ".arrow {";
         html +=                       "border: solid #45A29E;";
         html +=                       "border-width: 0 70px 70px 0;";
         html +=                       "display: inline-block;";
         html +=                       "padding: 70px;";
         html +=                     "}";
         html +=                     ".right {";
         html +=                       "transform: rotate(-45deg);";
         html +=                       "-webkit-transform: rotate(-45deg);";
         html +=                     "}";
         html +=                     ".left {";
         html +=                       "transform: rotate(135deg);";
         html +=                       "-webkit-transform: rotate(135deg);";
         html +=                     "}";
         html +=                     ".up {";
         html +=                       "transform: rotate(-135deg);";
         html +=                       "-webkit-transform: rotate(-135deg);";
         html +=                     "}";
         html +=                     ".down {";
         html +=                       "transform: rotate(45deg);";
         html +=                       "-webkit-transform: rotate(45deg);";
         html +=                     "}";
         html +=             "</style>";
         html +=         "</head>";
         html +=         "<body style=\"font-size: 64px; background-color:#0B0C10; margin-top: 50px; margin-bottom: 50px;\">";
         html +=             "<h1 style=\"color:#FFFFFF;\">Playing snake</h1>";
         html +=             "<hr>";
         html +=             "<a class=\"up arrow\" href=\"/SnakeUp\"></a>";
         html +=             "<br><br>";
         html +=             "<a style=\"margin-right: 370px;\" class=\"left arrow\" href=\"/SnakeLeft\"></a>";
         html +=             "<a class=\"right arrow\" href=\"/SnakeRight\"></a>";
         html +=             "<br><br>";
         html +=             "<a class=\"down arrow\" href=\"/SnakeDown\"></a>";
         html +=             "<hr>";
         html +=             "<a style=\"color: #C5C6C7; text-decoration: none; margin-right: 90px\" href=\"/\">Main menu</a>";
         html +=             "<a style=\"color: #C5C6C7; text-decoration: none; margin-left: 90px\" href=\"/Snake\">Play again</a>";
         html +=         "</body>";
         html +=     "</html>";
  return html;
}

#endif
