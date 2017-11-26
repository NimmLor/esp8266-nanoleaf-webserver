//#include <DNSServer.h>

//DNSServer dnsServer;

//const byte DNS_PORT = 53;

// AP mode password
const char WiFiAPPSK[] = "";

// Wi-Fi network to connect to (leave blank to connect to saved network, or to start in AP mode)
const char* ssid = "";
const char* password = "";

#define HOSTNAME "ESP8266-" ///< Hostname. The initializeWiFi function adds the Chip ID at the end.

#define DEBUG_WIFI 1

WiFiMode mode = WIFI_STA; // connect to existing Wi-Fi network
//WiFiMode mode = WIFI_AP; // act as an Access Point, creating a new Wi-Fi network
//WiFiMode mode = WIFI_AP_STA; // act as both a client and Access Point (mesh mode)

template <typename Generic>
void debugPrint(Generic text) {
  if (DEBUG_WIFI) {
    Serial.print(text);
  }
}

template <typename Generic>
void debugPrintln(Generic text) {
  if (DEBUG_WIFI) {
    Serial.println(text);
  }
}

String getWiFiJson() {
  String hostname = String(HOSTNAME);
  hostname += String(ESP.getChipId(), HEX);

  String json = "{";

  json += "\"status\":\"" + String(WiFi.status()) + "\"";
  json += ",\"localIP\":\"" + WiFi.localIP().toString() + "\"";
  json += ",\"softAPIP\":\"" + WiFi.softAPIP().toString() + "\"";
  json += ",\"hostname\":\"" + hostname + "\"";
  json += ",\"ssid\":\"" + WiFi.SSID() + "\"";
  json += ",\"rssi\":\"" + String(WiFi.RSSI()) + "\"";

  json += ",\"networks\":[";
  byte ssidCount = WiFi.scanNetworks();
  for (byte i = 0; i < ssidCount; i++) {
    if (i > 0)
      json += ",";

    json += "{\"name\":\"" + WiFi.SSID(i) + "\",\"rssi\":\"" + String(WiFi.RSSI(i)) + "\"}";
  }

  json += "]";

  json += "}";

  return json;
}

void initializeWiFi() {
  // Set Hostname.
  String hostname = String(HOSTNAME);
  hostname += String(ESP.getChipId(), HEX);
  WiFi.hostname(hostname);

  // Print hostname.
  Serial.println("Hostname: " + hostname);

  char hostnameChar[hostname.length() + 1];
  memset(hostnameChar, 0, hostname.length() + 1);

  for (uint8_t i = 0; i < hostname.length(); i++)
    hostnameChar[i] = hostname.charAt(i);

  //  MDNS.begin(hostnameChar);

  // Add service to MDNS-SD
  //  MDNS.addService("http", "tcp", 80);

  // attempt to connect; should it fail, fall back to AP mode
  //  WiFi.mode(WIFI_STA);

  String stored_ssid = WiFi.SSID();

  if (ssid != NULL && password != NULL &&
      ssid != "" && password != "") {
    debugPrint("WiFi mode: ");
    debugPrintln(WIFI_STA);
    WiFi.mode(WIFI_STA);

    debugPrint("Connecting to hard-coded SSID: ");
    debugPrintln(stored_ssid);
    WiFi.begin(ssid, password);
  }
  else if (stored_ssid != NULL && stored_ssid != "") {
    debugPrint("WiFi mode: ");
    debugPrintln(WIFI_STA);
    WiFi.mode(WIFI_STA);

    debugPrint("Connecting to stored SSID: ");
    debugPrintln(stored_ssid);
    WiFi.begin();
  }
  else {
    debugPrintln("No stored SSID");
    debugPrint("Starting soft AP: ");
    debugPrintln(hostnameChar);

    WiFi.mode(WIFI_AP);

    if (WiFiAPPSK != NULL) {
      debugPrint(WiFi.softAP(hostnameChar, WiFiAPPSK) ? "ready" : "failed");
    } else {
      debugPrint(WiFi.softAP(hostnameChar) ? "ready" : "failed");
    }

    debugPrint("Connect to Wi-Fi access point: ");
    debugPrintln(hostnameChar);

    delay(500); // Without delay I've seen the IP address blank
    debugPrint("AP IP address: ");
    debugPrintln(WiFi.softAPIP());

    //  dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
    //  dnsServer.start(DNS_PORT, "*", WiFi.softAPIP());
  }

  webServer.on("/wifi", HTTP_POST, []() {
    String ssid = webServer.arg("ssid");
    String password = webServer.arg("password");

    char ssidChars[50];
    ssid.toCharArray(ssidChars, 50);

    char passwordChars[50];
    password.toCharArray(passwordChars, 50);

    debugPrint("Connecting to new SSID: ");
    debugPrintln(ssid);

    WiFi.begin(ssidChars, passwordChars);

    webServer.sendHeader("Location", "/wifi.htm");
    webServer.send(303);
  });

  webServer.on("/wifi", HTTP_GET, []() {
    String json = getWiFiJson();
    webServer.send(200, "application/json", json);
  });
}

