#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define I2C_ADDR    0x27  // Define I2C Address where the PCF8574A is
// Address can be changed by soldering A0, A1, or A2
// Default is 0x27

// map the pin configuration of LCD backpack for the LiquidCristal class
#define BACKLIGHT_PIN 3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7

LiquidCrystal_I2C lcd(I2C_ADDR,
                      En_pin, Rw_pin, Rs_pin, D4_pin, D5_pin, D6_pin, D7_pin,
                      BACKLIGHT_PIN, POSITIVE);
int OUT_Pin = A0;


// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

#include "DHT.h"

#define DHTPIN 2     // what digital pin we're connected to

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);

void setup() {

  lcd.begin(20, 4);       // 20 columns by 4 rows on display
  lcd.setBacklight(HIGH); // Turn on backlight, LOW for off
  Serial.begin(9600);

  dht.begin();

  lcd.setCursor ( 0, 0 );            // go to the bottom left corner
  lcd.print("Nebulaworks2016"); // write this string

}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  // float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(f)) {
    lcd.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  // float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  // float hic = dht.computeHeatIndex(t, h, false);

  lcd.setCursor ( 0, 1 );            // go to the Top left corner

  lcd.print("Humidity: ");
  lcd.print(h);
  lcd.print(" %");

  lcd.setCursor ( 0, 2 );            // go to the middle left corner

  lcd.print("Temperature: ");
  // lcd.print(t);
  // lcd.print(" *C ");
  lcd.print(f);
  lcd.print(" F");
  // lcd.print("Heat index: ");
  // lcd.print(hic);
  // lcd.print(" *C ");
  // lcd.print(hif);
  // lcd.println(" *F");

  lcd.setCursor ( 0, 3 );            // go to the middle left corner
  lcd.print("Output Level:"); // write this string on the top row
  lcd.print(analogRead(OUT_Pin));
  delay(500);

}
