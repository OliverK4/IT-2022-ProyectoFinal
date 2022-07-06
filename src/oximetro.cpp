#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "MAX30100_PulseOximeter.h"
#define REPORTING_PERIOD_MS    100
PulseOximeter max_sensor;
uint32_t lastReportTime = 0;
Adafruit_SSD1306 OLED = Adafruit_SSD1306(128, 32, &Wire);

void onBeatDetected()
{
   Serial.println("Beat!");
}

void setup() {
 // put your setup code here, to run once:
 OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C);
 Serial.begin(115200);
 OLED.display();
 OLED.clearDisplay();
 OLED.setTextSize(2);
 OLED.setTextColor(SSD1306_WHITE);
 OLED.setCursor(0,0);
 OLED.display();
 delay(1000);

   Serial.print("Initializing pulse oximeter..");

   // Initialize the PulseOximeter instance
   // Failures are generally due to an improper I2C wiring, missing power supply
   // or wrong target chip
   if (!max_sensor.begin()) {
       Serial.println("FAILED");
       for(;;);
   } else {
       Serial.println("SUCCESS");
   }
       max_sensor.setOnBeatDetectedCallback(onBeatDetected);
}

void loop() {
 // put your main code here, to run repeatedly:

max_sensor.update();


   if (millis() - lastReportTime > REPORTING_PERIOD_MS) {

       OLED.clearDisplay();
       OLED.setCursor(0,0);
       OLED.print("H:");
       OLED.print(max_sensor.getHeartRate());
       OLED.println("bpm");
       OLED.print("SpO2:");
       OLED.print(max_sensor.getSpO2());
       OLED.println("%");
       lastReportTime = millis();
   }
   OLED.display();
}