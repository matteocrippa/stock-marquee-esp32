#include "network_stock.h"

NetworkStock net = NetworkStock();
String stockString = "";

unsigned long lastSync = 0;

// refresh data every
unsigned long syncEvery = 60000.0 * 10.0; // 10 minutes

// force add a + if value is positive
String plusMin(double value) {
    if (value > 0) {
        return "+" + String(value, 2) + "%";
    }else {
        return String(value, 2) + "%";
    }
}

// generates the text to be shown according the stocks
// and takes care of refreshing each syncEvery
String loadStockInfo(String stocks) {

    if (lastSync == 0 || millis() - lastSync > syncEvery) {

        // reset the string
        stockString = "";

        // retrieve stocks
        Stock **data = net.get(stocks);
        int itemsCount = net.elements;
        
        for(int i=0; i < itemsCount; i++) {
            Stock *stock = data[i];
            if (stock->ticker.length() > 0) {
                stockString += " / $" + stock->ticker + " " + plusMin(stock->percentage);
            }
        }

        lastSync = millis();
    }
    return stockString;
}