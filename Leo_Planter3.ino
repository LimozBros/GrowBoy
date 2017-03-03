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

int startHour = 0;
int startMin = 0;
int baseHour = 0;
int baseMin = 0;
int Mode1Hour = 0;
int Mode1Min = 0;

int a = 0;  // cursor position

//--------------------SETUP--------------------//
void setup() {

  pinMode(buttonUp, INPUT_PULLUP);  // button open = HIGH, button pressed = LOW
  pinMode(buttonDown, INPUT_PULLUP);
  pinMode(buttonLeft, INPUT_PULLUP);
  pinMode(buttonRight, INPUT_PULLUP);
  pinMode(buttonOK, INPUT_PULLUP);

  Serial.begin(9600);

  lcd.begin(16, 2);
  //lcd.blink();

  welcome();
  delay(5000);

  setUhrzeit();
  baseHour = startHour;
  baseMin = startMin;
  startHour = 0;
  startMin = 0;
  setTime(baseHour,baseMin,0,3,3,2017);
  delay(1000);

  setMode1();
  Mode1Hour = startHour;
  Mode1Min = startMin;
  startHour = 0;
  startMin = 0;
  delay(1000);

  //setMode2();
  //delay(1000);
  //setCustom1();
  //delay(1000);
  //setCustom2();

  //delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SUCCESS!");
  delay(2500);
}

//--------------------LOOP--------------------//
void loop() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hour");
  lcd.setCursor(0, 1);
  printToLCD(hour());
  lcd.print(":");
  printToLCD(minute());
  delay(5000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("HourMode1");
  lcd.setCursor(0, 1);
  printToLCD(Mode1Hour);
  lcd.print(":");
  printToLCD(Mode1Min);
  delay(5000);
}

//--------------------SETUHRZEIT--------------------//
void setUhrzeit() {
  pushOK = digitalRead(buttonOK);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Set time:");
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
void setHour() {
  if (digitalRead(buttonUp) == LOW) {
    if (startHour == 23) {
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
void setMin() {
  if (digitalRead(buttonUp) == LOW) {
    if (startMin == 59) {
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

//--------------------SCROLL--------------------//
void scroll(int a) {
  if (digitalRead(buttonRight) == LOW) {
    if (a = 15) {
      a = 0;
    }
    else {
      a++;
    }
  }
  if (digitalRead(buttonLeft) == LOW) {
    if (a = 0) {
      a = 15;
    }
    else {
      a--;
    }
  }
  delay(200);
}

//--------------------WELCOME--------------------//
void welcome() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WELCOME!");
  lcd.setCursor(0, 1);
  lcd.print("SETUP starting");
}

//--------------------SETMODE1--------------------//
void setMode1() {
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

//--------------------SETMODE2--------------------//
void setMode2() {

}

//--------------------SETCUSTOM1--------------------//
void setCustom1() {

}

//--------------------SETCUSTOM2--------------------//
void setCustom2() {

}

//--------------------PRINTTOSERIAL--------------------//
void printToSerial() {
  pushUp = digitalRead(buttonUp);
  pushDown = digitalRead(buttonDown);
  pushLeft = digitalRead(buttonLeft);
  pushRight = digitalRead(buttonRight);
  pushOK = digitalRead(buttonOK);
  Serial.print("buttonOK: ");
  Serial.print(pushOK);
  Serial.print(", ");
  Serial.print("buttonUp: ");
  Serial.print(pushUp);
  Serial.print(", ");
  Serial.print("buttonDown: ");
  Serial.print(pushDown);
  Serial.print(", ");
  Serial.print("buttonLeft: ");
  Serial.print(pushLeft);
  Serial.print(", ");
  Serial.print("buttonRight: ");
  Serial.print(pushRight);
  Serial.print(", time: ");
  Serial.print(baseHour);
  Serial.print(":");
  Serial.println(baseMin);
}

//--------------------PRINTTOLCD--------------------//
void printToLCD(int a) {
  if (a < 10) {
    lcd.print("0");
    lcd.print(a);
  }
  else {
    lcd.print(a);
  }
}
