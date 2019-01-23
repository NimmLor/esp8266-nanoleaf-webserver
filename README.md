Nanoleaf Web Server
=========

This is a fork of [jasoncoon's esp8266 fastled webserver](https://github.com/jasoncoon/esp8266-fastled-webserver) that was adapted to control the colors of my  [DIY-Nanoleaf Replica](https://www.thingiverse.com/thing:3354082).

[![Nanoleafs](https://github.com/NimmLor/esp8266-nanoleaf-webserver/blob/master/gallery/rgb_preview2.gif?raw=true)](https://www.thingiverse.com/thing:3354082)

Hardware
--------

##### ESP8266

![Wemos D1 Mini Pro & Headers](https://ae01.alicdn.com/kf/HTB1QYHzJKuSBuNjy1Xcq6AYjFXau/ESP8266-ESP-12-ESP12-WeMos-D1-Mini-Modul-Wemos-D1-Mini-WiFi-Entwicklung-Bord-Micro-USB.jpg)

[Wemos D1 mini](http://s.click.aliexpress.com/e/cBDdafPw) is recommended, but any other ESP8266 variant should work too, but it might require an additional step-down converter.



**Addressable Led Strip**

![](https://cdn.pixabay.com/photo/2017/02/27/11/36/digital-led-strip-lights-2103020_960_720.jpg)

I have used 12 led pixels per leaf → 1m of 60 leds/m = 5 leafs

I would recommend buying a strip with 60 leds/m or more.

[WS2812b led strip](http://s.click.aliexpress.com/e/SkQFQqc), make sure you choose IP30 any other IP rating wouldn't make any sense and might not even fit.



Other (optional) hardware:

* [3.3V to 5V Logic Level Shifter](http://s.click.aliexpress.com/e/buDr0PT2) (required if LEDs "glitch")

Features
--------
* Control the colors of individual leafs
* Adjust the brightness
* Change the display pattern
* Adjust the color
* Adapted patterns to look great on the [DIY-Nanoleaf Replica](https://www.thingiverse.com/thing:3354082)
* OTA-Update support



### Upcoming Features

- **Node-RED** integration
  - Custom-Alexa skill
  - Nanoleaf voice control
  - Custom color pattern designer
  - **Node-RED** webinterface to store special patterns persistant
  - Controlling multiple nanoleafs at once

>  these features will be optional and require additional hardware (any linux/windows device that is in the same network)

Webinterface
--------

![Webinterface](https://github.com/NimmLor/esp8266-nanoleaf-webserver/blob/master/gallery/interface.jpg?raw=true)

The web app is stored in SPIFFS (on-board flash memory).

Installing
-----------
The app is installed via the Arduino IDE which can be [downloaded here](https://www.arduino.cc/en/main/software). The ESP8266 boards will need to be added to the Arduino IDE which is achieved as follows. Click File > Preferences and copy and paste the URL "http://arduino.esp8266.com/stable/package_esp8266com_index.json" into the Additional Boards Manager URLs field. Click OK. Click Tools > Boards: ... > Boards Manager. Find and click on ESP8266 (using the Search function may expedite this). Click on Install. After installation, click on Close and then select your ESP8266 board from the Tools > Board: ... menu.

The app depends on the following libraries. They must either be downloaded from GitHub and placed in the Arduino 'libraries' folder, or installed as [described here](https://www.arduino.cc/en/Guide/Libraries) by using the Arduino library manager.

* [FastLED](https://github.com/FastLED/FastLED)
* [Arduino WebSockets](https://github.com/Links2004/arduinoWebSockets)

Download the app code from GitHub using the green Clone or Download button from [GitHub](https://github.com/NimmLor/esp8266-nanoleaf-webserver) and click Download ZIP. Decompress the ZIP file in your Arduino sketch folder.

The web app needs to be uploaded to the ESP8266's SPIFFS.  You can do this within the Arduino IDE after installing the [Arduino ESP8266FS tool](http://esp8266.github.io/Arduino/versions/2.3.0/doc/filesystem.html#uploading-files-to-file-system). An alternative would be to install the [Visual Micro](https://www.visualmicro.com/) plugin for Visual Studio.

With ESP8266FS installed upload the web app using `ESP8266 Sketch Data Upload` command in the Arduino Tools menu.

## Configuration

The most important thing to do is to set the amount of 'leafs' and the amount of led pixels that one 'leaf' contains.

For instance I use 12 leafs (triangles) with a total of 12 pixels in one leaf (=4 leds in each corner of the triangle).

```c++
#define LEAFCOUNT 12
#define PIXELS_PER_LEAF 12
```

Next enter the pin where the *Data* line is connected to, in my case it's pin D4 (you can either write D4 or 2).

`#define DATA_PIN D4`

Another **important** step is to create the **Secrets.h** file. Create a new tab (**ctrl**+**shift**+**n**) and name it *Secrets.h*, this file contains your WIFI credentials and it's structure must look like this:

``````c++
// AP mode password
const char WiFiAPPSK[] = "WIFI_NAME_IF_IN_AP_MODE";

// Wi-Fi network to connect to (if not in AP mode)
char* ssid = "YOUR_WIFI_NAME";
char* password = "YOUR_WIFI_PASSWORD";
``````

If colors appear to be swapped you should change the color order. For me, red and green was swapped so i had to change the color order from *RGB* to *GRB*.

You should also set the milli-amps of your power supply to prevent power overloading. I am using a 3A 5V psu so i defined 3000mA.

`#define MILLI_AMPS 3000`



## Circuit

### Without Logic-Level Converter

![circuit without Logic level converter](https://github.com/NimmLor/esp8266-nanoleaf-webserver/blob/master/gallery/circuit.jpg?raw=true)



### With Logic-Level-Converter (required if leds 'glitch')

![circuit with logic level converter](https://github.com/NimmLor/esp8266-nanoleaf-webserver/blob/master/gallery/circuit_logic_level_Steckplatine.jpg?raw=true)



Technical information
-----------------

Patterns are requested by the app from the ESP8266, so as new patterns are added, they're automatically listed in the app.

The web app is stored in SPIFFS (on-board flash memory).

The web app is a single page app that uses [jQuery](https://jquery.com) and [Bootstrap](http://getbootstrap.com).  It has buttons for On/Off, a slider for brightness, a pattern selector, and a color picker (using [jQuery MiniColors](http://labs.abeautifulsite.net/jquery-minicolors)).  Event handlers for the controls are wired up, so you don't have to click a 'Send' button after making changes.  The brightness slider and the color picker use a delayed event handler, to prevent from flooding the ESP8266 web server with too many requests too quickly.

The only drawback to SPIFFS that I've found so far is uploading the files can be extremely slow, requiring several minutes, sometimes regardless of how large the files are.  It can be so slow that I've been just developing the web app and debugging locally on my desktop (with a hard-coded IP for the ESP8266), before uploading to SPIFFS and testing on the ESP8266.



The firmware implements basic [RESTful web services](https://en.wikipedia.org/wiki/Representational_state_transfer) using the ESP8266WebServer library.  Current values are requested with HTTP GETs, and values are set with POSTs using query string parameters.  It can run in connected or standalone access point modes.
