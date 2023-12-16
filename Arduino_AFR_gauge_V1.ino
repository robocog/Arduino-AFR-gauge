#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MCP4725.h>
Adafruit_MCP4725 dac;
// Set this value to 9, 8, 7, 6 or 5 to adjust the resolution
//#define DAC_RESOLUTION    (9)
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

float input_voltage = 0.0;
float afr=0.00;
float gauge=0;

void setup(void) {
  Serial.begin(9600);

// SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
    }
// Clear the SSD1306 buffer
  display.clearDisplay();
  
  Serial.println("MCP4725A1 Test");
  // MCP4725A1 address is 0x62 (default) 
  // MCP4725A1 address is 0x63 (ADDR pin tied to VCC) 
  // MCP4725A1 address is 0x60 (ADDR pin tied to GND) 
  dac.begin(0x60); //I have my ADDR pin connected to GND so address is 0x60
}

void loop(void) { 
//read analog pin
int analog_value = analogRead(A0);
  
//convert input pin ADC value to volts (0=0v rich, 1024=5v lean)
input_voltage = (analog_value * 5) / 1024.0;

//convert calculated voltage to AFR reading  (0v=10afr- rich, 5v=20afr-lean)
afr= ((input_voltage / 0.5)+10);

//convert calculated afr to suit gauge scaling (my gauge = rich max=60, stoich=30, lean min=0)
//alternately to scale top of optimal as 12.5 and lower optimal as 15...
//gauge = ((afr - 10)/(18-10))*(1-50)+50;
//new_value = ((old_value - old_min) / (old_max - old_min) ) * (new_max - new_min) + new_min

//new dac controlled gauge...
gauge = ((afr - 10)/(20-10))*(0-4095)+4095;

//Send raw iput pin ADC value, calculated volts and calculated AFR to serial output 
Serial.print("Pin= ");
Serial.println(analog_value);  
Serial.print("V= ");
Serial.println(input_voltage);
Serial.print("AFR= ");
Serial.println(afr);
Serial.print("Gauge= ");
Serial.println(gauge);

//send to analog gauge
dac.setVoltage(gauge/4.5, false);        //Set voltage to gauge
//dac.setVoltage(1095/4, false);
//send to display
display.clearDisplay();
display.setCursor(0,0);             // Start at top-left corner

display.setTextSize(4);             // Draw 2X-scale text
display.setTextColor(WHITE);

display.println(afr);

display.setTextSize(2);
display.print("----------");
display.print(F("Volt: ")); display.println(input_voltage);

display.display();
  
}
