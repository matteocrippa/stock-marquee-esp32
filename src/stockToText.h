#include <StringSplitter.h>

#include "stock.h"

Stock stockInfo = Stock();
String stockString = "";

unsigned long lastSync = 0;

// refresh data
unsigned long syncEvery = 60000.0 * 10.0; // aka 10 minute

String plusMin(double value) {
    if (value > 0) {
        return "+" + String(value, 2) + "%";
    }else {
        return String(value, 2) + "%";
    }
}

String loadStockInfo(String stocks) {

    if (lastSync == 0 || millis() - lastSync > syncEvery) {

        // reset the string
        stockString = "";

        StringSplitter *splitter = new StringSplitter(stocks, ';', 10);  // new StringSplitter(string_to_split, delimiter, limit)
        int itemCount = splitter->getItemCount();
        Serial.println("Item count: " + String(itemCount));

        for(int i=0; i < itemCount; i++) {
            String stockName = splitter->getItemAtIndex(i);
            if (stockName.length() > 0) {
                stockInfo.get(stockName);
                stockString += " / $" + stockName + " " + plusMin(stockInfo.info.percentage);
            }
        }
        lastSync = millis();
    }

    return stockString;
}