/*

ESP32 WiFi Message Board
by Matteo Crippa

V 0.1 - Initial code - August 18, 2021

*/

#define USE_ADAFRUIT_GFX

#include "EEPROM.h"

// Third party libs
#include <WiFi.h>
#include <WebServer.h>
#include <Adafruit_BusIO_Register.h>
#include <LEDMatrixDriver.hpp>

// headers
#include "arduino_secrets.h"
#include "font.h"
#include "mat_functions.h"
#include "web_interface.h"
#include "stockToText.h"

// Create WebServer instance
WebServer server(80);

// Default stocks to track
String stocksTickers = "NKLA;TSLA;";

//function for handling POST data
void dataHandler() {
  String tickers = server.arg("tickers"); //message from POST data
  Serial.print("Received: ");         //print to serial terminal
  Serial.println(tickers);
  tickers.toUpperCase(); //all incoming string is converted to uppercase since no font for small cases
  stocksTickers = tickers;
  EEPROM.writeString(0, tickers);     //store received message to EEPROM
  EEPROM.commit();                    //commit the save
  server.sendHeader("Location", "/"); //redirect client to home page
  server.send(302);                   //redirect http code

  // reset the sync to force reload
  lastSync = 0;
}

void setup() {
  //This uses EEPROM to store previous message
  //Initialize EEPROM
  if (!EEPROM.begin(1000)) {
    Serial.println("Failed to initialise EEPROM");
    Serial.println("Restarting...");
    delay(1000);
    ESP.restart();
  }
  //Initialize the display
  lmd.setEnabled(true);
  lmd.setIntensity(0); // 0 = low, 10 = high
                       //For debugging
  Serial.begin(9600);

  // Use ESP32 as WiFi Station
  WiFi.mode(WIFI_STA);
  // Initiate WiFi Connection
  WiFi.begin(SECRET_SSID, SECRET_PASS);
  Serial.println("");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  //Print your WiFi's SSID (might be insecure)
  Serial.println(SECRET_SSID);
  Serial.print("IP address: ");
  //Print your local IP address (needed for browsing the app)
  Serial.println(WiFi.localIP());
  server.on("/", []() {
   server.send(200, "text/html", page);
  });
  //POST data handler
  server.on("/tickers", HTTP_POST, dataHandler);
  //start web server
  server.begin();
  //Just stating things
  Serial.println("HTTP server started");
  //At first start, read previous message from EEPROM
  stocksTickers = EEPROM.readString(0);
  // Print stored message to serial port for checking
  Serial.print("Monitoring stocks: ");
  Serial.println(stocksTickers);
}

void loop() {
  // enables webserver handler
  server.handleClient();

  // generates text for stocks
  String message = loadStockInfo(stocksTickers);

  int len = message.length();
  writeToMatrix(message, len); 
                               
  // Toggle display of the new framebuffer
  lmd.display();
  
  // Wait to let the human read the display
  delay(ANIM_DELAY);
  
  // Advance to next coordinate
  if (--x < len * -8) {
    x = LEDMATRIX_WIDTH;
  }

  //adjust this for faster/slower scrolling
  delay(100); 
}
