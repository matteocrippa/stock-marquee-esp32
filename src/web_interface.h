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
            "#tmm-logo{"
            "  margin-top: 100px;"
            "  margin-left: 50%;"
            "  width:50%;"
            "}"
            "</style>"
            " </head>"
            " <body>"
            " <h1>Stock Marquee - Setup</h1>"
            " <p>Enter stock tickers you want to monitor semicolumn separated. (e.g. NKLA;TSLA;)</p>"
            " <form action='/tickers' method='POST'>\r\n"
            " <label for='message'>Message:</label> <input type='text' name='tickers' id='tickers'>""</p>\r\n" 
            " <input type='submit' id='send' value='Save' />\r\n "
            " </form> \r\n"
            "</body>";
