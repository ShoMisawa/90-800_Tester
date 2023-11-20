#include <U8g2lib.h>
#include <Wire.h>
#include <SPI.h>
#include "graphics.h"

/* Definitions*/
// OLED Screen Pixel Size
#define SCREEN_WIDTH          128           // OLED display width, in pixels
#define SCREEN_HEIGHT         64            // OLED display height, in pixels

// Voltage Upper and Lower Limit
#define upperLimit            24*(1+0.1)    // 10% upper limit
#define lowerLimit            24*(1-0.1)    // 10% lower limit

/*Pin Definitions*/
#define LED_8                 8             // Pin 8 : LED for Power Ditection
#define LED_9                 9             // Pin 9 : LED for Voltage Level
#define LED_10                10            // Pin 10 : LED for Fire Loop test
#define Relay                 7             // Pin 7 : Relay Control
#define Button                2             // Pin 2 : Button Read
#define voltageDisplayToggle  3             // Pin 3 : Option to view the voltage level at the end of the test

// Debug Mode
#define LED_TEST_MODE         0             // This mode can be used to check the LED brightness for LED8, 9, and 10

/*U8G2 Initialization*/
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE); // initialization for the used OLED display

float R1 = 100000;                  // 100K Ohm
float R2 = 10000;                   // 10K Ohm
float resRatio = R2 / (R1 + R2);    // Calculating the ratio

/*Voltage Reading Parameters*/
float ref_voltage = 3.3;            // Reference voltage of 3V3

// Bot J6
float adc_voltage = 0.0;            // ADC reading for J6
float in_voltage = 0.0;             // Converted voltage level
int adc_value = 0;                  // Converted value

// Top J9
float adc_voltage_2 = 0.0;          // ADC reading for J9
float in_voltage_2 = 0.0;           // Converted Voltage Level
int adc_value_2 = 0;                // Converted Value

/*Test Confirmation Flags*/
int voltageValidation_1 = 0;        // Flag if J9 reads proper voltage level
int voltageValidation_2 = 0;        // Flag if J6 reads proper voltage level

int voltageDetected = 0;            // upon power connection to 24V, this flag is set to 0 when it is less than 15V.  Set to 1 when it is greater than 15V.  15V is random value.

// State Switch Parameter
int state = 0;

//unsigned long previousMillis;
int count = 1; // for development purpose, it is set to the state

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


void setup() {

  pinMode(Button, INPUT_PULLUP); // this line also has external pullup resistor
  pinMode(voltageDisplayToggle, INPUT_PULLUP); // this line also has external pullup resistor
  pinMode(LED_8, OUTPUT);
  pinMode(LED_9, OUTPUT);
  pinMode(LED_10, OUTPUT);
  pinMode(Relay, OUTPUT);
  // pinMode(A0, INPUT);
  // pinMode(A1, INPUT);
  
  digitalWrite(LED_8, LOW);
  digitalWrite(LED_9, LOW);
  digitalWrite(LED_10, LOW);
  digitalWrite(Relay, HIGH);

  // SSD1306 Initialization...
  Serial.begin(9600);
  Serial.println("Starting up ...");

  u8g2.begin(); // start the u8g2 library...
  u8g2.clearBuffer();
  u8g2.setBitmapMode(1);
  u8g2.drawXBMP( 15, -1, 100, 70, image_detex_bits);
  u8g2.sendBuffer();
  delay(1000); // One second splash screen

  analogReadResolution(12);

}

void loop() {

  if(LED_TEST_MODE == 1){
    digitalWrite(LED_8, HIGH);
    digitalWrite(LED_9, HIGH);
    digitalWrite(LED_10, HIGH);
  }else{

  // J2 on the tester PWA
  adc_value = analogRead(0);
  adc_voltage = (adc_value * ref_voltage) / 4095.0;
  in_voltage = (adc_voltage / resRatio) + 0.3; // 0.3 is for schottky diode voltage adjustment

  // J4 on the tester PWA
  adc_value_2 = analogRead(1);
  adc_voltage_2 = (adc_value_2 * ref_voltage) / 4095.0;
  in_voltage_2 = (adc_voltage_2 / resRatio) + 0.3; // 0.3 is for schottky diode voltage adjustment

  switch(state){
    case 0: // Waiting for 24V to come in... Upon detection move to the next case

      // Waiting until voltage readings become higher than 15VDC
      while ((in_voltage < 15 || in_voltage_2 < 15)){
        currentMillis = millis();

        if (currentMillis - previousMillis >= interval){
          previousMillis = currentMillis;
          iconVisible = !iconVisible;
        }
        
        
        // J2 on the tester PWA
        adc_value = analogRead(0);
        adc_voltage = (adc_value * ref_voltage) / 4095.0;
        in_voltage = (adc_voltage / resRatio) + 0.3; // 0.3 is for schottky diode voltage adjustment

        // J4 on the tester PWA
        adc_value_2 = analogRead(1);
        adc_voltage_2 = (adc_value_2 * ref_voltage) / 4095.0;
        in_voltage_2 = (adc_voltage_2 / resRatio) + 0.3; // 0.3 is for schottky diode voltage adjustment
        
        u8g2.clearBuffer();
        u8g2.setBitmapMode(1);
        u8g2.drawFrame(2, 2, 123, 61);
        u8g2.setFont(u8g2_font_helvB08_tr);
        u8g2.drawStr(17, 29, "Waiting for Power");
        //u8g2.drawBox(56, 35, 13, 15);
        //u8g2.drawXBMP( 55, 35, 16, 16, image_Voltage_16x16_bits);
        u8g2.drawXBMP(45,35,30,30,epd_bitmap_allArray[counterGraphics]);
//        if(iconVisible == true){
//          u8g2.drawXBMP( 55, 35, 16, 16, image_Voltage_16x16_bits);
//        }else{
//          u8g2.setDrawColor(0);
//          u8g2.drawBox(56, 35, 13, 15);
//          u8g2.setDrawColor(1);
//        }
        
        u8g2.sendBuffer();          // transfer internal memory to the display
        counterGraphics = (counterGraphics + 1) % 29;
//    }

      } 
      
//      preDisplay(3, 0, 0);
//      display.println("   Power");
//      display.println("  Detected");
//      display.display();
      delay(1000);
      
      voltageDetected = 1; // after coming out from the while loop, the voltage should be greater than 15VDC
      state = 1;
      counterGraphics = 0;

    break;

    case 1: // Power detected... Transition into voltage confirmation
      
      powerDetectionOK = 1;
      state = 2;
      digitalWrite(LED_8, HIGH);
      
      // After voltage detected and voltage drops below 15V, it will go back to state 0
      if (in_voltage < 15 || in_voltage_2 < 15){
        state = 0;
        digitalWrite(LED_8, LOW);
      }
      
    break;

    case 2: // Showing voltage reading on OLED and waiting for confirmation button to be pressed
      // Waiting for the confirmation by pressing the button located on the right hand bottom side
      while(!digitalRead(Button) == LOW){
          adc_value = analogRead(0);
          adc_voltage = (adc_value * ref_voltage) / 4095.0;
          in_voltage = (adc_voltage / resRatio) + 0.3; // 0.3 is for schottky diode voltage adjustment

          // J4 on the tester PWA
          adc_value_2 = analogRead(1);
          adc_voltage_2 = (adc_value_2 * ref_voltage) / 4095.0;
          in_voltage_2 = (adc_voltage_2 / resRatio) + 0.3; // 0.3 is for schottky diode voltage adjustment

          u8g2.setBitmapMode(1);
          u8g2.clearBuffer(); 
          u8g2.drawFrame(2, 2, 124, 62);
          u8g2.drawLine(3, 15, 125, 15);
          u8g2.setFont(u8g2_font_9x15B_mr);
          //u8g2.drawStr(27, 30, "J6:");
          u8g2.setFont(u8g2_font_9x15B_mr);
          sprintf(voltagebuffer,"J6: %.2f", in_voltage);
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
//          if (in_voltage < upperLimit && in_voltage > lowerLimit)
//            u8g2.drawXBMP( 99, 38, 24, 24, image_icons8_outline_effect_tickmark_under_a_square_box_24_bits);
//          else{
//            u8g2.setDrawColor(0);
//            u8g2.drawBox(97, 36, 27, 26);
//            u8g2.setDrawColor(1);
//            voltageCheckVisible = false;
//          }
          u8g2.sendBuffer();

          if (in_voltage < upperLimit && in_voltage > lowerLimit) {
            voltageValidation_1 = 1;
            voltageValidation_2 = 1;
            digitalWrite(LED_9,HIGH);
          } else {
            voltageValidation_1 = 0;
            voltageValidation_2 = 0;
            digitalWrite(LED_9,LOW);
          } 

          if ( voltageValidation_1 == 1 && voltageValidation_2 == 1) {
          VoltageTestOK = 1;
          digitalWrite(LED_9, HIGH);
          state = 3;
        } else {
          digitalWrite(LED_9, LOW);
        }
      }
    break;

    case 3: // Turning off relay for FL test
            u8g2.setBitmapMode(1);
            u8g2.clearBuffer(); 
        
            u8g2.drawFrame(2, 2, 125, 61);
            u8g2.drawLine(2, 14, 126, 14);
            u8g2.setFont(u8g2_font_haxrcorp4089_tr);
            u8g2.drawStr(51, 30, "Relay");
            u8g2.setFont(u8g2_font_haxrcorp4089_tr);
            u8g2.drawStr(33, 12, "Fire Loop Test");
            u8g2.drawXBMP( 50, 34, 30, 30, aepd_bitmap_allArray[counterGraphics]);
            //sprintf(graphicsBuffer, "N: %d", counterGraphics);
            //u8g2.drawStr(100, 12, graphicsBuffer);
            u8g2.sendBuffer();
            
            counterGraphics = (counterGraphics + 1) % 11;
              
//            if (relaySwitchVisible == true){
//              u8g2.drawXBMP( 50, 34, 24, 24, image_icons8_switch_24_bits);
//              u8g2.sendBuffer();  
//              delay(500); // half second delay
//
//              relaySwitchVisible = false;
//        
//            }else{
//              u8g2.drawXBMP( 50, 34, 24, 24, image_icons8_switch_24__1__bits);
//              u8g2.sendBuffer();  
//        
//              // Add relay pin change
//              digitalWrite(Relay,LOW);
//              relaySwitchVisible = true;
//            }
            
            //delay(1000);
            if (counterGraphics == 0){
              state = 4;
              counterGraphics = 0;
              relayActiveFlag = 1;
              digitalWrite(Relay,LOW);
              delay(1000);
              //break;
            }
            
        break;
        
        case 4: // Fire loop test            
        if (relayActiveFlag == 1){
          // Resetting the voltageValidation for fire loop detection
          voltageValidation_1 = 0;
          voltageValidation_2 = 0;

          if (in_voltage < 10 || in_voltage_2 < 10){
            voltageValidation_1 = 1;
            voltageValidation_2 = 1;
          }else{
            voltageValidation_1 = 0;
            voltageValidation_2 = 0;
          }
          
          if ( voltageValidation_1 == 1 && voltageValidation_2 == 1) {
            u8g2.setBitmapMode(1);
            u8g2.clearBuffer(); 
            u8g2.drawFrame(2, 3, 125, 61);
            u8g2.setFont(u8g2_font_haxrcorp4089_tr);
            u8g2.drawStr(33, 12, "Fire Loop Test");
            u8g2.drawLine(2, 14, 126, 14);
            u8g2.drawXBMP( 51, 26, 24, 24, image_icons8_outline_effect_tickmark_under_a_square_box_24_bits);
            u8g2.sendBuffer();
            delay(1000);
            FLTestOK = 1;
            digitalWrite(LED_10, HIGH);
            digitalWrite(Relay, HIGH);
            relayActiveFlag = 0;
            state = 5;
          } else {
//            preDisplay(3, 0, 0);
//            display.println("    FL");
//            display.println("    BAD");
//            display.display();
            delay(1000);
            digitalWrite(LED_10, LOW);
            state = 5;
          } 
        }
        break;
        
        case 5: // Test Result

          // while toggle switch is in the LOW state, display the output voltage reading.
          while (!digitalRead(voltageDisplayToggle) == LOW){
              in_voltage = voltMeasure(0);
              in_voltage_2 = voltMeasure(1);

              u8g2.setBitmapMode(1);
              u8g2.clearBuffer(); 
              u8g2.drawFrame(2, 2, 124, 62);
              u8g2.drawLine(3, 15, 125, 15);
              u8g2.setFont(u8g2_font_haxrcorp4089_tr);
              //u8g2.drawStr(27, 30, "J6:");
              u8g2.setFont(u8g2_font_haxrcorp4089_tr);
              sprintf(voltagebuffer,"J6: %.2f", in_voltage);
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
                u8g2.drawXBMP( 99, 38, 24, 24, image_icons8_outline_effect_tickmark_under_a_square_box_24_bits);
              else{
                u8g2.setDrawColor(0);
                u8g2.drawBox(97, 36, 27, 26);
                u8g2.setDrawColor(1);
                voltageCheckVisible = false;
              }
              u8g2.sendBuffer();
          }
          
          if (VoltageTestOK == 1 && FLTestOK == 1 && powerDetectionOK == 1){

              u8g2.setBitmapMode(1);
              u8g2.clearBuffer(); 
              u8g2.drawFrame(2, 3, 125, 61);
              u8g2.setFont(u8g2_font_haxrcorp4089_tr);
              u8g2.drawStr(40, 12, "All Test OK");
              u8g2.drawLine(2, 14, 126, 14);
              //u8g2.drawXBMP( 51, 26, 24, 24, image_icons8_outline_effect_tickmark_under_a_square_box_24_bits);
              u8g2.drawXBMP(51, 26, 30, 30, good_bitmap_allArray[counterGraphics]);
              u8g2.sendBuffer();  
              counterGraphics = (counterGraphics + 1) % 28;
            ////delay(5000);
            in_voltage = voltMeasure(0);
            in_voltage_2 = voltMeasure(1);
            if(in_voltage < 20 || in_voltage_2 < 20){
              int resetGraphicEnable = 1;
              while (resetGraphicEnable == 1){
                u8g2.clearBuffer();
                u8g2.setBitmapMode(1);
                u8g2.drawFrame(2, 2, 125, 61);
                //u8g2.drawXBMP( 51, 11, 24, 24, image_icons8_reset_24_bits);
                
                u8g2.setFont(u8g2_font_haxrcorp4089_tr);
                u8g2.drawStr(40, 49, "RESETTING...");
                u8g2.drawXBMP(51, 11, 24, 24, reset_bitmap_allArray[counterGraphics2]);
                u8g2.sendBuffer();
                counterGraphics2 = (counterGraphics2 + 1) % 28;

                if (counterGraphics2 == 0){
                  resetGraphicEnable = 0;
                }
              }
              
              
              delay(2000);
              resetParameters();
              
              
              
            }
          }else if(VoltageTestOK == 0 && FLTestOK == 1 && powerDetectionOK == 1){
            // Test Failed
            u8g2.clearBuffer();  
            u8g2.setBitmapMode(1);
            u8g2.drawFrame(2, 2, 124, 62);
            u8g2.setFont(u8g2_font_haxrcorp4089_tr);
            u8g2.drawStr(33, 13, "Voltage Test");
            u8g2.drawLine(2, 14, 126, 14);
            u8g2.drawXBMP( 37, 15, 48, 48, image_icons8_cross_48_bits);
            u8g2.sendBuffer();
            delay(5000);
          }else if(VoltageTestOK == 1 && FLTestOK == 0 && powerDetectionOK == 1){
            // Test Failed
              u8g2.clearBuffer();  
              u8g2.setBitmapMode(1);
              u8g2.drawFrame(2, 2, 124, 62);
              u8g2.setFont(u8g2_font_haxrcorp4089_tr);
              u8g2.drawStr(33, 13, "Fire Loop Test");
              u8g2.drawLine(2, 14, 126, 14);
              u8g2.drawXBMP( 37, 15, 48, 48, image_icons8_cross_48_bits);
              u8g2.sendBuffer();
//            delay(5000);
          }else if(VoltageTestOK == 1 && FLTestOK == 1 && powerDetectionOK == 0){
              u8g2.clearBuffer();  
              u8g2.setBitmapMode(1);
              u8g2.drawFrame(2, 2, 124, 62);
              u8g2.setFont(u8g2_font_haxrcorp4089_tr);
              u8g2.drawStr(20, 13, "Power Detection Test");
              u8g2.drawLine(2, 14, 126, 14);
              u8g2.drawXBMP( 37, 15, 48, 48, image_icons8_cross_48_bits);
              u8g2.sendBuffer();  
//            delay(5000);
          }else if(VoltageTestOK == 0 && FLTestOK == 0 && powerDetectionOK == 1){
            u8g2.clearBuffer();  
            u8g2.setBitmapMode(1);
            u8g2.drawFrame(2, 2, 124, 62);
            u8g2.setFont(u8g2_font_haxrcorp4089_tr);
            u8g2.drawStr(27, 13, "FL and VT Test");
            u8g2.drawLine(2, 14, 126, 14);
            u8g2.drawXBMP( 37, 15, 48, 48, image_icons8_cross_48_bits);
            u8g2.sendBuffer();
            //delay(5000);
          }else{
//            preDisplay(3, 0, 0);
//            display.println("    Test");
//            display.println("   Failed");
//            display.display();
            u8g2.clearBuffer();  

            u8g2.setBitmapMode(1);
            u8g2.drawFrame(2, 2, 125, 61);
            u8g2.setFont(u8g2_font_haxrcorp4089_tr);
            u8g2.drawStr(38, 49, "ALL FAILED");
            u8g2.drawXBMP( 50, 13, 24, 24, image_icons8_sad_24_bits);
                        
            u8g2.sendBuffer();


            //delay(5000);
          }
          
          
          //resetParameters();
          
          
        break;
  }
  }


} // End of main loop

void resetParameters(){
  voltageValidation_1 = 0;
  voltageValidation_2 = 0;
  
  voltageDetected = 0; // upon power connection to 24V, this flag is set to 0 when it is less than 15V.  Set to 1 when it is greater than 15V.  15V is random value.
  
  state = 0;
  
  previousMillis;
  count = 1; // for development purpose, it is set to the state
  
  relayActiveFlag = 0;
  powerDetectionOK = 0;
  VoltageTestOK = 0;
  FLTestOK = 0;

  digitalWrite(LED_8, LOW);
  digitalWrite(LED_9, LOW);
  digitalWrite(LED_10, LOW);
  digitalWrite(Relay,HIGH);
}

float voltMeasure(int channel) {
  analogReadResolution(12);
  
  if(channel == 0){
    
    adc_value = analogRead(channel);
    adc_voltage = (adc_value * ref_voltage) / 4095.0;
    in_voltage = adc_voltage / resRatio;
    return in_voltage;
    
  }

  if(channel == 1){
    
    adc_value_2 = analogRead(channel);
    adc_voltage_2 = (adc_value_2 * ref_voltage) / 4095.0;
    in_voltage_2 = adc_voltage_2 / resRatio;
    return in_voltage_2;

  }
  
} // end of voltMeter function

//void printDisplay(String string, float voltage) {
//  display.println(string);
//  display.print("  ");
//  display.print(voltage);
//  display.print(" V");
//  display.println();
//} // end of printDisplay
//
//void preDisplay(char textSize, int x, int y) {
//  display.clearDisplay();
//  display.setTextSize(2);
//  display.setTextColor(SSD1306_WHITE);
//  display.setCursor(x, y);
//}//end of preDisplay

// void timerIsr() {
//   digitalWrite(2, HIGH);
//   delay(100);
//   digitalWrite(2, LOW);
// }
