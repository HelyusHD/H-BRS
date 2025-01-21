
/*
 Stepper Motor Control 

 
 Darf ohne Einschränkungen Genutzt werden
 
 H.Salbert
*/
 

#include <Stepper.h>

const int drehung = 150;  // Schritte pro Drehung;

// initialisierung;

int pinA1 = 8;   // + Spule A;
int pinA2 = 11;   // - Spule A;
int pinB1 = 12;   // + Spule B;
int pinB2 = 13;   // - Spule B;
int v;

void setup() {
  // serial port:
  
  
  pinMode( pinA1, OUTPUT); // alle Pins als Output definiert;
  pinMode( pinA2, OUTPUT);
  pinMode( pinB1, OUTPUT);
  pinMode( pinB2, OUTPUT);
  v = 20;
  
}

void loop() {
  
  
  //Schritt  1
  
  digitalWrite(pinA1, HIGH);
  digitalWrite(pinA2, LOW);
  digitalWrite(pinB1, HIGH);
  digitalWrite(pinB2, LOW);
 
  delay(v);
  
  //Schritt  2
  
  digitalWrite(pinA1, LOW);
  digitalWrite(pinA2, HIGH);
  digitalWrite(pinB1, HIGH);
  digitalWrite(pinB2, LOW);
 delay(v);
  
  //Schritt  3
  
  digitalWrite(pinA1, LOW);
  digitalWrite(pinA2, HIGH);
  digitalWrite(pinB1, LOW);
  digitalWrite(pinB2, HIGH);
  
  delay(v);
  //Schritt  4
  
  digitalWrite(pinA1, HIGH);
  digitalWrite(pinA2, LOW);
  digitalWrite(pinB1, LOW);
  digitalWrite(pinB2, HIGH);
  delay(v);
  
}
