#include "EEPROM.h"

#include <ArduinoHttpClient.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

#include "stock.h"

class NetworkStock {
    private:
        WiFiClientSecure wifi;
        String kHostname = "query1.finance.yahoo.com";
        HttpClient client = HttpClient(wifi, kHostname, 443);

    public:
        int elements = 0;
        Stock **get(String tickers) {

            String path = "/v7/finance/quote?symbols="+tickers;
            client.get(path);
            // Serial.print(path);

            // int statusCode = client.responseStatusCode();
            String response = client.responseBody();

            // Serial.println();
            // Serial.print("Status code: ");
            // Serial.println(statusCode);
            // Serial.print("Response: ");
            // Serial.println(response);

            DynamicJsonDocument doc(8192);

            DeserializationError error = deserializeJson(doc, response);

            if (error) {
                Serial.print(F("deserializeJson() failed: "));
                Serial.println(error.f_str());
                return NULL;
            }

            JsonArray quoteResponse_result = doc["quoteResponse"]["result"];

            // Serial.print("Items: ");
            // Serial.println(quoteResponse_result.size());

            elements = quoteResponse_result.size();

            Stock **data = NULL;
            data = (Stock **)calloc(elements+1, sizeof(Stock *));

            for(int i=0;i<elements;i++) {
                Stock *stock = new Stock();
                stock->value = quoteResponse_result[i]["regularMarketPrice"];
                stock->percentage = quoteResponse_result[i]["regularMarketChangePercent"];
                stock->ticker = quoteResponse_result[i]["symbol"].as<String>();
                data[i] = stock;
            }

            return data;
        }
};