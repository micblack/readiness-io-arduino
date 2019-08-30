const String    CHANNEL_ID    = "test"; // The Readiness.io channel ID
const String    SENSOR_ID     = "ardunodev"; // Your AgriWebb or made up sensor ID
const String    TOPIC         = "library3"; // The type of sensor or name of the data your sending
const String    VERSION       = "1";
const String    FORMAT        = "";

char*     WIFI_SSID     = "BAAJA 2.4G"; // Your WiFi SSID / name
char*     WIFI_PASS     = "connect@adams"; // Your WiFi password

const uint8_t   TIMEZONE_OFFSET = 10; // The timezone the sensor is located in (eg. 10 for GMT)
const uint16_t  DEBOUNCE_TIME   = 200; // How long before the next gate reading can take place (ms)
