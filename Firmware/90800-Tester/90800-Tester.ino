#include <Beastdevices_INA3221.h>
#include <Wire.h>

#include <SPI.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>  //https://github.com/adafruit/Adafruit-GFX-Library
#include <OneWire.h>
//#include <DallasTemperature.h>   //https://github.com/milesburton/Arduino-Temperature-Control-Library
#define ONE_WIRE_BUS 10

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Beastdevices_INA3221 ina3221(INA3221_ADDR41_VCC);

//OneWire oneWire(ONE_WIRE_BUS);
//DallasTemperature sensors(&oneWire);


#define UI_BMPWIDTH  128
//#define upperLimit 24*(1+0.05)
#define upperLimit 24*(1+0.1)
#define lowerLimit 24*(1-0.1)

#define LED_8 8
#define LED_9 9
#define LED_10 10
#define Relay 7
#define Button 2

float R1 = 100000;
float R2 = 10000;
float resRatio = R2 / (R1 + R2);

// Bot J6
float adc_voltage = 0.0;
float in_voltage = 0.0;
float ref_voltage = 3.3;
int adc_value = 0;

// Top J9
float adc_voltage_2 = 0.0;
float in_voltage_2 = 0.0;
int adc_value_2 = 0;

int voltageValidation_1 = 0;
int voltageValidation_2 = 0;

int voltageDetected = 0; // upon power connection to 24V, this flag is set to 0 when it is less than 15V.  Set to 1 when it is greater than 15V.  15V is random value.

int state = 0;

unsigned long previousMillis;
int count = 1; // for development purpose, it is set to the state

int relayActiveFlag = 0;
int powerDetectionOK = 0;
int VoltageTestOK = 0;
int FLTestOK = 0;


void setup() {

  pinMode(Button, INPUT_PULLUP);
  pinMode(LED_8, OUTPUT);
  pinMode(LED_9, OUTPUT);
  pinMode(LED_10, OUTPUT);
  //digitalWrite(3,HIGH);
  pinMode(Relay, OUTPUT);
  digitalWrite(LED_8, LOW);
  digitalWrite(LED_9, LOW);
  digitalWrite(LED_10, LOW);
  digitalWrite(Relay, HIGH);

  Serial.begin(9600);
  Serial.println("Starting up ...");
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.display();

  

}

void loop() {


  unsigned long currentMillis = millis();

  // Waiting for 24V to come in...
  // Reading Voltage
  in_voltage = voltMeasure(0);
  in_voltage_2 = voltMeasure(1);

  // if 24V line is greater than 15V, asume that the DUT is connected to the tester.  Which is indicated using voltageDetected variable.
  if ((in_voltage > 15 || in_voltage_2 > 15) && voltageDetected == 0 && voltageDetected != 2) {
    voltageDetected = 1;
    state = 1; // Going to state 1

  } else if (voltageDetected != 2) {
    preDisplay(2, 0, 0);
    display.println("  Waiting");
    display.println("    for ");
    display.println("   Power");
    display.display();
    voltageDetected = 0;
  }

  if (voltageDetected == 1) {
    voltageDetected = 2;
  }

  if (voltageDetected == 2) {
    switch (state) {
      case 1: // Waiting until power is detected...
        preDisplay(3, 0, 0);
        display.println("   Power");
        display.println("  Detected");
        display.display();
        delay(100);
        powerDetectionOK = 1;
        state = 2;
        digitalWrite(LED_8, HIGH);
        break;

      case 2: // Checking voltage level
        if ((currentMillis - previousMillis) >= 1000) {
          previousMillis = currentMillis;
          digitalWrite(LED_9, HIGH);
        }
        digitalWrite(LED_9, LOW);
        preDisplay(2, 0, 0);
        printDisplay("J6", in_voltage);
        printDisplay("J7", in_voltage_2);
        display.display();

        if (in_voltage < 15 || in_voltage_2 < 15) {
          voltageDetected = 0;
          break;
        }

        while(!digitalRead(Button) == LOW){
          in_voltage = voltMeasure(0);
          in_voltage_2 = voltMeasure(1);
          preDisplay(2, 0, 0);
          printDisplay("J6", in_voltage);
          printDisplay("J7", in_voltage_2);
          display.display();
          
          if (in_voltage < upperLimit && in_voltage > lowerLimit) {
            voltageValidation_1 = 1;
            voltageValidation_2 = 1;
            digitalWrite(LED_9,HIGH);
          } else {
            voltageValidation_1 = 0;
            voltageValidation_2 = 0;
            digitalWrite(LED_9,LOW);
          }

          
        }
//        
//        if ((in_voltage < upperLimit) && ((in_voltage > lowerLimit))) {
//          voltageValidation_1 = 1;
//        } else {
//          voltageValidation_1 = 0;
//        }
//
//        if ((in_voltage_2 < upperLimit) && ((in_voltage_2 > lowerLimit))) {
//          voltageValidation_2 = 1;
//        } else {
//          voltageValidation_2 = 0;
//        }
        
        if ( voltageValidation_1 == 1 && voltageValidation_2 == 1) {
          VoltageTestOK = 1;
          preDisplay(3, 0, 0);
          display.println("  Voltage");
          display.println("    OK");
          display.display();
          digitalWrite(LED_9, HIGH);
          delay(1000);
          state = 3;
        } else {
          digitalWrite(LED_9, LOW);
        }
        break;
        case 3: // Turning off relay for FL test
            digitalWrite(Relay,LOW);
            preDisplay(3, 0, 0);
            display.println("   Relay");
            display.println("   Active");
            display.display();
            relayActiveFlag = 1;
            delay(1000);
            state = 4;
        break;
        case 4: // Fire loop test
            
            preDisplay(2, 0, 0);
            printDisplay("J6", in_voltage);
            printDisplay("J7", in_voltage_2);
            display.display();
            
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
            preDisplay(3, 0, 0);
            display.println("    FL");
            display.println("   Good");
            display.display();
            delay(1000);
            FLTestOK = 1;
            digitalWrite(LED_10, HIGH);
            digitalWrite(Relay, HIGH);
            relayActiveFlag = 0;
            state = 5;
          } else {
            preDisplay(3, 0, 0);
            display.println("    FL");
            display.println("    BAD");
            display.display();
            delay(1000);
            digitalWrite(LED_10, LOW);
            state = 5;
          }
          
        }

        break;
        case 5:
//          preDisplay(3, 0, 0);
//          display.println("   Case 5");
//          //display.println("   ");
//          display.display();
//          delay(5000);
          
          if (VoltageTestOK == 1 && FLTestOK == 1 && powerDetectionOK == 1){
            preDisplay(3, 0, 0);
            display.println("   Test");
            display.println("   Good");
            display.display();
            //delay(5000);
            in_voltage = voltMeasure(0);
            in_voltage_2 = voltMeasure(1);
            if(in_voltage < 20 || in_voltage_2 < 20){
              preDisplay(3, 0, 0);
              display.println("Resetting");
              display.display();
              delay(2000);
              resetParameters();
            }
          }else if(VoltageTestOK == 0 && FLTestOK == 1 && powerDetectionOK == 1){
            // Test Failed
            preDisplay(3, 0, 0);
            display.println("     VT");
            display.println("   Failed");
            display.display();
            delay(5000);
          }else if(VoltageTestOK == 1 && FLTestOK == 0 && powerDetectionOK == 1){
            // Test Failed
            preDisplay(3, 0, 0);
            display.println("     FL");
            display.println("   Failed");
            display.display();
            delay(5000);
          }else if(VoltageTestOK == 1 && FLTestOK == 1 && powerDetectionOK == 0){
            preDisplay(3, 0, 0);
            display.println("     PD");
            display.println("   Failed");
            display.display();
            delay(5000);
          }else if(VoltageTestOK == 0 && FLTestOK == 0 && powerDetectionOK == 1){
            preDisplay(3, 0, 0);
            display.println("   VT,FL");
            display.println("   Failed");
            display.display();
            delay(5000);
          }else{
            preDisplay(3, 0, 0);
            display.println("    Test");
            display.println("   Failed");
            display.display();
            delay(5000);
          }
          
          
          //resetParameters();
          
          
        break;
    } // end of switch statement
  }
  //delay(500);
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
  adc_value = analogRead(channel);
  adc_voltage = (adc_value * ref_voltage) / 4095.0;
  in_voltage = adc_voltage / resRatio;

  return in_voltage;
} // end of voltMeter function

void printDisplay(String string, float voltage) {
  display.println(string);
  display.print("  ");
  display.print(voltage);
  display.print(" V");
  display.println();
} // end of printDisplay

void preDisplay(char textSize, int x, int y) {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(x, y);
}//end of preDisplay

void timerIsr() {
  digitalWrite(2, HIGH);
  delay(100);
  digitalWrite(2, LOW);
}
