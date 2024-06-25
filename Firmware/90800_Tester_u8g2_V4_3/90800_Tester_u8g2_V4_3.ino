/*

Program Written for Seeeduino-XIAO
Microcontroller: ATSAMD21G18A
Datasheet: https://files.seeedstudio.com/wiki/Seeeduino-XIAO/res/ATSAMD21G18A-MU-Datasheet.pdf

Revision: V4.2 : Added watchdog timer to each state and while loop.  Also in the beginning of the main loop
Revision V4.3 : Organized code.  Put stuff into function and made it easier to read

*/

#include "global_variables.h"
#include "global_functions.h"

/* Setting Up */
void setup() {

#if LED_TEST_MODE
  GPIO_setup();  // Only initialize the GPIO
#else
  GPIO_setup();
  OLED_init();

#if DEBUG
  Serial.begin(9600);
  Serial.println("Starting up ...");
#endif

  delay(1000);  // One second splash screen

  // Setup the watchdog timer
  WATCHDOG_init();
#endif
}

void loop() {
  Watchdog.reset();
#if LED_TEST_MODE
  LED_TEST_ALLON();
#else
  /* Measuring the voltage */
  checkVoltage();

  unsigned long currentMillis = millis();

#if DEMO
  if (currentMillis - lastStateChangeTime >= stateChangeInterval) {
    lastStateChangeTime = currentMillis;
    state = (state + 1) % 6;  // Cycle through states 0 to 5
  }
#endif
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


#if DEBUG
        Serial.println("Power Detected!");
        Serial.print("Voltage Reading: ");
        Serial.print(in_voltage);
        Serial.print(" , ");
        Serial.println(in_voltage_2);
#endif

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

    case 5:  // Showing Test Result
      // while toggle switch is in the LOW state, display the output voltage reading.
      while (!digitalRead(VOLTAGE_DISPLAY_TOGGLE_PIN) == LOW) {
        /* Measure Voltage */
        checkVoltage();
        OLED_Voltage_Reading_Display();
        Watchdog.reset();
      }

      if (VoltageTestOK == 1 && FLTestOK == 1 && powerDetectionOK == 1) {

        OLED_Test_OK_Screen();
        ////delay(5000);

        /*.Measure Voltage */
        checkVoltage();

        if (in_voltage < 20 || in_voltage_2 < 20) {
          int resetGraphicEnable = 1;
          while (resetGraphicEnable == 1) {
            OLED_RESET_Screen();

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
        OLED_Voltage_Test_Failed_Screen();
        delay(5000);
      } else if (VoltageTestOK == 1 && FLTestOK == 0 && powerDetectionOK == 1) {
        // Fire Loop Test Failed
        OLED_FL_Test_Failed_Screen();
      } else if (VoltageTestOK == 1 && FLTestOK == 1 && powerDetectionOK == 0) {
        // Power Detection Test Failed
        OLED_Power_Detection_Failed_Screen();
      } else if (VoltageTestOK == 0 && FLTestOK == 0 && powerDetectionOK == 1) {
        // Voltage and Fire loop test failed
        OLED_FL_VT_Failed_Screen();
      } else {
        // All test failed
        OLED_All_Failed_Screen();
      }
      Watchdog.reset();
      break;
  }
#endif
  // }


}  // End of main loop
