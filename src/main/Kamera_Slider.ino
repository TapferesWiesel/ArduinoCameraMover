#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

int dist = 0;      // Weg der Kamera
int zeit = 0; // Zeit für Weg
long schritte = 0;
long t_delay = 0;
int wert_encoder1 = LOW;
int wert_encoder1Alt = LOW;
int endstop =7;
int dir = 8;
int steps = 9;
int encoder1 = 10;
int encoder2 = 11;
int encoder_sw = 12;
#define OLED_RESET 4 // not used / nicht genutzt bei diesem Display
Adafruit_SSD1306 display(OLED_RESET);

LiquidCrystal_I2C lcd(0x27, 16, 2);
display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
void setup() {

  pinMode(endstop, INPUT);
  pinMode(dir, OUTPUT);
  pinMode(steps, OUTPUT);
  pinMode(encoder1, INPUT);
  pinMode(encoder2, INPUT);
  pinMode(encoder_sw, INPUT_PULLUP);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  #define DRAW_DELAY 118
  #define D_NUM 4
}

void findZero() {                        //Enstop anfahren 
//  Serial.println(digitalRead(10));
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Home...");
delay(1000);
    digitalWrite(dir, LOW);
  while (!digitalRead(endstop)){
     digitalWrite(steps, HIGH);
  delayMicroseconds(60);
  digitalWrite(steps, LOW);
  delayMicroseconds(60);
  }
//  Serial.println("Found Zero");

lcd.setCursor(0, 1);
lcd.print("Nullpunkt OK");
} 

void getDist(){             // Eingabe Distanz, max. 400mm Weg
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Distanz:");
while (digitalRead(encoder_sw)){
  
wert_encoder1 = digitalRead(encoder1);
 if ((wert_encoder1 == HIGH) && (wert_encoder1Alt == LOW)) {
 if (digitalRead(encoder2) == HIGH) {
 dist = dist +10;
 if (dist > 410) dist = 410;
 } else {
 dist = dist - 10;
 if (dist < 0) dist = 0;
 }
 // Serial.print("Distanz: ");
 // Serial.println (dist, DEC);
 lcd.setCursor(0, 1);
 lcd.print(dist);
 }
 wert_encoder1Alt = wert_encoder1;
}
}


void getTime(){          // Eingabe Zeit in Sekunden

lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Zeit:");

while (digitalRead(encoder_sw)){
  
wert_encoder1 = digitalRead(encoder1);
 if ((wert_encoder1 == HIGH) && (wert_encoder1Alt == LOW)) {
 if (digitalRead(encoder2) == HIGH) {
 zeit = zeit +10;
 } else {
 zeit = zeit - 10;
 if (zeit < 0) zeit = 0;
 }
 // Serial.print("Zeit: ");
 // Serial.println (zeit);
lcd.setCursor(0, 1);
lcd.print(zeit);
 
 }
 wert_encoder1Alt = wert_encoder1;
}
  
 
}
void moveMillimeters(long dist){

 

  schritte = (dist * 800);
  t_delay = ((zeit)*1000000/schritte)/2;
  if (t_delay < 60) t_delay = 60;
 /* Serial.print(schritte, DEC);
  Serial.println(" Steps");
  Serial.print(t_delay);
  Serial.println(" Mirkosekunden");
  Serial.print("Moving ");
  Serial.print(dist, DEC);
  Serial.print(" millimeters");
  Serial.print(" in ");
  Serial.print(zeit, DEC);
  Serial.println(" Sekunden");*/
  digitalWrite(dir, HIGH);
for (long i = 0; i < schritte; i++)  { //count all Steps
  
  digitalWrite(steps, HIGH);
  delayMicroseconds(t_delay);
  digitalWrite(steps, LOW);
  delayMicroseconds(t_delay);

}

 lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print("Fertig!");
 lcd.setCursor(0, 1);
 lcd.print("zurueck auf Null...");
 
  delay(5000);
  digitalWrite(dir, LOW);

  for (long i = 0; i < schritte-3200; i++) {    // Schlitten zurück auf Start -2mm
    digitalWrite(steps, HIGH);
  delayMicroseconds(60);
  digitalWrite(steps, LOW);
  delayMicroseconds(60);
  } 
}




void loop() {
 findZero();
 getDist();
 delay(200);
 getTime();
 lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print("Distanz: ");
 lcd.print(dist);
 lcd.setCursor(0, 1);
 lcd.print("Zeit: ");
 lcd.print(zeit);
 
/* Serial.print("Distanz ");
 Serial.print(dist);
 Serial.println(" mm");
 Serial.print("Zeit ");
 Serial.print(zeit);
 Serial.println(" Sekunden");  */
 moveMillimeters(dist);

 delay(10000);
 zeit = 0;
 dist = 0;

}
