
/*
 Stepper Motor Control 

 Der Schrittmotor wird über die Pins 8,11,12,13 gesteuert
 Die Freigabe geschieht über Pin 9, 10
 
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

int anz_step = 0;         // Zählt Schitte;
int enA = 9;              // Freigabe A;
int enB = 10;             // Freigabe B;
int v = 1;
int i;

void setup() {
  // serial port:
  Serial.begin(9600);
  
  pinMode( pinA1, OUTPUT); // alle Pins als Output definiert;
  pinMode( pinA2, OUTPUT);
  pinMode( pinB1, OUTPUT);
  pinMode( pinB2, OUTPUT);
   
  pinMode( enA, OUTPUT);
  pinMode( enB, OUTPUT);
}

void loop() {
  
  anz_step=0;
  digitalWrite(enA, HIGH); // Freigabe beider Spulen;
  digitalWrite(enB, HIGH);
  
  for (int i=0; i <= drehung-1; i++){
  for(int j=0; j<1; j++)
  {
  //Schritt  1
  
  digitalWrite(pinA1, HIGH);
  digitalWrite(pinA2, LOW);
  digitalWrite(pinB1, HIGH);
  digitalWrite(pinB2, HIGH);
  delay(v);
  anz_step++;
  //Serial.print("Schritt:");
  //Serial.println(anz_step);
  
  
  //Schritt  2
  
  digitalWrite(pinA1, HIGH);
  digitalWrite(pinA2, LOW);
  digitalWrite(pinB1, HIGH);
  digitalWrite(pinB2, LOW);
  delay(v); 
  anz_step++;
  //Serial.print("Schritt:");
  //Serial.println(anz_step);
  
  
  //Schritt  3
  
  digitalWrite(pinA1, LOW);
  digitalWrite(pinA2, LOW);
  digitalWrite(pinB1, HIGH);
  digitalWrite(pinB2, LOW);
  delay(v); 
  anz_step++;
  //Serial.print("Schritt:");
  //Serial.println(anz_step);
  
  
  //Schritt  4
  
  digitalWrite(pinA1, LOW);
  digitalWrite(pinA2, HIGH);
  digitalWrite(pinB1, HIGH);
  digitalWrite(pinB2, LOW);
  delay(v); 
  anz_step++;
  //Serial.print("Schritt:");
  //Serial.println(anz_step);
  
   //Schritt  5
  
  digitalWrite(pinA1, LOW);
  digitalWrite(pinA2, HIGH);
  digitalWrite(pinB1, HIGH);
  digitalWrite(pinB2, HIGH);
  delay(v);
  anz_step++;
  //Serial.print("Schritt:");
  //Serial.println(anz_step);
  
  
  //Schritt  6
  
  digitalWrite(pinA1, LOW);
  digitalWrite(pinA2, HIGH);
  digitalWrite(pinB1, LOW);
  digitalWrite(pinB2, HIGH);
  delay(v); 
  anz_step++;
  //Serial.print("Schritt:");
  //Serial.println(anz_step);
  
  
  //Schritt  7
  
  digitalWrite(pinA1, HIGH);
  digitalWrite(pinA2, HIGH);
  digitalWrite(pinB1, LOW);
  digitalWrite(pinB2, HIGH);
  delay(v); 
  anz_step++;
  //Serial.print("Schritt:");
  //Serial.println(anz_step);
  
  
  //Schritt  8
  
  digitalWrite(pinA1, HIGH);
  digitalWrite(pinA2, LOW);
  digitalWrite(pinB1, LOW);
  digitalWrite(pinB2, HIGH);
  delay(v); 
  anz_step++;
  //Serial.print("Schritt:");
  //Serial.println(anz_step); 
  
  }
  } //End for Schleife
  
  digitalWrite(enA, HIGH); // Aus beider Spulen;
  digitalWrite(enB, HIGH);
  
  delay(v);
  
}
