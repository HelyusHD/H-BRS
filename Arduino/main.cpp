#include <FastLED.h>
#include <stdio.h>
#include <math.h>
#include <IRremote.h>

#define BUTTON0 3910598400
#define BUTTON1 4077715200
#define BUTTON2 3877175040
#define BUTTON3 2707357440
#define BUTTON4 4144561920
#define BUTTON5 3810328320
#define BUTTON6 2774204160
#define BUTTON7 3175284480
#define BUTTON8 2907897600
#define BUTTON9 3041591040
#define BUTTONON 3125149440

#define RECIVER_PIN 4
#define LED_PIN 5    // Replace with the pin number you used for DATA connection

#define NUM_LEDS 47  // Replace with the number of LEDs in your strip
#define DELAY_TIME 100  // Delay between LED movements (in milliseconds)
CRGB leds[NUM_LEDS];

const int RECV_PIN = 7;
bool on;
int r, g, b;
int t = 0, max_t = NUM_LEDS*10;

// Funktion zum Umwandeln von HSV in RGB
void hsv_to_rgb(float h, float s, float v, int *r, int *g, int *b) {
  float c = v * s; // Chroma
  float x = c * (1 - fabs(fmod(h / 60.0, 2) - 1));
  float m = v - c;

  float r_prime, g_prime, b_prime;

  if (h >= 0 && h < 60) {
      r_prime = c, g_prime = x, b_prime = 0;
  } else if (h >= 60 && h < 120) {
      r_prime = x, g_prime = c, b_prime = 0;
  } else if (h >= 120 && h < 180) {
      r_prime = 0, g_prime = c, b_prime = x;
  } else if (h >= 180 && h < 240) {
      r_prime = 0, g_prime = x, b_prime = c;
  } else if (h >= 240 && h < 300) {
      r_prime = x, g_prime = 0, b_prime = c;
  } else {
      r_prime = c, g_prime = 0, b_prime = x;
  }

  *r = (int)((r_prime + m) * 255);
  *g = (int)((g_prime + m) * 255);
  *b = (int)((b_prime + m) * 255);
}

// Hauptfunktion für den Regenbogen
void rainbow_color(int t, int max_t, int *r, int *g, int *b) {
    if (t < 0) t = 0;
    if (t > max_t) t = max_t;

    float hue = 360.0 * t / max_t; // Hue von 0 bis 360 Grad
    hsv_to_rgb(hue, 1.0, 1.0, r, g, b); // Volle Sättigung und Helligkeit
}

void setup()
{
    Serial.begin(9600);
    IrReceiver.begin(RECIVER_PIN, ENABLE_LED_FEEDBACK);
    Serial.print("running\n");
    on = true;
    FastLED.addLeds<WS2815, LED_PIN, RGB>(leds, NUM_LEDS);
}

void loop() {
    if (IrReceiver.decode()) {
        uint32_t rawData= IrReceiver.decodedIRData.decodedRawData;
        Serial.print(rawData);
        Serial.print("\n");

        if(rawData == BUTTONON){
            Serial.print("pressed ON\n");
            if(on){
                on = false;
                for (int i = 0; i < NUM_LEDS; i++) {
                    leds[i].r = 0;
                    leds[i].g = 0; 
                    leds[i].b = 0;
                }
                FastLED.show();  // Update the LED strip
            }else{
                on = true;
            }
        }else if(rawData == BUTTON1) {
            Serial.print("pressed 1\n");
        }
        IrReceiver.resume(); 
    }else if (on){
    for (int i = 0; i < NUM_LEDS; i++) {
        // int p = t + i*(int)floor(max_t / NUM_LEDS);
        int p = t + i;
        if (p > max_t) p = p - max_t;
        rainbow_color(p, max_t, &r, &g, &b);
        leds[i].r = r;
        leds[i].g = g; 
        leds[i].b = b;
    }
    t += 5;
    if (t > max_t) t = 0;
    FastLED.show();  // Update the LED strip
    delay(DELAY_TIME);  // Delay between LED movements
    }

}
