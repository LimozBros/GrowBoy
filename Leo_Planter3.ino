#include <LiquidCrystal.h>
#include <TimeLib.h>

LiquidCrystal lcd(2, 3, 7, 6, 5, 4);

int buttonUp = 12;
int buttonDown = 11;
int buttonLeft = 10;
int buttonRight = 9;
int buttonOK = 8;

int pushUp = digitalRead(buttonUp);
int pushDown = digitalRead(buttonDown);
int pushLeft = digitalRead(buttonLeft);
int pushRight = digitalRead(buttonRight);
int pushOK = digitalRead(buttonOK);

int startHour = 0;  // used to save hour
int startMin = 0;   // used to save min
int baseHour = 0;   // current time (hour)
int baseMin = 0;    // current time (min)
int Mode1Hour = 0;  // Mode1 start time (hour)
int Mode1Min = 0;   // Mode1 start time (min)

//--------------------SETUP--------------------//
void setup() {

  pinMode(buttonUp, INPUT_PULLUP);      // set the 5 button pins as INPUT_PULLUP
  pinMode(buttonDown, INPUT_PULLUP);    
  pinMode(buttonLeft, INPUT_PULLUP);    // button open = HIGH, button pressed = LOW
  pinMode(buttonRight, INPUT_PULLUP);   
  pinMode(buttonOK, INPUT_PULLUP);      

  Serial.begin(9600);

  lcd.begin(16, 2);

  welcome();
  delay(5000);

  setUhrzeit();                             // SET CURRENT TIME
  baseHour = startHour;                     // save baseHour
  baseMin = startMin;                       // save baseMin
  startHour = 0;                            // reset startHour
  startMin = 0;                             // reset startMin
  setTime(baseHour,baseMin,0,3,3,2017);     // set Arduino time to user settings (*date must be added*)
  delay(1000);

  setMode1();                               // SET MODE1 STARTING TIME
  Mode1Hour = startHour;
  Mode1Min = startMin;
  startHour = 0;
  startMin = 0;
  delay(1000);
  
  lcd.clear();                              // message at the end of setup
  lcd.setCursor(0, 0);
  lcd.print("SUCCESS!");
  delay(2500);
}

//--------------------LOOP--------------------//
void loop() {
  
  lcd.clear();
  lcd.setCursor(0, 0);                 // prints the following on LCD screen:
  lcd.print("Hour");                    
  lcd.setCursor(0, 1);                 // Hour
  printToLCD(hour());                  // 00:00 (current time)
  lcd.print(":");
  printToLCD(minute());
  delay(5000);                       
  
  lcd.clear();                        
  lcd.setCursor(0, 0);                // prints the following on LCD screen:
  lcd.print("HourMode1");
  lcd.setCursor(0, 1);                // HourMode1
  printToLCD(Mode1Hour);              // 00:00 (Mode1 starting time set by user)
  lcd.print(":");
  printToLCD(Mode1Min);
  delay(5000);
}



//--------------------WELCOME--------------------//
void welcome() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WELCOME!");
  lcd.setCursor(0, 1);
  lcd.print("SETUP starting");
}



//--------------------SETUHRZEIT--------------------//
void setUhrzeit() {                                       // SET CURRENT TIME
  pushOK = digitalRead(buttonOK);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Set time:");
  while (pushOK == HIGH) {                                // push buttonOK to save the displayed hour and go to setMin
    setHour();
  }
  delay(500);
  pushOK = digitalRead(buttonOK);
  while (pushOK == HIGH) {                                // push buttonOK to save the displayed minute and proceed
    setMin();
  }
  delay(500);
}



//--------------------SETMODE1--------------------//
void setMode1() {                                        // SET MODE1
  pushOK = digitalRead(buttonOK);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Set mode1:");
  lcd.setCursor(0, 1);
  while (pushOK == HIGH) {
    setHour();
  }
  delay(500);
  pushOK = digitalRead(buttonOK);
  while (pushOK == HIGH) {
    setMin();
  }
  delay(500);
}



//--------------------SETHOUR--------------------//
void setHour() {                                      // Set hour (00-23)
  if (digitalRead(buttonUp) == LOW) {                 // If buttonUp is pressed, the hour variable is increased by 1
    if (startHour == 23) {                            // If buttonDown is pressed, the hour variable is decreased by 1
      startHour = 0;
    }
    else {
      startHour++;
    }
  }
  if (digitalRead(buttonDown) == LOW) {
    if (startHour == 0) {
      startHour = 23;
    }
    else {
      startHour--;
    }
  }
  lcd.setCursor(0, 1);
  printToLCD(startHour);
  lcd.print(":");
  printToLCD(startMin);
  pushOK = digitalRead(buttonOK);
  delay(200);
}



//--------------------SETMIN--------------------//
void setMin() {                                       // Set minute (00-59)
  if (digitalRead(buttonUp) == LOW) {                 // If buttonUp is pressed, the minute value is increased by 1
    if (startMin == 59) {                             // If buttonDown is pressed, the minute value is decreased by 1
      startMin = 00;
    }
    else {
      startMin++;
    }
  }
  if (digitalRead(buttonDown) == LOW) {
    if (startMin == 00) {
      startMin = 59;
    }
    else {
      startMin--;
    }
  }
  lcd.setCursor(0, 1);
  printToLCD(startHour);
  lcd.print(":");
  printToLCD(startMin);
  pushOK = digitalRead(buttonOK);
  delay(200);
}



//--------------------PRINTTOLCD--------------------//
void printToLCD(int a) {                                // Print the following to LCD:
  if (a < 10) {                                         //  a if a >= 10
    lcd.print("0");                                     //  0a if a < 10 
    lcd.print(a);                                       //
  }                                                     // This way hour and minute are always aligned on the LCD display
  else {                                                // (otherwise you could read 0:0 instead of 00:00)
    lcd.print(a);
  }
}
