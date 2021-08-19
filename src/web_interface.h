/*

This file contains HTML code for app of WiFi Message Board

*/

const String page PROGMEM = "<head>"
            " <meta name='viewport' content='width=device-width, initial-scale=1.0'>"
            " <link href='https://fonts.googleapis.com/css2?family=Roboto:wght@300&display=swap' rel='stylesheet'>"
            " <style>"
            " body{"
            " background-color:white;"
            " font-family: 'Roboto', sans-serif;" 
            "}"
            "</style>"
            " </head>"
            " <body>"
            " <h1>Stock Marquee - Setup</h1>"
            " <p>Enter stock tickers you want to monitor comma separated. (e.g. NKLA,TSLA)</p>"
            " <form action='/tickers' method='POST'>\r\n"
            " <label for='message'>Message:</label> <input type='text' name='tickers' id='tickers'>""</p>\r\n" 
            " <input type='submit' id='send' value='Save' />\r\n "
            " </form> \r\n"
            "</body>";
