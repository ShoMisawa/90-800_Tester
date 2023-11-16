static const unsigned char image_icons8_reset_24_bits[] U8X8_PROGMEM = {0x00,0x00,0x00,0x00,0x3c,0x0c,0x80,0xff,0x0f,0xe0,0xff,0x0f,0xf0,0x81,0x0f,0x78,0xc0,0x0f,0x38,0xe0,0x0f,0x1c,0x00,0x00,0x1c,0x00,0x00,0x0c,0x00,0x00,0x0e,0x00,0x00,0x0e,0x00,0x20,0x04,0x00,0x70,0x00,0x00,0x70,0x00,0x00,0x30,0x00,0x00,0x38,0x00,0x00,0x38,0xf0,0x07,0x1c,0xf0,0x03,0x1e,0xf0,0x81,0x0f,0xf0,0xff,0x07,0xf0,0xff,0x01,0x30,0x3c,0x00,0x00,0x00,0x00};

u8g2.setBitmapMode(1);
u8g2.drawFrame(2, 2, 125, 61);
u8g2.drawXBMP( 51, 11, 24, 24, image_icons8_reset_24_bits);
u8g2.setFont(u8g2_font_haxrcorp4089_tr);
u8g2.drawStr(40, 49, "RESETTING...");



static const unsigned char image_detex_bits[] U8X8_PROGMEM = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xc0,0xff,0x00,0xf0,0xff,0xff,0xff,0xff,0xff,0xcf,0x0f,0xc0,0x03,0xf0,0xff,0x0f,0xf0,0xff,0xff,0xff,0xff,0xff,0xcf,0x3f,0xf8,0x03,0xf0,0xff,0x0f,0xf0,0xff,0xff,0xff,0xff,0xff,0xcf,0x3f,0xf8,0x03,0xf0,0xff,0x3f,0xfc,0xff,0xff,0xff,0xff,0xff,0x0f,0x3f,0xfe,0x00,0xf0,0xff,0x3f,0xf8,0xff,0xff,0xff,0xff,0xff,0x0f,0x3f,0xfe,0x00,0xf0,0x03,0x7f,0x00,0x00,0xc0,0x3f,0x00,0x00,0x00,0xff,0x3f,0x00,0xf0,0x03,0x7f,0x00,0x00,0xc0,0x3f,0x00,0x00,0x00,0xfe,0x3f,0x00,0xfc,0x01,0x7f,0xfc,0xff,0xc0,0x3f,0xf0,0xff,0x03,0xfc,0x1f,0x00,0xfc,0x00,0x7f,0xfc,0xff,0xc0,0x3f,0xf0,0xff,0x03,0xfc,0x0f,0x00,0xfc,0x00,0x7f,0xfe,0xff,0xc0,0x1f,0xf0,0xff,0x03,0xfc,0x0f,0x00,0xfc,0x00,0x3f,0xfe,0xff,0xc0,0x0f,0xf0,0xff,0x03,0xfc,0x0f,0x00,0xfc,0x00,0x3f,0x00,0x00,0xc0,0x0f,0x00,0x00,0x00,0xff,0x0f,0x00,0xfc,0x00,0x3f,0x00,0x00,0xc0,0x0f,0x00,0x00,0x00,0xff,0x0f,0x00,0xfc,0xc0,0x3f,0x00,0x00,0xf0,0x0f,0x00,0x00,0xc0,0xff,0x1f,0x00,0xfc,0xc0,0x1f,0x00,0x00,0xf0,0x0f,0x00,0x00,0xc0,0xcf,0x1f,0x00,0xff,0xff,0x0f,0xff,0x3f,0xf0,0x0f,0xfc,0xff,0xf0,0x0f,0x3f,0x00,0xff,0xff,0x8f,0xff,0x3f,0xf0,0x0f,0xfc,0xff,0xf0,0x07,0x3f,0x00,0xff,0xff,0xc1,0xff,0x3f,0xf0,0x07,0xfc,0xff,0xfc,0x01,0x3f,0x00,0xff,0xff,0xc0,0xff,0x3f,0xf0,0x07,0xfc,0xff,0xfc,0x01,0x3f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
u8g2.setBitmapMode(1);
u8g2.drawXBMP( 15, -1, 100, 70, image_detex_bits);


#include <Arduino.h>
#include <U8g2lib.h>

#include <Wire.h> // library requires for IIC communication

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE); // initialization for the used OLED display

// images from https://lopaka.app/
static const unsigned char image_Voltage_16x16_bits[] U8X8_PROGMEM = {0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x03,0x80,0x01,0xc0,0x01,0xe0,0x00,0xf0,0x07,0x80,0x03,0xc0,0x01,0xc0,0x00,0x60,0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
static const unsigned char image_icons8_outline_effect_tickmark_under_a_square_box_24_bits[] U8X8_PROGMEM = {0xfe,0xff,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf8,0xff,0x7f,0xf0,0xff,0x3f,0xf0,0xff,0x1f,0xf0,0xff,0x1f,0xf8,0xff,0x0f,0xfc,0x1f,0x07,0xfe,0x0f,0x02,0xff,0x0f,0x00,0xff,0x0f,0x80,0xff,0x1f,0xc0,0xff,0x7f,0xe0,0xff,0xff,0xf0,0xff,0xff,0xf1,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0xff,0x7f};
static const unsigned char image_icons8_switch_24__1__bits[] U8X8_PROGMEM = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xe0,0xff,0x07,0xf8,0xff,0x1f,0x1c,0x00,0x38,0x0c,0x80,0x37,0x06,0xc0,0x6f,0x06,0xc0,0x6f,0x06,0xc0,0x6f,0x06,0xc0,0x6f,0x0c,0x80,0x37,0x1c,0x00,0x38,0xf8,0xff,0x1f,0xe0,0xff,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
static const unsigned char image_icons8_switch_24_bits[] U8X8_PROGMEM = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xe0,0xff,0x07,0xf8,0xff,0x1f,0x1c,0xfe,0x3f,0x0c,0xfc,0x3f,0x06,0xf8,0x7f,0x06,0xf8,0x7f,0x06,0xf8,0x7f,0x06,0xf8,0x7f,0x0c,0xfc,0x3f,0x1c,0xfe,0x3f,0xf8,0xff,0x1f,0xe0,0xff,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
static const unsigned char image_icons8_cross_48_bits[] U8X8_PROGMEM = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xfe,0xff,0xff,0x7f,0x00,0x00,0xff,0xff,0xff,0xff,0x00,0x80,0xff,0xff,0xff,0xff,0x01,0xc0,0xff,0xff,0xff,0xff,0x03,0xc0,0xff,0xff,0xff,0xff,0x03,0xc0,0xff,0xff,0xff,0xff,0x03,0xc0,0xff,0xff,0xff,0xff,0x03,0xc0,0xff,0xff,0xff,0xff,0x03,0xc0,0xff,0xff,0xff,0xff,0x03,0xc0,0x7f,0xfc,0x3f,0xfe,0x03,0xc0,0x7f,0xf8,0x1f,0xfe,0x03,0xc0,0x7f,0xf0,0x0f,0xfe,0x03,0xc0,0xff,0xe0,0x07,0xff,0x03,0xc0,0xff,0xc1,0x83,0xff,0x03,0xc0,0xff,0x83,0xc1,0xff,0x03,0xc0,0xff,0x07,0xe0,0xff,0x03,0xc0,0xff,0x0f,0xf0,0xff,0x03,0xc0,0xff,0x1f,0xf8,0xff,0x03,0xc0,0xff,0x1f,0xf8,0xff,0x03,0xc0,0xff,0x0f,0xf0,0xff,0x03,0xc0,0xff,0x07,0xe0,0xff,0x03,0xc0,0xff,0x83,0xc1,0xff,0x03,0xc0,0xff,0xc1,0x83,0xff,0x03,0xc0,0xff,0xe0,0x07,0xff,0x03,0xc0,0x7f,0xf0,0x0f,0xfe,0x03,0xc0,0x7f,0xf8,0x1f,0xfe,0x03,0xc0,0x7f,0xfc,0x3f,0xfe,0x03,0xc0,0xff,0xff,0xff,0xff,0x03,0xc0,0xff,0xff,0xff,0xff,0x03,0xc0,0xff,0xff,0xff,0xff,0x03,0xc0,0xff,0xff,0xff,0xff,0x03,0xc0,0xff,0xff,0xff,0xff,0x03,0xc0,0xff,0xff,0xff,0xff,0x03,0x80,0xff,0xff,0xff,0xff,0x01,0x00,0xff,0xff,0xff,0xff,0x00,0x00,0xfe,0xff,0xff,0x7f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};


int state = 9; // debug purpose only


bool iconVisible = true; // default should be true
bool voltageCheckVisible = true; // default should be false
bool relaySwitchVisible = true; // default should be true

const long interval = 1000; // Flash interval for the icon in millisecond
unsigned long previousMillis = 0;

char buffer[32]; // helper buffer to construct a string to be displayed

void setup(void) {
  u8g2.begin(); // start the u8g2 library
}

void loop(void) {
  unsigned long currentMillis = millis();

	u8g2.clearBuffer();					// clear the internal memory
	u8g2.setBitmapMode(1);
	if (state == 1){
		if (currentMillis - previousMillis >= interval) {
				previousMillis = currentMillis;
				iconVisible = !iconVisible;
				u8g2.clearBuffer();
				u8g2.drawFrame(2, 2, 123, 61);
				u8g2.setFont(u8g2_font_helvB08_tr);
				u8g2.drawStr(17, 29, "Waiting for Power");
				if(iconVisible == true){
					u8g2.drawXBMP( 55, 35, 16, 16, image_Voltage_16x16_bits);
				}else{
					u8g2.setDrawColor(0);
					u8g2.drawBox(56, 35, 13, 15);
					u8g2.setDrawColor(1);
				}
				
				u8g2.sendBuffer();					// transfer internal memory to the display
		}
	} // end of if

	// Power is detected.
	if (state == 2){
		u8g2.setBitmapMode(1);
		u8g2.clearBuffer();	
		u8g2.drawFrame(2, 2, 124, 62);
		u8g2.drawLine(3, 15, 125, 15);
		u8g2.setFont(u8g2_font_haxrcorp4089_tr);
		u8g2.drawStr(27, 30, "J6:");
		u8g2.setFont(u8g2_font_haxrcorp4089_tr);
		u8g2.drawStr(52, 30, "24.6");
		u8g2.setFont(u8g2_font_haxrcorp4089_tr);
		u8g2.drawStr(83, 30, "V");
		u8g2.setFont(u8g2_font_haxrcorp4089_tr);
		u8g2.drawStr(30, 13, "Voltage Reading");
		u8g2.setFont(u8g2_font_haxrcorp4089_tr);
		u8g2.drawStr(27, 45, "J7:");
		u8g2.setFont(u8g2_font_haxrcorp4089_tr);
		u8g2.drawStr(52, 45, "24.6");
		u8g2.setFont(u8g2_font_haxrcorp4089_tr);
		u8g2.drawStr(83, 45, "V");
		if (voltageCheckVisible == true)
			u8g2.drawXBMP( 99, 38, 24, 24, image_icons8_outline_effect_tickmark_under_a_square_box_24_bits);
		else{
			u8g2.setDrawColor(0);
			u8g2.drawBox(97, 36, 27, 26);
			u8g2.setDrawColor(1);
		}
		u8g2.sendBuffer();	
	}

	// Showing turning off relay for FL test
	if (state == 3){
		u8g2.setBitmapMode(1);
		u8g2.clearBuffer();	

		u8g2.drawFrame(2, 2, 125, 61);
		u8g2.drawLine(2, 14, 126, 14);
		u8g2.setFont(u8g2_font_haxrcorp4089_tr);
		u8g2.drawStr(51, 30, "Relay");
		u8g2.setFont(u8g2_font_haxrcorp4089_tr);
		u8g2.drawStr(33, 12, "Fire Loop Test");

		if (relaySwitchVisible == true){
			u8g2.drawXBMP( 50, 34, 24, 24, image_icons8_switch_24_bits);
			u8g2.sendBuffer();	
			delay(500); // half second delay

		}else{
			u8g2.drawXBMP( 50, 34, 24, 24, image_icons8_switch_24__1__bits);
			u8g2.sendBuffer();	

			// Add relay pin change



		}

		
	}

	// FL Test Good
	if (state == 4){
		u8g2.setBitmapMode(1);
		u8g2.clearBuffer();	
		u8g2.drawFrame(2, 3, 125, 61);
		u8g2.setFont(u8g2_font_haxrcorp4089_tr);
		u8g2.drawStr(33, 12, "Fire Loop Test");
		u8g2.drawLine(2, 14, 126, 14);
		u8g2.drawXBMP( 51, 26, 24, 24, image_icons8_outline_effect_tickmark_under_a_square_box_24_bits);
		u8g2.sendBuffer();	
	}

	// Power is detected.
	if (state == 5){
		u8g2.setBitmapMode(1);
		u8g2.clearBuffer();	
		u8g2.drawFrame(2, 3, 125, 61);
		u8g2.setFont(u8g2_font_haxrcorp4089_tr);
		u8g2.drawStr(40, 12, "All Test OK");
		u8g2.drawLine(2, 14, 126, 14);
		u8g2.drawXBMP( 51, 26, 24, 24, image_icons8_outline_effect_tickmark_under_a_square_box_24_bits);
		u8g2.sendBuffer();	
	}

	// Voltage test failed
	if (state == 6){
		u8g2.clearBuffer();	
		u8g2.setBitmapMode(1);
		u8g2.drawFrame(2, 2, 124, 62);
		u8g2.setFont(u8g2_font_haxrcorp4089_tr);
		u8g2.drawStr(33, 13, "Voltage Test");
		u8g2.drawLine(2, 14, 126, 14);
		u8g2.drawXBMP( 37, 15, 48, 48, image_icons8_cross_48_bits);
		u8g2.sendBuffer();	
	}

	// Power is detected.
	if (state == 7){
		u8g2.clearBuffer();	
		u8g2.setBitmapMode(1);
		u8g2.drawFrame(2, 2, 124, 62);
		u8g2.setFont(u8g2_font_haxrcorp4089_tr);
		u8g2.drawStr(33, 13, "Fire Loop Test");
		u8g2.drawLine(2, 14, 126, 14);
		u8g2.drawXBMP( 37, 15, 48, 48, image_icons8_cross_48_bits);
		u8g2.sendBuffer();	
	}

	if (state == 8){
		u8g2.clearBuffer();	
		u8g2.setBitmapMode(1);
		u8g2.drawFrame(2, 2, 124, 62);
		u8g2.setFont(u8g2_font_haxrcorp4089_tr);
		u8g2.drawStr(20, 13, "Power Detection Test");
		u8g2.drawLine(2, 14, 126, 14);
		u8g2.drawXBMP( 37, 15, 48, 48, image_icons8_cross_48_bits);
		u8g2.sendBuffer();	
	}

	if (state == 9){
		u8g2.clearBuffer();	
		u8g2.setBitmapMode(1);
		u8g2.drawFrame(2, 2, 124, 62);
		u8g2.setFont(u8g2_font_haxrcorp4089_tr);
		u8g2.drawStr(27, 13, "FL and VT Test");
		u8g2.drawLine(2, 14, 126, 14);
		u8g2.drawXBMP( 37, 15, 48, 48, image_icons8_cross_48_bits);
		u8g2.sendBuffer();	
	}

	if (state == 10){
		u8g2.clearBuffer();	



		u8g2.sendBuffer();	
	}
	
	

  
}


