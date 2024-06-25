/*

Program Written for Seeeduino-XIAO
Microcontroller: ATSAMD21G18A
Datasheet: https://files.seeedstudio.com/wiki/Seeeduino-XIAO/res/ATSAMD21G18A-MU-Datasheet.pdf

Revision: V4.2 : Added watchdog timer to each state and while loop.  Also in the beginning of the main loop

*/

#include "global_variables.h"
#include "global_functions.h"

/* Setting Up */
void setup() {

#if LED_TEST_MODE == 1
  GPIO_setup();  // Only initialize the GPIO
#else
  GPIO_setup();
  OLED_init();

  // SSD1306 Initialization...
  Serial.begin(9600);
  Serial.println("Starting up ...");

  delay(1000);  // One second splash screen

  // Setup the watchdog timer
  WATCHDOG_init();
#endif
}

void loop() {
  Watchdog.reset();
#if LED_TEST_MODE == 1
  LED_TEST_ALLON();
#else
  /* Measuring the voltage */
  checkVoltage();

  switch (state) {
    case 0:  // Waiting for 24V to come in... Upon detection move to the next case

      // Waiting until voltage readings become higher than 15VDC (powerLevel, defined in global_variable.h)
      while ((in_voltage < powerLevel || in_voltage_2 < powerLevel)) {
        currentMillis = millis();

        if (currentMillis - previousMillis >= interval) {
          previousMillis = currentMillis;
          iconVisible = !iconVisible;
        }

        /* Measuring the voltage */
        checkVoltage();

        // Debug purposes
        Serial.println("Waiting for power...");
        Serial.print("Voltage Reading: ");
        Serial.print(in_voltage);
        Serial.print(" , ");
        Serial.println(in_voltage_2);

        OLED_waiting_for_power();
        Watchdog.reset();  // Reset the watchdog timer within the while loop
      }

      delay(500);

      voltageDetected = 1;  // after coming out from the while loop, the voltage should be greater than 15VDC
      state = 1;
      counterGraphics = 0;

      break;

    case 1:  // Power detected... Transition into voltage confirmation

      powerDetectionOK = 1;
      state = 2;
      digitalWrite(LED_8_PIN, HIGH);

      // After voltage detected and voltage drops below 15V, it will go back to state 0
      if (in_voltage < powerLevel || in_voltage_2 < powerLevel) {
        state = 0;
        digitalWrite(LED_8_PIN, LOW);
      }
      Watchdog.reset();

      break;

    case 2:  // Showing voltage reading on OLED and waiting for confirmation button to be pressed
      // Waiting for the confirmation by pressing the button located on the right hand bottom side
      while (!digitalRead(BUTTON_PIN) == LOW) {
        /* Measure Voltage */
        checkVoltage();

        // Debug purposes
        Serial.println("Power Detected!");
        Serial.print("Voltage Reading: ");
        Serial.print(in_voltage);
        Serial.print(" , ");
        Serial.println(in_voltage_2);

        updateDisplay();

        if (in_voltage < upperLimit && in_voltage > lowerLimit) {
          voltageValidation_1 = 1;
          voltageValidation_2 = 1;
          digitalWrite(LED_9_PIN, HIGH);
        } else {
          voltageValidation_1 = 0;
          voltageValidation_2 = 0;
          digitalWrite(LED_9_PIN, LOW);
        }

        if (voltageValidation_1 == 1 && voltageValidation_2 == 1) {
          VoltageTestOK = 1;
          digitalWrite(LED_9_PIN, HIGH);
          state = 3;
        } else {
          digitalWrite(LED_9_PIN, LOW);
        }

        Watchdog.reset();
      }
      break;

    case 3:  // Turning off relay for FL test

      OLED_Relay_Animation();

      if (counterGraphics == 0) {
        state = 4;
        counterGraphics = 0;
        relayActiveFlag = 1;
        digitalWrite(RELAY_PIN, LOW);
        delay(1000);
        //break;
      }
      Watchdog.reset();

      break;

    case 4:  // Fire loop test - when the fireloop connection is open, the 24VDC output should be OFF.
      if (relayActiveFlag == 1) {
        // Resetting the voltageValidation for fire loop detection
        reset_voltage_validation();

        /* Measuring the voltage */
        checkVoltage();

        /*.Checking voltage and setting the flags*/
        if (in_voltage < 10 || in_voltage_2 < 10) {
          voltageValidation_1 = 1;
          voltageValidation_2 = 1;
        } else {
          voltageValidation_1 = 0;
          voltageValidation_2 = 0;
        }

        if (voltageValidation_1 == 1 && voltageValidation_2 == 1) {
          OLED_FL_OK_Screen();
          delay(1000);
          FLTestOK = 1;
          digitalWrite(LED_10_PIN, HIGH);
          digitalWrite(RELAY_PIN, HIGH);
          relayActiveFlag = 0;
          state = 5;
        } else {
          delay(1000);
          digitalWrite(LED_10_PIN, LOW);
          state = 5;
        }
      }
      Watchdog.reset();
      break;

    case 5:  // Test Result
      // while toggle switch is in the LOW state, display the output voltage reading.
      while (!digitalRead(VOLTAGE_DISPLAY_TOGGLE_PIN) == LOW) {
        /* Measure Voltage */
        checkVoltage();

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
        Watchdog.reset();
      }

      if (VoltageTestOK == 1 && FLTestOK == 1 && powerDetectionOK == 1) {

        u8g2.setBitmapMode(1);
        u8g2.clearBuffer();
        u8g2.drawFrame(2, 3, 125, 61);
        u8g2.setFont(u8g2_font_haxrcorp4089_tr);
        u8g2.drawStr(40, 12, "All Test OK");
        u8g2.drawLine(2, 14, 126, 14);
        u8g2.drawXBMP(51, 26, 30, 30, good_bitmap_allArray[counterGraphics]);
        u8g2.sendBuffer();
        counterGraphics = (counterGraphics + 1) % 28;
        ////delay(5000);

        /*.Measure Voltage */
        checkVoltage();

        if (in_voltage < 20 || in_voltage_2 < 20) {
          int resetGraphicEnable = 1;
          while (resetGraphicEnable == 1) {
            u8g2.clearBuffer();
            u8g2.setBitmapMode(1);
            u8g2.drawFrame(2, 2, 125, 61);
            u8g2.setFont(u8g2_font_haxrcorp4089_tr);
            u8g2.drawStr(40, 49, "RESETTING...");
            u8g2.drawXBMP(51, 11, 24, 24, reset_bitmap_allArray[counterGraphics2]);
            u8g2.sendBuffer();
            counterGraphics2 = (counterGraphics2 + 1) % 28;

            if (counterGraphics2 == 0) {
              resetGraphicEnable = 0;
            }

            Watchdog.reset();
          }

          delay(2000);
          resetParameters();
        }
      } else if (VoltageTestOK == 0 && FLTestOK == 1 && powerDetectionOK == 1) {
        // Test Failed
        u8g2.clearBuffer();
        u8g2.setBitmapMode(1);
        u8g2.drawFrame(2, 2, 124, 62);
        u8g2.setFont(u8g2_font_haxrcorp4089_tr);
        u8g2.drawStr(33, 13, "Voltage Test");
        u8g2.drawLine(2, 14, 126, 14);
        u8g2.drawXBMP(37, 15, 48, 48, image_icons8_cross_48_bits);
        u8g2.sendBuffer();
        delay(5000);
      } else if (VoltageTestOK == 1 && FLTestOK == 0 && powerDetectionOK == 1) {
        // Test Failed
        u8g2.clearBuffer();
        u8g2.setBitmapMode(1);
        u8g2.drawFrame(2, 2, 124, 62);
        u8g2.setFont(u8g2_font_haxrcorp4089_tr);
        u8g2.drawStr(33, 13, "Fire Loop Test");
        u8g2.drawLine(2, 14, 126, 14);
        u8g2.drawXBMP(37, 15, 48, 48, image_icons8_cross_48_bits);
        u8g2.sendBuffer();
        //            delay(5000);
      } else if (VoltageTestOK == 1 && FLTestOK == 1 && powerDetectionOK == 0) {
        u8g2.clearBuffer();
        u8g2.setBitmapMode(1);
        u8g2.drawFrame(2, 2, 124, 62);
        u8g2.setFont(u8g2_font_haxrcorp4089_tr);
        u8g2.drawStr(20, 13, "Power Detection Test");
        u8g2.drawLine(2, 14, 126, 14);
        u8g2.drawXBMP(37, 15, 48, 48, image_icons8_cross_48_bits);
        u8g2.sendBuffer();
        //            delay(5000);
      } else if (VoltageTestOK == 0 && FLTestOK == 0 && powerDetectionOK == 1) {
        u8g2.clearBuffer();
        u8g2.setBitmapMode(1);
        u8g2.drawFrame(2, 2, 124, 62);
        u8g2.setFont(u8g2_font_haxrcorp4089_tr);
        u8g2.drawStr(27, 13, "FL and VT Test");
        u8g2.drawLine(2, 14, 126, 14);
        u8g2.drawXBMP(37, 15, 48, 48, image_icons8_cross_48_bits);
        u8g2.sendBuffer();
        //delay(5000);
      } else {
        u8g2.clearBuffer();
        u8g2.setBitmapMode(1);
        u8g2.drawFrame(2, 2, 125, 61);
        u8g2.setFont(u8g2_font_haxrcorp4089_tr);
        u8g2.drawStr(38, 49, "ALL FAILED");
        u8g2.drawXBMP(50, 13, 24, 24, image_icons8_sad_24_bits);
        u8g2.sendBuffer();
      }
      Watchdog.reset();
      break;
  }
#endif
  // }


}  // End of main loop
