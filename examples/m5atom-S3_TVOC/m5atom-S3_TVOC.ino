//SGP30 needs 15 seconds to initialize calibration after power on.
//The screen will display TVOC and CO2

#include <M5Unified.h>

#include "Adafruit_SGP30.h"

// #define Wire1_SDA (2)
// #define Wire1_SCL (1)

Adafruit_SGP30 sgp;
int i = 15;
long last_millis = 0;

void header(const char *string, uint16_t color)
{
    M5.Lcd.setTextColor(color, TFT_BLUE);
    M5.Lcd.fillRect(0, 0, 128, 15, TFT_BLUE);
    M5.Lcd.setTextDatum(TC_DATUM);  // align top-center
    M5.Lcd.drawString(string, 64, 1, 2); 
}

void setup() {
  auto cfg = M5.config();
  cfg.internal_mic = false;
  M5.begin(cfg);

//  Wire1.begin(Wire1_SDA, Wire1_SCL);

  header("SGP30 TEST",TFT_YELLOW);
  Serial.println("SGP30 test");
  if (! sgp.begin()){
    Serial.println("Sensor not found :(");
    while (1);
  }

  M5.Lcd.setBrightness(64);
  M5.Lcd.setTextDatum(TL_DATUM);  // align top-left
  M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
  M5.Lcd.drawString("TVOC :", 10, 30, 2);
  M5.Lcd.drawString("eCO2 :", 10, 50, 2);
  M5.Lcd.setTextDatum(TC_DATUM);  // align top-center
  M5.Lcd.drawString("Initialization...", 64, 80, 2);

  Serial.print("Found SGP30 serial #");
  Serial.print(sgp.serialnumber[0], HEX);
  Serial.print(sgp.serialnumber[1], HEX);
  Serial.println(sgp.serialnumber[2], HEX);

  M5.Lcd.setTextDatum(TL_DATUM);  // align top-left
}

void loop() {
  while(i > 0) {    
    if(millis()- last_millis > 1000) {
      last_millis = millis();
      i--;
      M5.Lcd.fillRect(0, 100, 128, 28, TFT_BLACK);
      M5.Lcd.drawNumber(i, 20, 100, 2);
    }
  }
  M5.Lcd.fillRect(0, 80, 128, 48, TFT_BLACK);

  if (! sgp.IAQmeasure()) {
    Serial.println("Measurement failed");
    return;
  }
  M5.Lcd.fillRect(60, 30, 68, 40, TFT_BLACK);
  M5.Lcd.setTextDatum(TR_DATUM);  // align top-right
  M5.Lcd.drawNumber(sgp.TVOC, 90, 30 , 2);
  M5.Lcd.setTextDatum(TL_DATUM);  // align top-left
  M5.Lcd.drawString("ppb", 95, 30, 2);
  M5.Lcd.setTextDatum(TR_DATUM);  // align top-right
  M5.Lcd.drawNumber(sgp.eCO2, 90, 50, 2);
  M5.Lcd.setTextDatum(TL_DATUM);  // align top-left
  M5.Lcd.drawString("ppm", 95, 50, 2);
  Serial.print("TVOC "); Serial.print(sgp.TVOC); Serial.print(" ppb\t");
  Serial.print("eCO2 "); Serial.print(sgp.eCO2); Serial.println(" ppm");
 
  delay(1000);
}
