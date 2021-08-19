#include "EEPROM.h"

#include <ArduinoHttpClient.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

typedef struct {
    String ticker;
    double value;
    double percentage;
    bool isUpTrend;
} StockInfo;

class Stock {
    private:
        WiFiClientSecure wifi;
        String kHostname = "query1.finance.yahoo.com";
        HttpClient client = HttpClient(wifi, kHostname, 443);

    public:
        StockInfo info;
        bool get(String ticker) {

            String path = "/v7/finance/quote?symbols="+ticker;
            client.get(path);
            Serial.print(path);

            int statusCode = client.responseStatusCode();
            String response = client.responseBody();

            Serial.println();
            Serial.print("Status code: ");
            Serial.println(statusCode);
            Serial.print("Response: ");
            Serial.println(response);

            DynamicJsonDocument doc(1024);
            deserializeJson(doc, response);

            info.ticker = ticker;
            info.value = doc["quoteResponse"]["result"][0]["regularMarketPrice"];
            info.percentage = doc["quoteResponse"]["result"][0]["regularMarketChangePercent"];

            return true;
        }
};