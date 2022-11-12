/*********
  Henrique Gianetti Seleghini            RM82703
  Guilherme Hideki Takara Chalita        RM82358
  João Vitor de Camargo Ferreira Ramos   RM82215
*********/

#include <Adafruit_LiquidCrystal.h>

Adafruit_LiquidCrystal display_lcd(0);

typedef struct {
  int triggerPin;   
  int echoPin;      
  int ledPin;      
  int distance;
} UltrasonicSensor;

const int triggerDistance = 200; //200cm - 2m
const int qtParkingSpots = 2;
  
UltrasonicSensor parkingSpots[qtParkingSpots] = {
  {10, 9, 8, 0},
  {7, 6, 5, 0}
};

void setup() {
  for(int i=0; i < qtParkingSpots; i++) {
    pinMode(parkingSpots[i].ledPin, OUTPUT);
  }
  
  display_lcd.begin(16, 2);
  display_lcd.setBacklight(1);
  display_lcd.setCursor(0, 0);
  display_lcd.print(" Estacionamento");
  display_lcd.setCursor(0, 1);
  display_lcd.print("      FIAP      ");
  delay(3000);
}

void loop() {
  int occupedParkingSpots = 0;
  int emptyParkingSpots = 0;
  
  for(int i=0; i < qtParkingSpots; i++) {
    parkingSpots[i].distance = readUltrasonicDistance(parkingSpots[i].triggerPin, parkingSpots[i].echoPin);
    
    if(parkingSpots[i].distance <= triggerDistance) {
      occupedParkingSpots++;
      digitalWrite(parkingSpots[i].ledPin, LOW);
    } else{
      emptyParkingSpots++;
      digitalWrite(parkingSpots[i].ledPin, HIGH);
    }
  }
  
  display_lcd.setCursor(0, 0);
  display_lcd.print("Vagas Livres   ");
  display_lcd.print(emptyParkingSpots);
  display_lcd.setCursor(0, 1);
  display_lcd.print("Vagas Ocupadas ");
  display_lcd.print(occupedParkingSpots);
  
  delay(50);
}

long readUltrasonicDistance(int triggerPin, int echoPin) {
  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
 
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  
  //Converte para centímetros (cm)
  long distance = 0.01723 * pulseIn(echoPin, HIGH);
  
  return distance;
}