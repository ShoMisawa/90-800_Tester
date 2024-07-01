#ifndef GLOBAL_FUNCTIONS_H
#define GLOBAL_FUNCTIONS_H

#include <Adafruit_SleepyDog.h>
#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <SPI.h>
#include "graphics.h"
//#include "global_variables.h"

/* Function Declarations */
void resetParameters();                                      // Function to reset used parameters for each cycle
void updateDisplay();                                        // Update the display to show the voltage measurements on OLED screen
void GPIO_setup();                                           // GPIO Initialization
void OLED_init();                                            // OLED Initialization
void WATCHDOG_init();                                        // Watchdog Initialization
void OLED_FL_OK_Screen();                                    // OLED FL Screen Update
void OLED_Relay_Animation();                                 // OLED Relay Screen Update
void OLED_waiting_for_power();                               // OLED Waiting for Power Screen Update
float voltMeasure(int channel);                              // Measuring/Reading the channel
void checkVoltage();                                         // Checking the voltage using voltMeasure function
void displayVoltageReading(float voltage, float voltage_2);  // OLED display the voltage when the toggle switch is ON
void reset_voltage_validation();                             // Resetting the voltage validation flag for FL test

void LED_TEST_ALLON();  // Turn on all the test result LEDs to make sure that soldered correctly.

/*------------------------------------------------------------------------------------------------------------------------*/
/*U8G2 Initialization*/
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);  // initialization for the used OLED display
/*------------------------------------------------------------------------------------------------------------------------*/

void reset_voltage_validation() {
  voltageValidation_1 = 0;
  voltageValidation_2 = 0;
}

void checkVoltage() {
  /* Measuring the voltage */
  in_voltage = voltMeasure(0);
  in_voltage_2 = voltMeasure(1);
}

void OLED_Voltage_Reading_Display() {
  u8g2.setBitmapMode(1);
  u8g2.clearBuffer();
  u8g2.drawFrame(2, 2, 124, 62);
  u8g2.drawLine(3, 15, 125, 15);
  u8g2.setFont(u8g2_font_haxrcorp4089_tr);
  //u8g2.drawStr(27, 30, "J6:");
  u8g2.setFont(u8g2_font_haxrcorp4089_tr);
  sprintf(voltagebuffer, "J6: %.2f", in_voltage);
  u8g2.drawStr(27, 30, voltagebuffer);
  u8g2.setFont(u8g2_font_haxrcorp4089_tr);
  u8g2.drawStr(83, 30, "V");
  u8g2.setFont(u8g2_font_haxrcorp4089_tr);
  u8g2.drawStr(30, 13, "Voltage Reading");
  u8g2.setFont(u8g2_font_haxrcorp4089_tr);
  //u8g2.drawStr(27, 45, "J7:");
  u8g2.setFont(u8g2_font_haxrcorp4089_tr);
  sprintf(voltagebuffer, "J7: %.2f", in_voltage_2);
  u8g2.drawStr(27, 45, voltagebuffer);
  u8g2.setFont(u8g2_font_haxrcorp4089_tr);
  u8g2.drawStr(83, 45, "V");

  if (in_voltage < upperLimit && in_voltage > lowerLimit)
    u8g2.drawXBMP(99, 38, 24, 24, image_icons8_outline_effect_tickmark_under_a_square_box_24_bits);
  else {
    u8g2.setDrawColor(0);
    u8g2.drawBox(97, 36, 27, 26);
    u8g2.setDrawColor(1);
    voltageCheckVisible = false;
  }

  u8g2.sendBuffer();
}

void OLED_Voltage_Test_Failed_Screen() {
  u8g2.clearBuffer();
  u8g2.setBitmapMode(1);
  u8g2.drawFrame(2, 2, 124, 62);
  u8g2.setFont(u8g2_font_haxrcorp4089_tr);
  u8g2.drawStr(33, 13, "Voltage Test");
  u8g2.drawLine(2, 14, 126, 14);
  u8g2.drawXBMP(37, 15, 48, 48, image_icons8_cross_48_bits);
  u8g2.sendBuffer();
}

void OLED_All_Failed_Screen() {
  u8g2.clearBuffer();
  u8g2.setBitmapMode(1);
  u8g2.drawFrame(2, 2, 125, 61);
  u8g2.setFont(u8g2_font_haxrcorp4089_tr);
  u8g2.drawStr(38, 49, "ALL FAILED");
  u8g2.drawXBMP(50, 13, 24, 24, image_icons8_sad_24_bits);
  u8g2.sendBuffer();
}

void OLED_FL_VT_Failed_Screen() {
  u8g2.clearBuffer();
  u8g2.setBitmapMode(1);
  u8g2.drawFrame(2, 2, 124, 62);
  u8g2.setFont(u8g2_font_haxrcorp4089_tr);
  u8g2.drawStr(27, 13, "FL and VT Test");
  u8g2.drawLine(2, 14, 126, 14);
  u8g2.drawXBMP(37, 15, 48, 48, image_icons8_cross_48_bits);
  u8g2.sendBuffer();
}

void OLED_Power_Detection_Failed_Screen() {
  u8g2.clearBuffer();
  u8g2.setBitmapMode(1);
  u8g2.drawFrame(2, 2, 124, 62);
  u8g2.setFont(u8g2_font_haxrcorp4089_tr);
  u8g2.drawStr(20, 13, "Power Detection Test");
  u8g2.drawLine(2, 14, 126, 14);
  u8g2.drawXBMP(37, 15, 48, 48, image_icons8_cross_48_bits);
  u8g2.sendBuffer();
}

void OLED_FL_Test_Failed_Screen() {
  u8g2.clearBuffer();
  u8g2.setBitmapMode(1);
  u8g2.drawFrame(2, 2, 124, 62);
  u8g2.setFont(u8g2_font_haxrcorp4089_tr);
  u8g2.drawStr(33, 13, "Fire Loop Test");
  u8g2.drawLine(2, 14, 126, 14);
  u8g2.drawXBMP(37, 15, 48, 48, image_icons8_cross_48_bits);
  u8g2.sendBuffer();
}

void OLED_RESET_Screen() {
  u8g2.clearBuffer();
  u8g2.setBitmapMode(1);
  u8g2.drawFrame(2, 2, 125, 61);
  u8g2.setFont(u8g2_font_haxrcorp4089_tr);
  u8g2.drawStr(40, 49, "RESETTING...");
  u8g2.drawXBMP(51, 11, 24, 24, reset_bitmap_allArray[counterGraphics2]);
  u8g2.sendBuffer();
  counterGraphics2 = (counterGraphics2 + 1) % 28;
}

void OLED_Test_OK_Screen() {
  u8g2.setBitmapMode(1);
  u8g2.clearBuffer();
  u8g2.drawFrame(2, 3, 125, 61);
  u8g2.setFont(u8g2_font_haxrcorp4089_tr);
  u8g2.drawStr(40, 12, "All Test OK");
  u8g2.drawLine(2, 14, 126, 14);
  u8g2.drawXBMP(51, 26, 30, 30, good_bitmap_allArray[counterGraphics]);
  u8g2.sendBuffer();
  counterGraphics = (counterGraphics + 1) % 28;
}

void OLED_FL_OK_Screen() {
  u8g2.setBitmapMode(1);
  u8g2.clearBuffer();
  u8g2.drawFrame(2, 3, 125, 61);
  u8g2.setFont(u8g2_font_haxrcorp4089_tr);
  u8g2.drawStr(33, 12, "Fire Loop Test");
  u8g2.drawLine(2, 14, 126, 14);
  u8g2.drawXBMP(51, 26, 24, 24, image_icons8_outline_effect_tickmark_under_a_square_box_24_bits);
  u8g2.sendBuffer();
}

void OLED_Relay_Animation() {
  u8g2.setBitmapMode(1);
  u8g2.clearBuffer();
  u8g2.drawFrame(2, 2, 125, 61);
  u8g2.drawLine(2, 14, 126, 14);
  u8g2.setFont(u8g2_font_haxrcorp4089_tr);
  u8g2.drawStr(51, 30, "Relay");
  u8g2.setFont(u8g2_font_haxrcorp4089_tr);
  u8g2.drawStr(33, 12, "Fire Loop Test");
  u8g2.drawXBMP(50, 34, 30, 30, aepd_bitmap_allArray[counterGraphics]);
  u8g2.sendBuffer();
  counterGraphics = (counterGraphics + 1) % 11;
}

void OLED_waiting_for_power() {
  u8g2.clearBuffer();
  u8g2.setBitmapMode(1);
  u8g2.drawFrame(2, 2, 123, 61);
  u8g2.setFont(u8g2_font_helvB08_tr);
  u8g2.drawStr(17, 29, "Waiting for Power");
  u8g2.drawXBMP(45, 35, 30, 30, epd_bitmap_allArray[counterGraphics]);
  u8g2.sendBuffer();  // transfer internal memory to the display
  counterGraphics = (counterGraphics + 1) % 29;
}

void WATCHDOG_init() {
  int wdtTimeout = Watchdog.enable(8000);  // Enable WDT with 8 seconds timeout
  Serial.print("WDT set to ");
  Serial.print(wdtTimeout, DEC);
  Serial.println(" milliseconds");
}

void OLED_init() {
  u8g2.begin();  // start the u8g2 library...
  u8g2.clearBuffer();
  u8g2.setBitmapMode(1);
  u8g2.drawXBMP(15, -1, 100, 70, image_detex_bits);
  u8g2.sendBuffer();
}

void GPIO_setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);                  // this line also has external pullup resistor
  pinMode(VOLTAGE_DISPLAY_TOGGLE_PIN, INPUT_PULLUP);  // this line also has external pullup resistor

  pinMode(LED_8_PIN, OUTPUT);
  pinMode(LED_9_PIN, OUTPUT);
  pinMode(LED_10_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);

  digitalWrite(LED_8_PIN, LOW);
  digitalWrite(LED_9_PIN, LOW);
  digitalWrite(LED_10_PIN, LOW);
  digitalWrite(RELAY_PIN, HIGH);

  analogReadResolution(12);
}

void resetParameters() {
  voltageValidation_1 = 0;
  voltageValidation_2 = 0;

  voltageDetected = 0;  // upon power connection to 24V, this flag is set to 0 when it is less than 15V.  Set to 1 when it is greater than 15V.  15V is random value.

  state = 0;

  //previousMillis;
  count = 1;  // for development purpose, it is set to the state

  relayActiveFlag = 0;
  powerDetectionOK = 0;
  VoltageTestOK = 0;
  FLTestOK = 0;

  digitalWrite(LED_8_PIN, LOW);
  digitalWrite(LED_9_PIN, LOW);
  digitalWrite(LED_10_PIN, LOW);
  digitalWrite(RELAY_PIN, HIGH);
}

float voltMeasure(int channel) {
  analogReadResolution(12);

  if (channel == 0) {

    adc_value = analogRead(channel);
    adc_voltage = (adc_value * ref_voltage) / 4095.0;
    in_voltage = (adc_voltage / resRatio) + Calibration;
    return in_voltage;
  }

  if (channel == 1) {

    adc_value_2 = analogRead(channel);
    adc_voltage_2 = (adc_value_2 * ref_voltage) / 4095.0;
    in_voltage_2 = (adc_voltage_2 / resRatio) + Calibration;
    return in_voltage_2;
  }

}  // end of voltMeter function

/* Function to update display */
void updateDisplay() {
  u8g2.setBitmapMode(1);
  u8g2.clearBuffer();
  u8g2.drawFrame(2, 2, 124, 62);
  u8g2.drawLine(3, 15, 125, 15);

  u8g2.setFont(u8g2_font_9x15B_mr);
  //u8g2.drawStr(27, 30, "J6:");

  u8g2.setFont(u8g2_font_9x15B_mr);
  sprintf(voltagebuffer, "J6: %.2f", in_voltage);

  u8g2.drawStr(10, 30, voltagebuffer);
  u8g2.setFont(u8g2_font_9x15B_mr);
  u8g2.drawStr(83, 30, "V");
  u8g2.setFont(u8g2_font_haxrcorp4089_tr);
  u8g2.drawStr(30, 13, "Voltage Reading");
  u8g2.setFont(u8g2_font_9x15B_mr);
  //u8g2.drawStr(27, 45, "J7:");
  u8g2.setFont(u8g2_font_9x15B_mr);
  sprintf(voltagebuffer, "J7: %.2f", in_voltage_2);
  u8g2.drawStr(10, 45, voltagebuffer);
  u8g2.setFont(u8g2_font_9x15B_mr);
  u8g2.drawStr(83, 45, "V");
  u8g2.sendBuffer();
}

/* Function to display voltage reading */
void displayVoltageReading(float voltage, float voltage_2) {
  u8g2.setBitmapMode(1);
  u8g2.clearBuffer();
  u8g2.drawFrame(2, 2, 124, 62);
  u8g2.drawLine(3, 15, 125, 15);

  u8g2.setFont(u8g2_font_9x15B_mr);
  //u8g2.drawStr(27, 30, "J6:");

  u8g2.setFont(u8g2_font_9x15B_mr);
  sprintf(voltagebuffer, "J6: %.2f", in_voltage);

  u8g2.drawStr(10, 30, voltagebuffer);
  u8g2.setFont(u8g2_font_9x15B_mr);
  u8g2.drawStr(83, 30, "V");
  u8g2.setFont(u8g2_font_haxrcorp4089_tr);
  u8g2.drawStr(30, 13, "Voltage Reading");
  u8g2.setFont(u8g2_font_9x15B_mr);
  //u8g2.drawStr(27, 45, "J7:");
  u8g2.setFont(u8g2_font_9x15B_mr);
  sprintf(voltagebuffer, "J7: %.2f", in_voltage_2);
  u8g2.drawStr(10, 45, voltagebuffer);
  u8g2.setFont(u8g2_font_9x15B_mr);
  u8g2.drawStr(83, 45, "V");
  u8g2.sendBuffer();

  if (voltage < upperLimit && voltage > lowerLimit) {
    u8g2.drawXBMP(99, 38, 24, 24, image_icons8_outline_effect_tickmark_under_a_square_box_24_bits);
  } else {
    u8g2.setDrawColor(0);
    u8g2.drawBox(97, 36, 27, 26);
    u8g2.setDrawColor(1);
  }
  u8g2.sendBuffer();
}

void LED_TEST_ALLON() {
  digitalWrite(LED_8_PIN, HIGH);
  digitalWrite(LED_9_PIN, HIGH);
  digitalWrite(LED_10_PIN, HIGH);
}

#endif