#ifndef _GLOBAL_VARIABLES_H
#define _GLOBAL_VARIABLE_H

/*------------------------------------------------------------------------------------------------------------------------*/
/* Definitions*/
// OLED Screen Pixel Size
#define SCREEN_WIDTH                128           // OLED display width, in pixels
#define SCREEN_HEIGHT               64            // OLED display height, in pixels

// Voltage Upper and Lower Limit
#define upperLimit                  24*(1+0.1)    // 10% upper limit
#define lowerLimit                  24*(1-0.1)    // 10% lower limit

// Acceptable Power detection
#define powerLevel                  15

/*Pin Definitions*/
#define LED_8_PIN                   8             // Pin 8 (Port A): LED for Power Ditection
#define LED_9_PIN                   9             // Pin 9 (Port A): LED for Voltage Level
#define LED_10_PIN                  10            // Pin 10 (Port A): LED for Fire Loop test
#define RELAY_PIN                   7             // Pin 7 (Port A): Relay Control
#define BUTTON_PIN                  2             // Pin 2 (Port A): Button Read
#define VOLTAGE_DISPLAY_TOGGLE_PIN  3             // Pin 3 (Port A): Option to view the voltage level at the end of the test

// Debug Mode
#define LED_TEST_MODE                0             // This mode can be used to check the LED brightness for LED8, 9, and 10

/*------------------------------------------------------------------------------------------------------------------------*/

const float SCHOTTKY_VOLTAGE_DROP = 0.3;

/*------------------------------------------------------------------------------------------------------------------------*/
float R1 = 100000;                          // 100K Ohm
float R2 = 10000;                           // 10K Ohm
float resRatio = R2 / (R1 + R2);            // Calculating the ratio

/*Voltage Reading Parameters*/
float ref_voltage = 3.3;                    // Reference voltage of 3V3

// Bot J6
float adc_voltage = 0.0;                    // ADC reading for J6
float in_voltage = 0.0;                     // Converted voltage level
int adc_value = 0;                          // Converted value

// Top J9
float adc_voltage_2 = 0.0;                  // ADC reading for J9
float in_voltage_2 = 0.0;                   // Converted Voltage Level
int adc_value_2 = 0;                        // Converted Value

/*Test Confirmation Flags*/
int voltageValidation_1 = 0;                // Flag if J9 reads proper voltage level
int voltageValidation_2 = 0;                // Flag if J6 reads proper voltage level
int voltageDetected = 0;                    // upon power connection to 24V, this flag is set to 0 when it is less than 15V.  Set to 1 when it is greater than 15V.  15V is random value.

// Toggle Display
volatile bool showVoltage = false;

// State Switch Parameter
int state = 0;

//unsigned long previousMillis;
int count = 1;                              // for development purpose, it is set to the state

int relayActiveFlag = 0;
int powerDetectionOK = 0;
int VoltageTestOK = 0;
int FLTestOK = 0;

// Buffer for conversion to string
char buffer[32];

// Visibility Flags for Graphics
bool iconVisible = true; // default should be true
bool voltageCheckVisible = false; // default should be false
bool relaySwitchVisible = true; // default should be true

// Flashing graphics parameters
const long interval = 1000; // Flash interval for the icon in millisecond
unsigned long previousMillis = 0;
unsigned long currentMillis = 0;
char voltagebuffer[32]; // helper buffer to construct a string to be displayed

int counterGraphics = 0;
char graphicsBuffer[32];
int counterGraphics2 = 0;
/*------------------------------------------------------------------------------------------------------------------------*/


#endif
